#include "FEL.h"

/*
struct FEL_st{
  int* ArrivalsLeft;
  int* Lambda;
  int Mu;
  ListNode* EventList;
};
*/



//This function will return a random exponentially distributed variable
static int expDist(float constant);
static ListNode* FEL_PopNode(FEL* futureList);

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
	if (futureEvents == NULL)
		return;

  ListNode_DestroyList(futureEvents -> EventList);
  free(futureEvents -> ArrivalsLeft);
  free(futureEvents -> Lambda); 
}



void FEL_GenerateNewArrival(FEL* futureEvents, int  priority, int currentTime)
{
  int time = currentTime; //The time that the new event will occur
  float lambda = futureEvents -> Lambda[priority];
  Event* event;
  
  //If there are still some events of that priority level that need to arrive
  if(futureEvents -> ArrivalsLeft[priority] != 0)
  {
    futureEvents -> ArrivalsLeft[priority]--;
    time += expDist(lambda);
    event = Event_Create(ARRIVAL, priority, time);
    FEL_AddEvent(futureEvents, event); 
  }
}



void FEL_GenerateNewDeparture(FEL* futureEvents, int currentTime)
{ 
  int time = currentTime; //The time that the new event will occur
  float mu = futureEvents -> Mu;
  Event* event;

  time += (int)ceil(-(log(1 - (((float)rand()+1))/RAND_MAX)) / (mu));
  event = Event_Create(DEPARTURE, 12345, time);

  FEL_AddEvent(futureEvents, event); 
}



void FEL_AddEvent(FEL* futureEvents, Event* event)
{  
  ListNode* node = ListNode_Create(event);
  futureEvents -> EventList = ListNode_InsertSorted(node, futureEvents -> EventList, ListNode_CompEventTime);
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
	if (futureEvents->EventList == NULL)
		return NULL;

	ListNode* poppedNode = FEL_PopNode(futureEvents);
	Event* event = ListNode_StripEvent(poppedNode);

	return event;
}



static int expDist(float constant)
{
  //A uniformly distributed random float
  float uniform = (1 - ((float)rand())/RAND_MAX);
  return((int)ceil(-log(uniform)/constant));
}

ListNode* FEL_PopNode(FEL* futureList)
{
	if (futureList->EventList == NULL)
		return NULL;
  ListNode* poppedNode = futureList->EventList;
  futureList->EventList = ListNode_PopHead(futureList->EventList);
  return poppedNode;
}
