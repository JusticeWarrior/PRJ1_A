#ifndef FEL_INCLUDED
#define FEL_INCLUDED 

#include "Server.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"
#include "Event.h"



typedef struct FEL_st{
  int ArrivalsLeft0;
  int ArrivalsLeft1;
  int Lambda0;
  int Lambda1;
  int Mu;
} FEL;

void FEL_GenerateNewArrival(FEL futureEvents, int  priority);

void FEL_GenerateNewDeparture(FEL futureEvents);

void FEL_AddEvent(FEL futureEvents, Event event);

int FEL_isEmpty(FEL futureEvents);

Event* FEL_popEvent(FEL futureEvents);

#endif /* FEL_INCLUDED */
