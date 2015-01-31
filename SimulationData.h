#ifndef SIMULATIONDATA_INCLUDED
#define SIMULATIONDATA_INCLUDED

typedef struct SimulationData_st SimulationData;

#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "ListNode.h"
#include "Server.h"

struct SimulationData_st{
  int CurrentTime;
  int WaitingTime0;
  int WaitingTime1;
  int CPUTime;
};

#endif /* SIMULATIONDATA_INCLUDED */
