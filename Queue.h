#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

// A structure to hold overhead data about a queue.
typedef struct Queue_st Queue;

#include "ListNode.h"
#include <assert.h>

#define DEFAULTCOUNT 0

struct Queue_st{
	int Count;
	ListNode* Head;
	ListNode* Tail;
	int Priority;
};

// Creates an instance of a queue with a default count of 0, null ListNode*, and 
// the provided priority level.
Queue* Queue_Create(int priority);

// Destroys the current instance of queue and all data that it still contains.
void Queue_Destroy(Queue* queue);

// Calls ListNode_AppendTail to append a node to the tail of the queue.
void Queue_Add(Queue* queue, ListNode* node);

// Pops the head node off of the queue and returns it as output. Returns NULL if
// the queue is empty.
ListNode* Queue_Pop(Queue* queue);

// Provided with two queues of different priority types, the function will add
// the node to the correct queue.
void Queue_AddArrival(Queue* queue0, Queue* queue1, ListNode* node);

#endif /* QUEUE_INCLUDED */
