#include "Control.h"
#define BUFFER_LEN 1000

//Return a 1 if both events are departures and occur at the same time
static int departSameTime(ListNode* a, ListNode* b);
  
FEL* Control_InitializeModeOne(float lambda0, float lambda1, float mu, int numTasks)
{
  FEL* fel = FEL_Create(numTasks, numTasks, mu, lambda0, lambda1);
  ListNode* newNode;

  float lbf = 0; //cumulative load balancing factor

  ListNode* zeroList; //A list of all of the zero arrivals
  ListNode* oneList;  //A list of all of the one arrivals

  ListNode* zeroListTail=NULL;  //Keep track of the tail of the lists
  ListNode* oneListTail=NULL;

  int prevTime0 = -1;
  int prevTime1 = -1;
  int i;

  //Initialize the FEL, calculate load balancing factor 
  zeroList = FEL_GenerateRandomTask(fel, 0, prevTime0);
  zeroListTail = ListNode_AppendTail(zeroList, NULL); //Find tail of list 
  prevTime0 = zeroList->Event->Time;
  lbf += (zeroList->Event->Task->MaxDuration - zeroList->Event->Task->MinDuration)*fel->Mu;

  oneList = FEL_GenerateRandomTask(fel, 1, prevTime1);
  oneListTail = ListNode_AppendTail(oneList, NULL); //Find tail of list 
  prevTime1 = oneList->Event->Time;
  lbf += (oneList->Event->Task->MaxDuration - oneList->Event->Task->MinDuration)*fel->Mu;
  
  for(i=1;i<numTasks;i++)
  {
    //Add a zero priority event
    newNode = FEL_GenerateRandomTask(fel,0,prevTime0);
    zeroListTail = ListNode_AppendTail(newNode, zeroListTail);
    prevTime0 = newNode->Event->Time;
    lbf += (newNode->Event->Task->MaxDuration - newNode->Event->Task->MinDuration)*fel->Mu;


    //Add a one priority event 
    newNode = FEL_GenerateRandomTask(fel,1,prevTime1);
    oneListTail = ListNode_AppendTail(newNode, oneListTail);
    prevTime1 = newNode->Event->Time;
    lbf += (newNode->Event->Task->MaxDuration - newNode->Event->Task->MinDuration)*fel->Mu;

  }

  
  zeroList = ListNode_MergeSortedLists(zeroList, oneList, ListNode_CompEventTimePriority);
  FEL_Append(fel, zeroList);
  
  lbf /= numTasks*2;
  fel->LBF = lbf;
  return fel;
}



FEL* Control_InitializeModeTwo(const char* filename, int* lineNumber)
{
  FILE* file = fopen(filename, "rb");
  FEL* fel;
  
  //Keep track of the number of each priority that have arrived
  int arrivals0 = 0;
  int arrivals1 = 0;
  int subTaskTotal=0;
  float cumuDuration=0; //Cumulative duration of all subtasks
  float cumuMax=0;      //Cumulative max duration of all tasks
  float cumuMin=0;      //Cumulative min duration of all tasks


  //int error = 0; //Whether or not an error has occured

  char buffer[BUFFER_LEN];
  char* token;
  Task* task;
  int arrivalTime;
  int priority;
  int duration;

  ListNode* taskHead; //The head of the task currently being built
  ListNode* taskTail; //The tail of hte task currently being built

  //Pointers to hold the head and tail of all of the tasks
  ListNode* zeroListHead;
  ListNode* zeroListTail;
  ListNode* oneListHead;
  ListNode* oneListTail;

  fel = FEL_Create(0,0,0,0,0);

  //Iterate through each line of the file and generate a task for each line
  fgets(buffer, BUFFER_LEN, file);
  while(!feof(file))
  {
    taskHead=NULL;
    taskTail=NULL;
    task = Task_Create(0,-1,0);
    arrivalTime = atoi(strtok(buffer, " "));
    priority = atoi(strtok(NULL, " "));

    //Do first subtask (there will always be at least one)
    duration = atoi(strtok(NULL, "\n "));
    taskHead = ListNode_Create(Event_Create(ARRIVAL, priority, arrivalTime, duration, task));
    taskTail = taskHead;

    //Collect statistics
    task->MinDuration = duration;
    task->MaxDuration = duration;
    cumuDuration += duration;
    subTaskTotal++;
    task -> SubTasks++;


    token = strtok(NULL, "\n ");
    while(token != NULL)
    {
      //Add Subtask to list
      duration = atoi(token);
      taskTail->Next = ListNode_Create(Event_Create(ARRIVAL, priority, arrivalTime, duration, task));
      taskTail = taskTail->Next;
      
      //Collect statistics
      cumuDuration += duration;
      subTaskTotal++;
      if(duration > task->MaxDuration)
        task->MaxDuration = duration;
      if(duration < task->MinDuration)
        task->MinDuration = duration;
      task -> SubTasks++;
      
      token = strtok(NULL, "\n ");
    }
    //Add to global statistics
    cumuMax += task -> MaxDuration;
    cumuMin += task -> MinDuration;

    if(priority==0)
    {
      if(arrivals0==0)
      {
        zeroListHead = taskHead;
        zeroListTail = taskTail;
      }
      else
      {
        zeroListTail = ListNode_AppendTail(taskHead, zeroListTail);
      }
      arrivals0++;
    }
    else
    {
      if(arrivals1==0)
      {
        oneListHead = taskHead;
        oneListTail = taskTail;
      }
      else
      {
        oneListTail = ListNode_AppendTail(taskHead, oneListTail);
      }
      arrivals1++;
    }
    fgets(buffer, BUFFER_LEN, file);
  }


  zeroListHead = ListNode_MergeSortedLists(zeroListHead, oneListHead, ListNode_CompEventTimePriority);

  FEL_Append(fel, zeroListHead);  
  fel -> NumberArrivals[0] = arrivals0;
  fel -> NumberArrivals[1] = arrivals1;
  fel -> LBF = (cumuMax-cumuMin)/(cumuDuration/subTaskTotal)/(arrivals0+arrivals1);

  //Cleanup
  fclose(file);

  return fel;
}



Output* Control_Run(FEL* fel)
{
  //Initialize main structures
  SimulationData* simData = SimulationData_Create();
  Server* server = Server_Create(64);
  Queue* queue0 = Queue_Create(0);
  Queue* queue1 = Queue_Create(1);
  Output* output;
  
  //Initialize other variables
  int iterateInput=1;
  ListNode* event;
  ListNode* node;
  int deltaTime;
  //int cumulativeTime;



  //Main loop
  while(!FEL_IsEmpty(fel))
  {
    while(iterateInput)
    {
      //Grab new event
      event = FEL_Pop(fel);

      //Determine if another event needs to be popped as well
      iterateInput = departSameTime(event, fel->EventList);

      //Collect statistics
      deltaTime = event->Event->Time - simData->CurrentTime;
      simData -> WaitingTime[0] += deltaTime * queue0->NumTasks; 
      simData -> WaitingTime[1] += deltaTime * queue1->NumTasks; 
      simData -> CPUTime += deltaTime*(server->Processors - server->Available);
      if(deltaTime!=0)
      {
        printf("DeltaT: %4d, Used cores: %4d, Cumulative: %4d\n", deltaTime, server->Processors - server->Available, simData->CPUTime);
        printf("Queue 0: %4d, Queue1:%4d\n\n",queue0->Count, queue1->Count);
      }
      
      
      //Now that statistics have been collected, it is safe to advance the time
      simData -> CurrentTime += deltaTime;
  
      //Handle Event
      if(event->Event->Type == ARRIVAL)
      {
        //Collect Arrival related stats
        simData->QueueLength += queue0->NumTasks + queue1->NumTasks;

        //Add Arrival to correct queue
        Queue_SortTask(queue0, queue1, event);
      }
      if(event->Event->Type == DEPARTURE)
      {
        //Remove subtask from server
        Server_RemoveSubTask(server, event);
      }
    }
    //Update Queue
    do
    {
      node = Queue_ScanQueues(queue0, queue1, server->Available);

      if(node != NULL)
      {
        FEL_GenerateAndAddDepartures(fel, node, simData->CurrentTime);
        Server_AddTask(server, node);
      }
    }while(node!=NULL);
    iterateInput=1;
  }

  //Calculate final simulation data values
  float wait0;
  float wait1;
  float queueLength;
  float utilization;
  float balancing;

  wait0=SimulationData_AverageWait(simData,0,fel->NumberArrivals[0]);
  wait1=SimulationData_AverageWait(simData,1,fel->NumberArrivals[1]);
  queueLength = SimulationData_AverageQueueLength(simData, fel->NumberArrivals[0] + fel->NumberArrivals[1]);
  utilization = SimulationData_Utilization(simData, server->Processors);
  balancing = fel -> LBF;

  output = Output_Create(wait0, wait1, queueLength, utilization, balancing, simData->CurrentTime);

  //Destroy given structures
  SimulationData_Destroy(simData);
  Server_Destroy(server);
  Queue_Destroy(queue0);
  Queue_Destroy(queue1);
  FEL_Destroy(fel);

  //Return simulation informatoin
  return output;
}



Output* Output_Create(float AvgWait0, float AvgWait1, float AvgQueue, float AvgCPU, float AvgLoadBalancing, int EndTime)
{
  Output* output = malloc(sizeof(Output));

  output -> AverageWait0 = AvgWait0;
  output -> AverageWait1 = AvgWait1;
  output -> AverageQueueLength = AvgQueue;
  output -> AverageUtilization = AvgCPU;
  output -> AverageLoadBalancingFactor = AvgLoadBalancing;
  output -> EndTime = EndTime;

  return output;
}



void Output_Destroy(Output* output)
{
  free(output);
}

static int departSameTime(ListNode* a, ListNode* b)
{
  if(a==NULL || b==NULL)
  {
    return 0;
  }
  if(a->Event->Type!=DEPARTURE || b->Event->Type!=DEPARTURE)
  {
    return 0;
  }
  if(a->Event->Time != b->Event->Time)
  {
    return 0;
  }
  return 1;
}
