#include "FEL.h"
#include "ListNode.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRIVALS 100
#define LAMBDA_ZERO .03
#define LAMBDA_ONE .003
int main(int argc, char** argv)
{
  int i;
  int prevTime0 = 0;
  int prevTime1 = 0;
  Event* event;
  printf("Adding 10 random arrivals\n");
  FEL* futureList = FEL_Create(100,1,LAMBDA_ZERO,LAMBDA_ONE);

  for(i=0;i<ARRIVALS;i++)
  {
    event = FEL_GenerateRandomArrival(futureList,0,prevTime0);
    FEL_AddEvent(futureList, event);
    prevTime0 = event->Time;

    event = FEL_GenerateRandomArrival(futureList,1,prevTime1);
    FEL_AddEvent(futureList, event);
    prevTime1 = event->Time;
  }

  ListNode_PrintList(futureList->EventList, "Event List");

  for(i=0;i<ARRIVALS*2;i++)
  {
    //printf("Removing first item from the list\n");
    event = FEL_PopEvent(futureList);
    Event_Destroy(event);
    //ListNode_PrintList(futureList->EventList, "Event List");
    
  }
  printf("Ending Test\n\n");
  FEL_Destroy(futureList);
  return EXIT_SUCCESS;
}
