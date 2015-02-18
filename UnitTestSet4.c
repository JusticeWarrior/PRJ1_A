#include "FEL.h"
#include "SimulationData.h"
#include "Server.h"
#include "ListNode.h"
#include "Control.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "test1.txt"

int main(int argc, char** argv)
{
  FEL* fel = FEL_Create(1,1,1,1,1);
  ListNode* list = NULL;
  ListNode* tail = NULL
  Task* task = Task_Create(3, 1, 3);
  
  list = ListNode_Create(Event_Create(ARRIVAL,0,0,1,task));
  tail = ListNode_AppendTail(ListNode_Create(Event_Create(Arrival,0,0,2,task)),list);
   tail = ListNode_AppendTail(ListNode_Create(Event_Create(Arrival,0,0,3,task)),tail);
  ListNode_PrintList(tail, "DebugList");  

  ListNode_PrintList(fel->EventList, "Event List");

  for(i=0;i<8;i++)
  {
    //printf("Removing first item from the list\n");
    event = FEL_PopEvent(fel);
    Event_Destroy(event);
    //ListNode_PrintList(futureList->EventList, "Event List");
    
  }
  printf("Ending Test\n\n");
  FEL_Destroy(fel);
  return EXIT_SUCCESS;
}
