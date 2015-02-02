#include "FEL.h"
#include "SimulationData.h"
#include "Server.h"
#include "ListNode.h"
#include "Control.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRIVALS 100
#define LAMBDA_ZERO .03
#define LAMBDA_ONE .003
#define MU .05
int main(int argc, char** argv)
{
  int i;
  Event* event;
  FEL* fel = Control_InitializeModeOne(LAMBDA_ZERO,LAMBDA_ONE,MU,ARRIVALS);

  float avgDuration = FEL_AverageEventDuration(fel);

  ListNode_PrintList(fel->EventList, "Event List");

  for(i=0;i<ARRIVALS*2;i++)
  {
    //printf("Removing first item from the list\n");
    event = FEL_PopEvent(fel);
    Event_Destroy(event);
    //ListNode_PrintList(futureList->EventList, "Event List");
    
  }

  fprintf(stdout, "Average Event Duration is: %f\n", avgDuration);

  printf("Ending Test\n\n");
  FEL_Destroy(fel);
  return EXIT_SUCCESS;
}
