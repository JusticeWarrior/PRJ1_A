#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED 

typedef struct Server_st Server;

#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"

struct Server_st{
  int Processors;  //The total number of processors this server has
  int Available;   //The number of available processors
  ListNode* Tasks; //A list of tasks currently in the server
};

//Create a Server structure with the given number of processors
Server* Server_Create(int processors);

//Destroy the given Server structure
void Server_Destroy(Server* server);


#endif /* SERVER_INCLUDED */
