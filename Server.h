#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED 

typedef struct Server_st Server;

#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"

struct Server_st{
  int processors;  //The total number of processors this server has
  int available;   //The number of available processors
  ListNode* Tasks; //A list of tasks currently in the server
};

Server* Server_Create(int processors);

void Server_Destroy(Server* server);

#endif /* SERVER_INCLUDED */
