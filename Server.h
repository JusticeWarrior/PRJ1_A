#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED 

#include "Event.h"
#include "ListNode.h"

typedef struct Server_st{
  int processors;
  int available;
  ListNode* Tasks;
} Server;

#endif /* SERVER_INCLUDED */
