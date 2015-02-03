#ifndef CONTROL_INCLUDED
#define CONTROL_INCLUDED 

typedef struct Output_st Output;


#include "Event.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"
#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A structure to hold the output metrics calculated from the simulation
struct Output_st{
  float AverageWait0;        //The average wait time of the zero priority queue
  float AverageWait1;        //The average wait time of the one priority queue
  float AverageQueueLength;  //The average queue length
  float AverageUtilization;  //Fraction of time the CPU is on
  int EndTime; //The time that the simulation ends
};

//Create and populate arrivals for the FEL for a random simulation
FEL* Control_InitializeModeOne(float lambda0, float lambda1, float mu, int numTasks);

//Create and populate arrivals for the FEL for a simulation given in
//a text file.  If there is an error, instead return null and set 
//the value at lineNumber to be the line number of the error
FEL* Control_InitializeModeTwo(const char* filename, int* lineNumber);

//Run the simulation and produce output
Output* Control_Run(FEL* fel);

//Create an Output struture
Output* Output_Create(float AvgWait0, float AvgWait1, float AvgQueue, float AvgCPU, int EndTime);

//Destroy an Output structure
void Output_Destroy(Output* output);


#endif /* CONTROL_INCLUDED */
