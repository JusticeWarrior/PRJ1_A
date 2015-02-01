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
	float Lambda0;
	float Lambda1;
	float Mu;
	int NumTasks;
	char* FileName;
	int Error;
} Args;

// Parses the arguments given and assigns errors as necessary. Does not duplicate strings,
// so make sure that the strings are not popped from the call stack.
static Args* parseArgs(char ** args, int numArgs)
{
	Args* parsedArgs = malloc(sizeof(Args));
	parsedArgs->Error = ERRORNONE;
	parsedArgs->FileName = NULL;
	parsedArgs->Lambda0 = 0;
	parsedArgs->Lambda1 = 0;
	parsedArgs->Mu = 0;
	parsedArgs->NumTasks = 0;
	
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

		parsedArgs->FileName = args[1];
	}

	if (numArgs == NUMARGSMODE1)
	{
		float lambda0 = (float)atof(args[1]);
		if (lambda0 == 0.0)
		{
			parsedArgs->Error = ERRORLAMBDA0;
			return parsedArgs;
		}
		parsedArgs->Lambda0 = lambda0;

		float lambda1 = (float)atof(args[2]);
		if (lambda1 == 0.0)
		{
			parsedArgs->Error = ERRORLAMBDA1;
			return parsedArgs;
		}
		parsedArgs->Lambda1 = lambda1;

		float mu = (float)atof(args[3]);
		if (mu == 0.0)
		{
			parsedArgs->Error = ERRORMU;
			return parsedArgs;
		}
		parsedArgs->Mu = mu;

		int numTasks = atoi(args[4]);
		if (numTasks == 0)
		{
			parsedArgs->Error = ERRORNUMTASKS;
			return parsedArgs;
		}
		parsedArgs->NumTasks = numTasks;
	}

	return parsedArgs;
}

int main(int argc, char** argv)
{


	printf("\nWoo!\n");
	return EXIT_SUCCESS;
}