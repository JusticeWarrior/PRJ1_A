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
static ListNode* FEL_PopNodes(FEL* futureList, int n);
static void FEL_setRandSeed();


FEL* FEL_Create(int arrivals0, int arrivals1, float mu, float lambda0, float lambda1)
{
  //Allocate structures
  FEL* futureEvents = malloc(sizeof(FEL));
  futureEvents -> Lambda = malloc(sizeof(float)*PRIORITY_LEVELS);
  futureEvents -> NumberArrivals = malloc(sizeof(int)*PRIORITY_LEVELS);

  //Initialize components of structure
  futureEvents -> NumberArrivals[0] = arrivals0;
  futureEvents -> NumberArrivals[1] = arrivals1;

  futureEvents -> Lambda[0] = lambda0;
  futureEvents -> Lambda[1] = lambda1;

  futureEvents -> Mu = mu;
  futureEvents -> EventList = NULL;

  FEL_setRandSeed();

  return futureEvents;
}



void FEL_Destroy(FEL* futureEvents)
{
	if (futureEvents == NULL)
		return;

  ListNode_DestroyList(futureEvents -> EventList);
  free(futureEvents -> NumberArrivals);
  free(futureEvents -> Lambda); 
  free(futureEvents);
}



Event* FEL_GenerateRandomArrival(FEL* futureEvents, int  priority, int previousTime)
{
  int eventTime;                //The time that the new event will occur
  int duration;            //How long this task will spend in the server
  float lambda = futureEvents -> Lambda[priority];
  Event* event;
  if(previousTime < 0)
  {
    eventTime = 0;
  } 
  else
  {
    eventTime = previousTime + expDist(lambda);
  }
  duration = expDist(futureEvents->Mu);
  event = Event_Create(ARRIVAL, priority, eventTime, duration, Task_Create(1, 0, 0));
  
  return event;
}



Event* FEL_GenerateDeparture(Event* arrival, int currentTime)
{
  if(arrival==NULL) {return NULL;} //Protect against NULL events
  Event* event;
  event = Event_Create(DEPARTURE, arrival->Priority, arrival->Duration + currentTime, arrival->Duration, Task_Create(1, 0, 0));
  return event;
}



void FEL_AddEvent(FEL* futureEvents, Event* event)
{  
  ListNode* node = ListNode_Create(event);
  futureEvents->EventList = ListNode_InsertSorted(node, futureEvents->EventList, ListNode_CompEventTimePriority);
}

void FEL_Append(FEL* fel, ListNode* node)
{
  ListNode* end; //Find the end of the list
  end = fel->EventList;
  if (end == NULL) //If the EventList is empty
  {
    fel->EventList = node;
  }
  else
  {
    while(end->Next != NULL)
    {
      end = end->Next;
    }
    end->Next = NULL;
  }
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

	ListNode* poppedNode = FEL_PopNodes(futureEvents,1);
	Event* event = ListNode_StripEvent(poppedNode);

	return event;
}


ListNode* FEL_Pop(FEL* fel)
{
  ListNode* node;
  if(fel -> EventList -> Event -> Type == DEPARTURE)
  {
    node = FEL_PopNodes(fel, 1);
  }
  else
  {
    node = FEL_PopNodes(fel,fel->EventList->Event->Task->SubTasks);
  }
  return node;
}

void FEL_InsertUnsorted(FEL* fel, ListNode* list)
{
  return;
}

static int expDist(float constant)
{
  //A uniformly distributed random float
  float uniform = (1 - ((float)rand())/((float)RAND_MAX + 1));
  return((int)ceil(-log(uniform)/constant));
}

ListNode* FEL_PopNodes(FEL* futureList, int n)
{
  int i=1;
  ListNode* poppedNodes = futureList -> EventList;
  ListNode* tail = poppedNodes;

  while(i!=n && tail!=NULL)
  {
    i++;
    tail=tail->Next;
  }
  if(tail==NULL)
  {
    futureList->EventList=NULL;
  }
  else
  {
    futureList->EventList = tail->Next;
    tail->Next=NULL;
  }
  return poppedNodes;
}



void FEL_GenerateAndAddDepartures(FEL* fel, ListNode* subTasks, int currentTime)
{
  
}


float FEL_AverageEventDuration(FEL* futureEvents)
{
	ListNode* head = futureEvents->EventList;
	int count = ListNode_GetLength(head);

	if (count == 0)
		return 0.0;

	int totalTime = 0;
	while (head != NULL)
	{
		totalTime += head->Event->Duration;
		head = head->Next;
	}

	return (float)totalTime / (float)count;
}

// Sets the rand() seed value to the current time.
static void FEL_setRandSeed()
{
	srand((unsigned int)time(NULL));
}
