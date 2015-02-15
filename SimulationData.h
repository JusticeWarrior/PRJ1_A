#ifndef SIMULATIONDATA_INCLUDED
#define SIMULATIONDATA_INCLUDED

#define PRIORITY_LEVELS 2 //The number of prority levels
typedef struct SimulationData_st SimulationData;

#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "ListNode.h"
#include "Server.h"

struct SimulationData_st{
  int CurrentTime; //The current time of the simulation
 
  //The cumulative time spent on the queue for elements of each priority
  int* WaitingTime;

  //The amount of time units so far, the CPU has spent handling a task
  int CPUTime;

  //The cumulative load balancing factor of all of the tasks
  int LoadBalancingFactor;

};

//Create a SimulationData structure
SimulationData* SimulationData_Create();

//Destroy a SimulationData structure
void SimulationData_Destroy(SimulationData* data);

//Calculate the average wait time for jobs of the given priority level, and the
//total number of arrivals in that priority level
float SimulationData_AverageWait(SimulationData* simData, int priority, int arrivals);

//Calculate the average number of objects in the queue
float SimulationData_AverageQueueLength(SimulationData* simData);

//Calculate the average time the CPU has spent busy
float SimulationData_Utilization(SimulationData* simData, int numProcessors);
#endif /* SIMULATIONDATA_INCLUDED */
