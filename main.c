#include "FEL.h"
#include "Control.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRORNONE -1
#define ERRORLAMBDA0 0
#define ERRORLAMBDA1 1
#define ERRORMU 2
#define ERRORNUMTASKS 3
#define ERRORTOOMANYARGS 4
#define ERRORTOOFEWARGS 5
#define ERRORINCORRECTNUMARGS 6
#define ERRORCANTFINDFILE 7
#define ERRORRATIO 8

#define NUMARGSMODE1 5
#define NUMARGSMODE2 2

#define DEFAULTLINENUM -1
#define OUTPUTNAME "proj1-a_output"

#define VERSION "1.0"

// A structure to hold information about command line arguments.
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
		fclose(file);
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

		if (parsedArgs->Lambda0 + parsedArgs->Lambda1 >= parsedArgs->Mu)
		{
			parsedArgs->Error = ERRORRATIO;
			return parsedArgs;
		}
	}

	return parsedArgs;
}

// Prints the usage message to stdout.
static void printUsageMessage()
{
	fprintf(stdout, "USAGE:\n\n");
	fprintf(stdout, "Mode 1:\t\t<executable name> <lambda0> <lambda1 > <mu> <total tasks in a priority group>\n");
	fprintf(stdout, "Example:\t\tproject1-A 0.5 0.3 1 10000\n\n");

	fprintf(stdout, "Mode 2:\t\t<executable name> <input file name>\n");
	fprintf(stdout, "Example:\t\tproject1-A input.txt\n\n");
}

// Prints the usage message to stdout.
static void printVersionMessage()
{
	fprintf(stdout, "VERSION %s\n\n", VERSION);
	fprintf(stdout, "The MIT License (MIT)\n\n");

	fprintf(stdout, "Copyright (c) 2015 Jordan Huffaker and Eric Colter\n\n");

	fprintf(stdout, "Permission is hereby granted, free of charge, to any person obtaining a copy\n");
	fprintf(stdout, "of this software and associated documentation files (the \"Software\"), to deal\n");
	fprintf(stdout, "in the Software without restriction, including without limitation the rights\n");
	fprintf(stdout, "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n");
	fprintf(stdout, "copies of the Software, and to permit persons to whom the Software is\n");
	fprintf(stdout, "furnished to do so, subject to the following conditions:\n\n");

	fprintf(stdout, "The above copyright notice and this permission notice shall be included in\n");
	fprintf(stdout, "all copies or substantial portions of the Software.\n\n");

	fprintf(stdout, "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n");
	fprintf(stdout, "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n");
	fprintf(stdout, "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n");
	fprintf(stdout, "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n");
	fprintf(stdout, "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n");
	fprintf(stdout, "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\n");
	fprintf(stdout, "THE SOFTWARE.\n");
}

// Prints error messages if any and returns whether there was an error.
static int printParsingErrors(int error)
{
	switch (error)
	{
		case ERRORCANTFINDFILE:
			fprintf(stderr, "Error: Could not open the file specified.\n\n");
			break;
		case ERRORINCORRECTNUMARGS:
			fprintf(stderr, "Error: An incorrect number of arguments was provided.\n\n");
			break;
		case ERRORLAMBDA0:
			fprintf(stderr, "Error: Could not understand the provided Lambda0 value.\n\n");
			break;
		case ERRORLAMBDA1:
			fprintf(stderr, "Error: Could not understand the provided Lambda1 value.\n\n");
			break;
		case ERRORMU:
			fprintf(stderr, "Error: Could not understand the provided Mu value.\n\n");
			break;
		case ERRORNUMTASKS:
			fprintf(stderr, "Error: Could not understand the provided Number of Tasks value.\n\n");
			break;
		case ERRORTOOFEWARGS:
			fprintf(stderr, "Error: Too few arguments were provided for either mode.\n\n");
			break;
		case ERRORTOOMANYARGS:
			fprintf(stderr, "Error: Too many arguments were provided for either mode.\n\n");
			break;
		case ERRORRATIO:
			fprintf(stderr, "Error: Lambda0 + Lambda1 was greater than or equal to Mu. System is unstable.\n\n");
			break;
		case ERRORNONE:
			return 0;
	}

	printUsageMessage();
	return 1;
}

// Prints an error message with the given line number and filename.
static void printFileReadingError(int lineNum, char* fileName)
{
	fprintf(stderr, "Error: Line %d of file %s is not in the correct format.\nCorrect format is:\t<arrival time> <priority> <duration>\n\n",
		lineNum, fileName);
}

// Prints the output to the output file and prints a message informing the user to stdout.
static void printOutput(Output* output)
{
	FILE* file = fopen(OUTPUTNAME, "wb");

	fprintf(file, "%f\n", output->AverageWait0);
	fprintf(file, "%f\n", output->AverageWait1);
	fprintf(file, "%f\n", output->AverageQueueLength);
	fprintf(file, "%f", output->AverageUtilization);

	fprintf(stdout, "The simulation has finished. Output located in file named: %s", OUTPUTNAME);

	fclose(file);
}

int main(int argc, char** argv)
{
	// Check for -help or -h flag
	if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
	{
		printUsageMessage();
		return EXIT_SUCCESS;
	}

	// Check for the -v flag
	if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0))
	{
		printVersionMessage();
		return EXIT_SUCCESS;
	}

	// Parse the arguments
	Args* args = parseArgs(argv, argc);
	// Check for errors in the provided arguments
	if (printParsingErrors(args->Error))
		return EXIT_FAILURE;

	fprintf(stdout, "Starting Simulation...\n");

	// Fill up a new FEL with the provided mode
	FEL* fel = NULL;
	// Mode 1:
	if (argc == NUMARGSMODE1)
	{
		fel = Control_InitializeModeOne(args->Lambda0, args->Lambda1, args->Mu, args->NumTasks);
	}
	// Mode 2:
	if (argc == NUMARGSMODE2)
	{
		int errorLine = DEFAULTLINENUM;
		fel = Control_InitializeModeTwo(args->FileName, &errorLine);
		if (errorLine != DEFAULTLINENUM)
		{
			printFileReadingError(errorLine, args->FileName);
			return EXIT_FAILURE;
		}
	}

	// Run simulation with generated FEL
	Output* output = Control_Run(fel);

	// Print the output in the correct format
	printOutput(output);

	// Destroy the output structure
	Output_Destroy(output);

	return EXIT_SUCCESS;
}