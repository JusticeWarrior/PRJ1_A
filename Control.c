#include "Control.h"

  
FEL* Control_InitializeModeOne(float lambda0, float lambda1, float mu, int numTasks)
{
  FEL* fel = FEL_Create(numTasks, mu, lambda0, lambda1);
  Event* event;

  //First, add two arrivals a t=0;

}



FEL* Control_InitializeModeTwo(const char* filename, int* lineNumber)
{

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
