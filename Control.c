#include "Control.h"
#define BUFFER_LEN 1000
  
FEL* Control_InitializeModeOne(float lambda0, float lambda1, float mu, int numTasks)
{
  FEL* fel = FEL_Create(numTasks, numTasks, mu, lambda0, lambda1);
  Event* event;
  ListNode* newNode;

  ListNode* zeroList; //A list of all of the zero arrivals
  ListNode* oneList;  //A list of all of the one arrivals
  ListNode* zeroListTail;  //Keep track of the tail of the lists
  ListNode* oneListTail;

  int prevTime0 = -1;
  int prevTime1 = -1;
  int i;

  //Initialize the FEL EventList
  event = FEL_GenerateRandomArrival(fel, 0, prevTime0);
  zeroList = ListNode_Create(event);
  zeroListTail = zeroList;

  event = FEL_GenerateRandomArrival(fel, 1, prevTime1);
  oneList = ListNode_Create(event);
  oneListTail = oneList;
  
  for(i=0;i<numTasks;i++)
  {
    //Add a zero priority event
    event = FEL_GenerateRandomArrival(fel,0,prevTime0);
    newNode = ListNode_Create(event);
    zeroListTail = ListNode_AppendTail(newNode, zeroListTail);
            
    prevTime0 = event->Time;

    //Add a one priority event
    event = FEL_GenerateRandomArrival(fel,1,prevTime1);
    newNode = ListNode_Create(event);
    oneListTail = ListNode_AppendTail(newNode, zeroListTail);
    prevTime1 = event->Time;
  }

  
  zeroList = ListNode_MergeSortedLists(zeroList, oneList, ListNode_CompEventTimePriority);
  FEL_AddNode(fel, zeroList);

  return fel;
}



FEL* Control_InitializeModeTwo(const char* filename, int* lineNumber)
{
  FILE* file = fopen(filename, "rb");
  FEL* fel;
  Event* event;
  
  //Keep track of the number of each priority that have arrived
  int arrivals0 = 0;
  int arrivals1 = 0;

  //int error = 0; //Whether or not an error has occured

  char buffer[BUFFER_LEN];
  
  int arrivalTime;
  int priority;
  int duration;

  fel = FEL_Create(0,0,0,0,0);

  fgets(buffer, BUFFER_LEN, file);
  while(!feof(file))
  {
    arrivalTime = atoi(strtok(buffer, " "));
    priority = atoi(strtok(NULL, " "));
    duration = atoi(strtok(NULL, "\n"));

    if(priority==0)
    {
      arrivals0++;
    }
    else
    {
      arrivals1++;
    }

    event = Event_Create(ARRIVAL, priority, arrivalTime, duration);
    FEL_AddEvent(fel, event);

    fgets(buffer, BUFFER_LEN, file);
  }
  
  fel -> NumberArrivals[0] = arrivals0;
  fel -> NumberArrivals[1] = arrivals1;
  
  //Cleanup
  fclose(file);

  return fel;
}



Output* Control_Run(FEL* fel)
{
  //Initialize main structures
  SimulationData* simData = SimulationData_Create();
  Server* server = Server_Create(1);
  Queue* queue0 = Queue_Create(0);
  Queue* queue1 = Queue_Create(1);
  Output* output;
  
  //Initialize other variables
  Event* event;
  Event* departure;
  ListNode* node;
  int deltaTime;
  //int cumulativeTime;



  //Main loop
  while(!FEL_IsEmpty(fel))
  {
    //Grab new event
    event = FEL_PopEvent(fel);

    //Collect statistics
    deltaTime = event->Time - simData->CurrentTime;
    simData -> WaitingTime[0] += deltaTime * queue0->Count; 
    simData -> WaitingTime[1] += deltaTime * queue1->Count; 
    simData -> CPUTime += deltaTime*Server_IsBusy(server);
    
    //Now that statistics have been collected, it is safe to advance the time
    simData -> CurrentTime += deltaTime;

    //Handle Event
    if(event->Type == ARRIVAL)
    {
      Queue_AddArrival(queue0, queue1, ListNode_Create(event));
    }
    if(event->Type == DEPARTURE)
    {
      Server_RemoveTask(server, event);
    }
    //Update Queue
    if((!Server_IsBusy(server)))
    {
      if(queue0->Count != 0)
      {
        node = Queue_Pop(queue0);
      }
      else if(queue1->Count != 0)
      {
        node = Queue_Pop(queue1);
      }
      else
      {
        node = NULL;
      }
      if(node != NULL)
      {
        event = ListNode_StripEvent(node); //Can this handle NULL?
        //Add task
        Server_AddTask(server, event); //Can this handle NULL?
        departure = FEL_GenerateDeparture(event, simData -> CurrentTime);
        FEL_AddEvent(fel, departure);
      }
    }

  }

  //Calculate final simulation data values
  float wait0;
  float wait1;
  float queueLength;
  float utilization;

  wait0=SimulationData_AverageWait(simData,0,fel->NumberArrivals[0]);
  wait1=SimulationData_AverageWait(simData,1,fel->NumberArrivals[1]);
  queueLength = SimulationData_AverageQueueLength(simData);
  utilization = SimulationData_Utilization(simData, server->Processors);

  output = Output_Create(wait0, wait1, queueLength, utilization, simData->CurrentTime);

  //Destroy given structures
  SimulationData_Destroy(simData);
  Server_Destroy(server);
  Queue_Destroy(queue0);
  Queue_Destroy(queue1);
  FEL_Destroy(fel);

  //Return simulation informatoin
  return output;
}



Output* Output_Create(float AvgWait0, float AvgWait1, float AvgQueue, float AvgCPU, int EndTime)
{
  Output* output = malloc(sizeof(Output));

  output -> AverageWait0 = AvgWait0;
  output -> AverageWait1 = AvgWait1;
  output -> AverageQueueLength = AvgQueue;
  output -> AverageUtilization = AvgCPU;
  output -> EndTime = EndTime;

  return output;
}



void Output_Destroy(Output* output)
{
  free(output);
}
