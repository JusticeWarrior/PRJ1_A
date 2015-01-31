#ifndef FEL_INCLUDED
#define FEL_INCLUDED 

typedef struct FEL_st FEL;

#include "Event.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"
#include "Server.h"
#include <math.h>
#include <stdlib.h>

struct FEL_st{
  int ArrivalsLeft0;
  int ArrivalsLeft1;
  int Lambda0;
  int Lambda1;
  int Mu;
  ListNode* EventList;
};

FEL* FEL_Create(int TotalArrivals, int Lambda0, int Lambda1, int mu);

void FEL_Destroy(FEL* FutureEvents);

void FEL_GenerateNewArrival(FEL* futureEvents, int  priority);

void FEL_GenerateNewDeparture(FEL* futureEvents);

void FEL_AddEvent(FEL* futureEvents, Event* event);

int FEL_IsEmpty(FEL* futureEvents);

Event* FEL_popEvent(FEL* futureEvents);

#endif /* FEL_INCLUDED */
