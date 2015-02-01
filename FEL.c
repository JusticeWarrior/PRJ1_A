#include "FEL.h"

/*
struct FEL_st{
  int* ArrivalsLeft;
  int* Lambda;
  int Mu;
  ListNode* EventList;
};
*/

//ListNode* ListNode_InsertSorted(ListNode* node, ListNode* listHead, int (*compFunc)(ListNode*, ListNode*))

static int eventComp(ListNode* nodeA, ListNode* nodeB);

FEL* FEL_Create(int totalArrivals, float mu, float lambda0, float lambda1)
{
  //Allocate structures
  FEL* futureEvents = malloc(sizeof(FEL));
  futureEvents -> Lambda = malloc(sizeof(float)*PRIORITY_LEVELS);
  futureEvents -> ArrivalsLeft = malloc(sizeof(float)*PRIORITY_LEVELS);

  //Initialize components of structure
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
  free(futureEvents -> ArrivalsLeft);
  free(futureEvents -> Lambda); 
}



void FEL_GenerateNewArrival(FEL* futureEvents, int  priority, int currentTime)
{
  float time = currentTime; //The time that the new event will occur
  float lambda = futureEvents -> Lambda[priority];
  Event* event;
  
  //If there are still some events of that priority level that need to arrive
  if(futureEvents -> ArrivalsLeft[priority] != 0)
  {
    futureEvents -> ArrivalsLeft[priority]--;
    time += - ceil((log(1 - rand())) / (lambda));
    event = Event_Create(ARRIVAL, priority, time);
    FEL_AddEvent(futureEvents, event); 
  }
}



void FEL_GenerateNewDeparture(FEL* futureEvents, int currentTime)
{ 
  float time = currentTime; //The time that the new event will occur
  float mu = futureEvents -> Mu;
  Event* event;

  time += - ceil((log(1 - rand())) / (mu));
  event = Event_Create(DEPARTURE, 12345, time);

  FEL_AddEvent(futureEvents, event); 
}



void FEL_AddEvent(FEL* futureEvents, Event* event)
{  
  ListNode* node = ListNode_Create(event);
  ListNode_InsertSorted(node, futureEvents -> EventList, eventComp);
}



int FEL_IsEmpty(FEL* futureEvents)
{
  if(futureEvents->EventList == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}



Event* FEL_PopEvent(FEL* futureEvents)
{
  ListNode* node = ListNode_PopHead(futureEvents -> EventList);
  Event* event = node->Event;
  free(node);  //The destroy function should not becalled because it will free the event as well
  return event;
}



static int eventComp(ListNode* nodeA, ListNode* nodeB)
{
  return (nodeB -> Event -> Time) - (nodeB -> Event -> Time);
}
