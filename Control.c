#include "Control.h"

  
FEL* Control_InitializeModeOne(float lambda0, float lambda1, float mu, int numTasks)
{
  FEL* fel = FEL_Create(numTasks, mu, lambda0, lambda1);
  Event* event;
  int prevTime0 = -1;
  int prevTime1 = -1;
  int i;

  //Initialize the FEL EventList
  for(i=0;i<numTasks;i++)
  {
    //Add a zero priority event
    event = FEL_GenerateRandomArrival(fel,0,prevTime0);
    FEL_AddEvent(fel,event);
    prevTime0 = event->Time;

    //Add a one priority event
    event = FEL_GenerateRandomArrival(fel,1,prevTime1);
    FEL_AddEvent(fel,event);
    prevTime1 = event->Time;
  }

  return fel;
}



FEL* Control_InitializeModeTwo(const char* filename, int* lineNumber)
{
  FILE* file = fopen(filename, "rb");
  FEL* fel;
  Event* event;
  int error = 0; //Whether or not an error has occured
  char* line;
  char* token;

  
  
  return NULL;
}



Output* Control_Run(FEL* fel)
{

  return NULL;
}



Output* Output_Create(float AvgWait0, float AvgWait1, float AvgQueue, float AvgCPU)
{
  Output* output = malloc(sizeof(Output));

  output -> AverageWait0 = AvgWait0;
  output -> AverageWait1 = AvgWait1;
  output -> AverageQueueLength = AvgQueue;
  output -> AverageUtilization = AvgCPU;

  return output;
}



void Output_Destroy(Output* output)
{
  free(output);
}
