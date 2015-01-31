#include "FEL.h"

/*
struct FEL_st{
  int ArrivalsLeft0;
  int ArrivalsLeft1;
  int Lambda0;
  int Lambda1;
  int Mu;
  ListNode* EventList;
};
*/

FEL* FEL_Create(int totalArrivals, int lambda0, int lambda1, int mu)
{
  FEL* futureEvents = malloc(sizeof(FEL));
  futureEvents -> ArrivalsLeft0 = totalArrivals;
  futureEvents -> ArrivalsLeft1 = totalArrivals;
  futureEvents -> Lambda0 = lambda0;
  futureEvents -> Lambda1 = lambda1;
  futureEvents -> Mu = mu;
  futureEvents -> EventList = NULL;
  return futureEvents;
}

void FEL_Destroy(FEL* futureEvents)
{
  //EventList_Destroy(futureEvents_EventList);
  free(futureEvents);
}

void FEL_GenerateNewArrival(FEL* futureEvents, int  priority);

void FEL_GenerateNewDeparture(FEL* futureEvents);

void FEL_AddEvent(FEL* futureEvents, Event* event);

int FEL_IsEmpty(FEL* futureEvents);

Event* FEL_popEvent(FEL* futureEvents);
