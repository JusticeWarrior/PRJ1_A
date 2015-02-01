#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"
#include "Server.h"

#include <stdio.h>
#include <stdlib.h>

#define ERRORLAMBDA0 0
#define ERRORLAMBDA1 1
#define ERRORMU 2
#define ERRORNUMTASKS 3
#define ERRORTOOMANYARGS 4
#define ERRORTOOFEWARGS 5
#define ERRORCANTFINDFILE 6

typedef struct Args_st{
	float* Lambda0;
	float* Lambda1;
	float Mu;
	int NumTasks;
	char* FileName;
} Args;

static Args* parseArgs(char ** args, int numArgs)
{


	return NULL;
}

int main(int argc, char** argv)
{


	printf("\nWoo!\n");
	return EXIT_SUCCESS;
}