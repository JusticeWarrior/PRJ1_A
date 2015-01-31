#ifndef LISTNODE_INCLUDED
#define LISTNODE_INCLUDED

typedef struct ListNode_st ListNode;

#include "Event.h"

typedef struct ListNode_st{
	struct ListNode_st* Next;
	Event* Event;
} ListNode;

#endif /* LISTNODE_INCLUDED */
