#ifndef SIMULATIONDATA_INCLUDED
#define SIMULATIONDATA_INCLUDED 
#include "FEL.h"
#include "Queue.h"
#include "Server.h"
#include "ListNode.h"
#include "Event.h"

typedef struct SimulationData_st{
  int CurrentTime;
  int WaitingTime0;
  int WaitingTime1;
  int CPUTime;
} SimulationData;

#endif /* SIMULATIONDATA_INCLUDED */
