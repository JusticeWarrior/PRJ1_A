#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED 
#include "FEL.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"
#include "Event.h"

typedef struct Server_st{
  int processors;
  int available;
  ListNode* Tasks;
} Server;

#endif /* SERVER_INCLUDED */
