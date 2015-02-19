#include "Queue.h"

static void Queue_RemoveTask(Queue* queue, ListNode* prevTask, ListNode* task, int length);
static void Queue_RemoveNodes(ListNode* prevNode, ListNode* node, int length, ListNode** head, ListNode** tail);
static void Queue_AddTask(Queue* queue, ListNode* task);

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

// Adds a task to a specific queue. Increases count, numtask, updates head,
// and updates tail.
static void Queue_AddTask(Queue* queue, ListNode* task)
{
	// If adding an empty task, do nothing
	if (task == NULL)
		return;

	// If the count is 0 then update the head.
	if (queue->Count == 0)
	{
		queue->Head = task;
	}

	// Get the new count
	queue->Count += ListNode_GetLength(task);

	// Update the number of tasks
	queue -> NumTasks++;

	// Append the task list and update tail
	queue->Tail = ListNode_AppendTail(task, queue->Tail);
}

void Queue_SortTask(Queue* queue0, Queue* queue1, ListNode* task)
{
	if (task->Event->Priority == 0)
		Queue_AddTask(queue0, task);
	else
		Queue_AddTask(queue1, task);
}

// When provided with the first node of a list, the function will remove the list
// (of the length provided) and reconnect the list together. If the tail of the list
// has changed, the function will automatically update the tail. If the head of the
// list has changed, the function will automatically update the head.
static void Queue_RemoveNodes(ListNode* prevNode, ListNode* node, int length, ListNode** head, ListNode** tail)
{
	assert(!(node == NULL && length > 0)); // IF NODE IS NULL, THE LENGTH MUST BE GREATHER THAN 0!

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
		node->Next = NULL; // Make the node a separate list
		return;
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
	assert(!(task == NULL && length > 0)); // MAKE SURE THAT THE TASK LINES UP WITH THE LENGTH!

	if (task == NULL) // Do nothing on empty tasks
		return;

	// Detach the task from the queue.
	Queue_RemoveNodes(prevTask, task, length, &queue->Head, &queue->Tail);

	// Decrement the number of tasks
	queue -> NumTasks--;
	// Decrement the count of the queue
	queue->Count -= length;
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
	ListNode* scan = Queue_ScanQueue(queue0, maxProcessors); // Check priority 0

	if (scan == NULL)
		return Queue_ScanQueue(queue1, maxProcessors); // Check priority 1

	return scan;
}
