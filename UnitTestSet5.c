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
  int time=0;
  FEL* fel = FEL_Create(2,2, 0.009, 0.01, 0.01);
  ListNode* randTask;
  ListNode* taskList=NULL;
  ListNode* taskListTail=NULL;
  randTask = FEL_GenerateRandomTask(fel, 0, time);
  //time = randTask->Event->Time;

  taskList = randTask;
  //taskListTail = ListNode_AppendTail(randTask, taskListTail);

  //randTask = FEL_GenerateRandomTask(fel, 0, time);
  //taskListTail=ListNode_AppendTail(randTask, taskListTail);
  
  

  ListNode_PrintList(taskList, "SubTasks");
  printf("NumSubTasks: %d\n",randTask->Event->Task->SubTasks);
  printf("Min Duration: %d\n",randTask->Event->Task->MinDuration);
  printf("Max Duration: %d\n",randTask->Event->Task->MaxDuration);
  return EXIT_SUCCESS;
}
