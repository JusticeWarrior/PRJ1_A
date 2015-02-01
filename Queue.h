#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

// A structure to hold overhead data about a queue.
typedef struct Queue_st Queue;

#include "ListNode.h"

#define DEFAULTCOUNT 0

struct Queue_st{
	int Count;
	ListNode* Head;
	ListNode* Tail;
};

// Creates an instance of a queue with a default count of 0 and null ListNode*.
Queue* Queue_Create();

// Destroys the current instance of queue and all data that it still contains.
void Queue_Destroy(Queue* queue);

// Calls ListNode_AppendTail to append a node to the tail of the queue.
void Queue_Add(Queue* queue, ListNode* node);

// Pops the head node off of the queue and returns it as output.
ListNode* Queue_Pop(Queue* queue);

#endif /* QUEUE_INCLUDED */