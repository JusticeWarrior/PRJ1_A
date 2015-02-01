#include "FEL.h"
#include "ListNode.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
  int i;
  Event* event;
  printf("Adding 10 random arrivals\n");
  FEL* futureList = FEL_Create(100,1,0.03,0.003 );
  for(i=0;i<10;i++)
  {
    FEL_GenerateNewArrival(futureList,i%2,0);
  }

  ListNode_PrintList(futureList->EventList, "Event List");

  for(i=0;i<10;i++)
  {
    printf("Removing first item from the list\n");
    event = FEL_PopEvent(futureList);
    Event_Destroy(event);
    ListNode_PrintList(futureList->EventList, "Event List");
    
  }
  printf("Ending Test\n\n");
  FEL_Destroy(futureList);
  return EXIT_SUCCESS;
}
