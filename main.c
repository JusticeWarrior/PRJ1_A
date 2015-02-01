#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"
#include "Server.h"

#include <stdio.h>
#include <stdlib.h>

#define ERRORNONE -1
#define ERRORLAMBDA0 0
#define ERRORLAMBDA1 1
#define ERRORMU 2
#define ERRORNUMTASKS 3
#define ERRORTOOMANYARGS 4
#define ERRORTOOFEWARGS 5
#define ERRORINCORRECTNUMARGS 6
#define ERRORCANTFINDFILE 7
#define NUMARGSMODE1 5
#define NUMARGSMODE2 2

typedef struct Args_st{
	float* Lambda0;
	float* Lambda1;
	float Mu;
	int NumTasks;
	char* FileName;
	int Error;
} Args;

static Args* parseArgs(char ** args, int numArgs)
{
	Args* parsedArgs = malloc(sizeof(Args));
	
	if (numArgs > NUMARGSMODE1)
	{
		parsedArgs->Error = ERRORTOOMANYARGS;
		return parsedArgs;
	}

	if (numArgs < NUMARGSMODE2)
	{
		parsedArgs->Error = ERRORTOOFEWARGS;
		return parsedArgs;
	}

	if (numArgs > NUMARGSMODE2 && numArgs < NUMARGSMODE1)
	{
		parsedArgs->Error = ERRORINCORRECTNUMARGS;
		return parsedArgs;
	}

	if (numArgs == NUMARGSMODE2)
	{
		FILE* file = fopen(args[1], "rb");
		if (file == NULL)
		{
			parsedArgs->Error = ERRORCANTFINDFILE;
			return parsedArgs;
		}
	}

	return parsedArgs;
}

int main(int argc, char** argv)
{


	printf("\nWoo!\n");
	return EXIT_SUCCESS;
}