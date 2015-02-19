#include "FEL.h"
#include "SimulationData.h"
#include "Server.h"
#include "ListNode.h"
#include "Control.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input1.txt"

int main(int argc, char** argv)
{
  int linenumber;
  FEL* fel = Control_InitializeModeTwo(INPUT_FILE, &linenumber);
  ListNode_PrintList(fel->EventList, "SubTaskArrivals");
  printf("Load Balancing Factor is: %f", fel->LBF);
  return EXIT_SUCCESS;
}
