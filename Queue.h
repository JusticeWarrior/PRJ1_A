#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

// A structure to hold overhead data about a queue.
typedef struct Queue_st Queue;

#include "ListNode.h"
#include <assert.h>

#define DEFAULTCOUNT 0
#define DEFAULTNUMTASKS 0

struct Queue_st{
	int Count;
	ListNode* Head;
	ListNode* Tail;
	int Priority;
	int NumTasks;
};

// Creates an instance of a queue with a default count of 0, null ListNode*,
// the default number of tasks, and the provided priority level.
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

// Adds an entire task to the corresponding queue and updates the number
// of tasks.
void Queue_AddTask(Queue* queue0, Queue* queue1, ListNode* task);

// Scans through a single queue to see if an entire task can be popped
// from it based on the number of processors available. Returns an entire
// task if possible, otherwise, it returns NULL. If a task is taken out,
// the function will decrement the NumTasks integer.
ListNode* Queue_ScanQueue(Queue* queue, int maxProcessors);

// Scans through the 0 priority queue to determine if an entire task can
// be popped from it. If it cannot, then the function will scan through the
// 1 priority queue. Returns an entire task if possible, otherwise, it returns
// NULL. If a task is taken out, the function will decrement the NumTasks
// integer.
ListNode* Queue_ScanQueues(Queue* queue0, Queue* queue1, int maxProcessors);

#endif /* QUEUE_INCLUDED */
