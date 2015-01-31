#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "Server.h"
#include "ListNode.h"

#ifndef SIMULATIONDATA_INCLUDED
#define SIMULATIONDATA_INLCUDED 

typedef Struct SimulationData_st{
  int CurrentTime;
  int WaitingTime0;
  int WaitingTime1;
  int CPUTime;
} SimulationData;

#endif /* SIMULATIONDATA_INCLUDED */
