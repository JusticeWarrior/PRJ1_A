#include "SimulationData.h"


SimulationData* SimulationData_Create()
{
  SimulationData* simData = malloc(sizeof(SimulationData));
  simData -> WaitingTime = malloc(sizeof(int)*PRIORITY_LEVELS);
  
  simData -> WaitingTime[0] = 0;
  simData -> WaitingTime[1] = 0;
  simData -> CPUTime = 0;
  simData -> CurrentTime = 0; 
  simData -> LoadBalancingFactor=0; 
  return simData;
}



void SimulationData_Destroy(SimulationData* simData)
{
  free(simData -> WaitingTime);
  free(simData);
}

float SimulationData_AverageWait(SimulationData* simData, int priority, int arrivals)
{
  float wait = (float)(simData -> WaitingTime[priority]);
  float average = wait / ((float)arrivals);
  return average;
}



float SimulationData_AverageQueueLength(SimulationData* simData)
{
  float length=0;
  int i;

  for(i=0;i<PRIORITY_LEVELS;i++)
  {
    length += (float)(simData->WaitingTime[i]);
  }
  return (length/((float)(simData->CurrentTime)));
}
 


float SimulationData_Utilization(SimulationData* simData, int processors)
{
  float cpu = (float)simData -> CPUTime;
  float average = cpu / ((float)(simData->CurrentTime)) / ((float)processors);
  return average;  
}


float SimulationData_AverageLoadBalancing(SimulationData* simData, int arrivals)
{
  float balancing = (float)simData -> LoadBalancingFactor;
  float average = balancing / ((float)arrivals);
  return average;
}
