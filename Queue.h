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

// Creates and instance of a queue with a default count of 0 and null ListNode*.
Queue* Queue_Create(Queue* queue);

// Destroys the current instance of queue and all data that it still contains.
void Queue_Destroy(Queue* queue);

// Calls ListNode_Append to append the node to the front of the queue's head.
ListNode* Queue_Append(Queue* queue, ListNode* node);

// Pops the head node off of the queue and returns it as output.
ListNode* Queue_Pop();

#endif /* QUEUE_INCLUDED */