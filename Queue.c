#include "Queue.h"

static void Queue_RemoveTask(Queue* queue, ListNode* prevTask, ListNode* task, int length);
static void Queue_RemoveNodes(ListNode* prevNode, ListNode* node, int length, ListNode** head, ListNode** tail);

Queue* Queue_Create(int priority)
{
	Queue* queue = malloc(sizeof(Queue));

	queue->Count = DEFAULTCOUNT;
	queue->Head = NULL;
	queue->Tail = NULL;
	queue->Priority = priority;
	queue->NumTasks = DEFAULTNUMTASKS;

	return queue;
}

void Queue_Destroy(Queue* queue)
{
	if (queue == NULL)
		return;

	ListNode_DestroyList(queue->Head);

	free(queue);
}

void Queue_Add(Queue* queue, ListNode* node)
{
	assert(node != NULL); // Make sure you don't add a NULL node!
	assert(node->Event->Priority == queue->Priority); // Make sure you don't add an event with a different priority than the queue!

	if (queue->Count == 0)
	{
		queue->Head = node;
		queue->Tail = node;
		queue->Count = 1;
		return;
	}

	queue->Count++;
	queue->Tail = ListNode_AppendTail(node, queue->Tail);
}

ListNode* Queue_Pop(Queue* queue)
{
	if (queue->Count == 0)
		return NULL;

	if (queue->Count == 1)
		queue->Tail = NULL;

	queue->Count--;
	ListNode* poppedNode = queue->Head;

	queue->Head = ListNode_PopHead(queue->Head);

	return poppedNode;
}

void Queue_AddArrival(Queue* queue0, Queue* queue1, ListNode* node)
{
	assert(queue0->Priority != queue1->Priority); // Make sure the Queues don't have the same priority level!
	assert(node != NULL); // Make sure you don't add a NULL node!
	assert(queue0 != NULL && queue1 != NULL); // Make sure the queue's aren't NULL!

	if (queue0->Priority == node->Event->Priority)
		Queue_Add(queue0, node);
	else if (queue1->Priority == node->Event->Priority)
		Queue_Add(queue1, node);
	else
	{
		assert(0); // The arrival could not be added to either queue!
	}
}

void Queue_AddTask(Queue* queue0, Queue* queue1, ListNode* task)
{
	
}

// When provided with the first node of a list, the function will remove the list
// (of the length provided) and reconnect the list together. If the tail of the list
// has changed, the function will automatically update the tail. If the head of the
// list has changed, the function will automatically update the head.
static void Queue_RemoveNodes(ListNode* prevNode, ListNode* node, int length, ListNode** head, ListNode** tail)
{
	assert(!(node != NULL && length > 0)); // IF NODE IS NULL, THE LENGTH MUST BE GREATHER THAN 0!

	if (node == NULL) // If there is no task to elliminate, do nothing
		return;

	// Iterate through the list until the last node of the removed list is reached.
	int i;
	for (i = 1; i < length; i++)
	{
		assert(node->Next != NULL); // THE LIST PROVIDED MUST BE OF THE LENGTH PROVIDED
		node = node->Next;
	}

	// If the tail has been removed.
	if (node->Next == NULL)
	{
		*tail = prevNode; // Update the tail
	}

	// If the head has changed
	if (prevNode == NULL)
	{
		*head = node->Next; // Update the head
	}
	
	// Connect the previous node to the node after the removed list
	prevNode->Next = node->Next;

	node->Next = NULL; // Make the node a separate list
}

// This function will remove an entire task from the queue based
// on the length of the task. Decrements the number of tasks if
// it has changed.
static void Queue_RemoveTask(Queue* queue, ListNode* prevTask, ListNode* task, int length)
{
	assert(!(task != NULL && length <= 0)); // MAKE SURE THAT THE TASK LINES UP WITH THE LENGTH!

	if (task == NULL) // Do nothing on empty tasks
		return;

	// Detach the task from the queue.
	Queue_RemoveNodes(prevTask, task, length, &queue->Head, &queue->Tail);

	// Decrement the number of tasks
	queue->NumTasks--;
}

ListNode* Queue_ScanQueue(Queue* queue, int maxProcessors)
{
	ListNode* prevNode = NULL;
	ListNode* head = queue->Head;

	while (head != NULL)
	{
		if (head->Event->Task->SubTasks <= maxProcessors)
		{
			Queue_RemoveTask(queue, prevNode, head, head->Event->Task->SubTasks);
			return head;
		}
			
		prevNode = head;
		head = head->Next;
	}

	return NULL;
}

ListNode* Queue_ScanQueues(Queue* queue0, Queue* queue1, int maxProcessors)
{
	return NULL;
}