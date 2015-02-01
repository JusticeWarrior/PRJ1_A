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

FEL* FEL_Create(int totalArrivals, int mu, int lambda0, int lambda1)
{
  FEL* futureEvents = malloc(sizeof(FEL));
  futureEvents -> Lambda = malloc(sizeof(int)*PRIORITY_LEVELS);
  futureEvents -> ArrivalsLeft = malloc(sizeof(int)*PRIORITY_LEVELS);

  futureEvents -> ArrivalsLeft[0] = totalArrivals;
  futureEvents -> ArrivalsLeft[1] = totalArrivals;
  futureEvents -> Lambda[0] = lambda0;
  futureEvents -> Lambda[1] = lambda1;
  futureEvents -> Mu = mu;
  futureEvents -> EventList = NULL;

  return futureEvents;
}

void FEL_Destroy(FEL* futureEvents)
{
  ListNode_DestroyList(futureEvents -> EventList);
  free(futureEvents); 
}

void FEL_GenerateNewArrival(FEL* futureEvents, int  priority, int currentTime)
{
  int time = currentTime; //The time that the new event will occur
  Event* event;

  
  event = Event_Create(ARRIVAL, priority, time);
  

}

void FEL_GenerateNewDeparture(FEL* futureEvents);

void FEL_AddEvent(FEL* futureEvents, Event* event);

int FEL_IsEmpty(FEL* futureEvents);

Event* FEL_popEvent(FEL* futureEvents);
