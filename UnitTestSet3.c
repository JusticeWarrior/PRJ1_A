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
  int i;
  Event* event;
  int lineNumber;
  FEL* fel = Control_InitializeModeTwo(INPUT_FILE, &lineNumber);

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
