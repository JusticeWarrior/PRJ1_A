#include "SimulationData.h"


SimulationData* SimulationData_Create()
{
  SimulationData* simData = malloc(sizeof(SimulationData));
  simData -> WaitingTime = malloc(sizeof(int)*PRIORITY_LEVELS);

  simData -> CPUTime = 0;
  simData -> CurrentTime = 0; 
 
  return simData;
}



void SimulationData_Destroy(SimulationData* simData)
{
  free(simData -> WaitingTime);
  free(simData);
}

float SimulationData_AverageWait(SimulationData* simData, int priority)
{
  float wait = simData -> WaitingTime[priority];
  float average = wait / ((float)(simData->CurrentTime) );
  return average;  
}

float SimulationData_Utilization(SimulationData* simData)
{
  float cpu = simData -> CPUTime;
  float average = cpu / ((float)(simData->CurrentTime));
  return average;  
}
