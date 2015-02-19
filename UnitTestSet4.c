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
  FEL* fel = FEL_Create(1,1,99999,1,1);
  Server* server = Server_Create(10);
  ListNode* list = NULL;
  ListNode* list2 = NULL;
  ListNode* tail = NULL;
  ListNode* tail2 = NULL;
  Task* task = Task_Create(SUBTASKS, 1, SUBTASKS);
  Task* task2 = Task_Create(SUBTASKS, 1, SUBTASKS);
  int i;
  int x;

  //Generate list and populate FEL with it
  list = ListNode_Create(Event_Create(ARRIVAL,0,0,11,task));
  tail=list;
  for(i=2;i<=SUBTASKS;i++)
  {
    tail = ListNode_AppendTail(ListNode_Create(Event_Create(ARRIVAL,0,0,i+10,task)),tail);
  }
  
  list2 = ListNode_Create(Event_Create(ARRIVAL,0,1,11,task2));
  tail2=list2;
  for(i=2;i<=SUBTASKS;i++)
  {
    tail2 = ListNode_AppendTail(ListNode_Create(Event_Create(ARRIVAL,0,1,i+10,task2)),tail2);
  }
  tail ->Next = list2;
  FEL_Append(fel,list);

  //Clean up lists
  list = NULL;
  list2 = NULL;
  
  ListNode_PrintList(fel->EventList, "FEL");
  Server_PrintState(server);
  scanf("%d",&x);

  printf("\nPOP1==============\n");
  list = FEL_Pop(fel);
  FEL_GenerateAndAddDepartures(fel, list, 0);
  Server_AddTask(server, list);

  ListNode_PrintList(fel->EventList,"FEL");
  Server_PrintState(server);
  scanf("%d", &x);
  
  printf("\nPOP2==============\n");
  list2 = FEL_Pop(fel); 
  FEL_GenerateAndAddDepartures(fel, list2, 0);
  Server_AddTask(server,list2);

  ListNode_PrintList(fel->EventList,"FEL");
  Server_PrintState(server);
  scanf("%d", &x);
  
  while(FEL_IsEmpty(fel)!=1)
  {
    list = FEL_Pop(fel);
    Server_RemoveSubTask(server, list);
    ListNode_PrintList(fel->EventList,"FEL");
    Server_PrintState(server);
    scanf("%d", &x);
  }
  
 // tail = FEL_Pop(fel);
 // printf("\nPOP3==============\n");
 // ListNode_PrintList(fel->EventList,"FEL");
 // ListNode_PrintList(tail, "Popped data");



  printf("Ending Test\n\n");

  FEL_Destroy(fel);
  Server_Destroy(server);
  return EXIT_SUCCESS;
}
