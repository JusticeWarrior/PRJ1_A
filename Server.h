#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"

#ifndef SERVER_INCLUDED
#define SERVER_INLCUDED 

typedef struct Server_st{
  int processors;
  int available;
  ListNode* Tasks;
} Server;

#endif /* SERVER_INCLUDED */
