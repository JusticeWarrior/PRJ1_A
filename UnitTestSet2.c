#include "FEL.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
  int i;
  printf("Beginning Test\n");
  FEL* futureList = FEL_Create(100,1,0.03,0.003 );
  for(i=0;i<5;i++)
  {
    FEL_GenerateNewArrival(futureList,i%2,0);
  }
  
  printf("Ending Test\n\n");
  FEL_Destroy(futureList);
  return EXIT_SUCCESS;
}
