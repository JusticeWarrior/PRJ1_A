#include "Queue.h"

Queue* Queue_Create(int priority)
{
	Queue* queue = malloc(sizeof(Queue));

	queue->Count = DEFAULTCOUNT;
	queue->Head = NULL;
	queue->Tail = NULL;
	queue->Priority = priority;

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