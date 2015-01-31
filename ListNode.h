#ifndef LISTNODE_INCLUDED
#define LISTNODE_INCLUDED

typedef struct ListNode_st ListNode;

#include "Event.h"

struct ListNode_st{
	struct ListNode_st* Next;
	Event* Event;
};

#endif /* LISTNODE_INCLUDED */
