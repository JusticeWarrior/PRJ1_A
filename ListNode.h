#ifndef LISTNODE_INCLUDED
#define LISTNODE_INCLUDED

#include <stdlib.h>
#include "FEL.h"
#include "Event.h"
#include "Server.h"
#include "Queue.h"
#include "SimulationData.h"

typedef struct ListNode_st{
	ListNode_st* Next;
	Event* Event;
} ListNode;

#endif /* LISTNODE_INCLUDED */