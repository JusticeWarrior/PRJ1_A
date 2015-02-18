#include "FEL.h"
#include "SimulationData.h"
#include "Server.h"
#include "ListNode.h"
#include "Control.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "test1.txt"
#define SUBTASKS 5

int main(int argc, char** argv)
{
  //Delarations
  FEL* fel = FEL_Create(1,1,1,1,1);
  ListNode* list = NULL;
  ListNode* list2 = NULL;
  ListNode* tail = NULL;
  ListNode* tail2 = NULL;
  Task* task = Task_Create(SUBTASKS, 1, SUBTASKS);
  Task* task2 = Task_Create(SUBTASKS, 1, SUBTASKS);
  int i; 

  //Generate list and populate FEL with it
  list = ListNode_Create(Event_Create(ARRIVAL,0,0,1,task));
  tail=list;
  for(i=2;i<=SUBTASKS;i++)
  {
    tail = ListNode_AppendTail(ListNode_Create(Event_Create(ARRIVAL,0,0,i,task)),tail);
  }
  
  list2 = ListNode_Create(Event_Create(ARRIVAL,0,1,1,task2));
  tail2=list2;
  for(i=2;i<=SUBTASKS;i++)
  {
    tail2 = ListNode_AppendTail(ListNode_Create(Event_Create(ARRIVAL,0,1,i,task2)),tail2);
  }
  tail ->Next = list2;
  tail2->Next = ListNode_Create(Event_Create(DEPARTURE, 2, 1, 1, task));
  FEL_Append(fel,list);

  //Clean up lists
  list = NULL;
  list2 = NULL;
  
  ListNode_PrintList(fel->EventList, "FEL");

  list = FEL_Pop(fel);
  printf("\nPOP1==============\n");
  ListNode_PrintList(fel->EventList,"FEL");
  ListNode_PrintList(list, "Popped data");
  
  list2 = FEL_Pop(fel);
  printf("\nPOP2==============\n");
  ListNode_PrintList(fel->EventList,"FEL");
  ListNode_PrintList(list2, "Popped data");

  
  tail = FEL_Pop(fel);
  printf("\nPOP3==============\n");
  ListNode_PrintList(fel->EventList,"FEL");
  ListNode_PrintList(tail, "Popped data");

  printf("Ending Test\n\n");

  FEL_Destroy(fel);
  ListNode_DestroyList(list);
  ListNode_DestroyList(list2);
  free(tail->Event);
  free(tail);

  return EXIT_SUCCESS;
}
