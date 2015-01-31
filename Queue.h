#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

// A structure to hold overhead data about a queue.
typedef struct Queue_st Queue;

#include "ListNode.h"

struct Queue_st{
	int Count;
	ListNode* Head;
	ListNode* Tail;
};

#endif /* QUEUE_INCLUDED */