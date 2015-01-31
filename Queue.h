#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

typedef struct Queue_st Queue;

#include "ListNode.h"

typedef struct Queue_st{
	int Count;
	ListNode* Head;
	ListNode* Tail;
} Queue;

#endif /* QUEUE_INCLUDED */