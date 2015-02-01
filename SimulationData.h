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
  int WaitingTime0;
  int WaitingTime1;

  //The amount of time units so far, the CPU has spent handling a task
  int CPUTime;
};

//Create a SimulationData structure
SimulationData* SimulationData_Create();

//Destroy a SimulationData structure
void SimulationData_Destroy(SimulationData* data);

#endif /* SIMULATIONDATA_INCLUDED */
