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

	if (queue->Tail == NULL)
	{
		queue->Head = node;
		queue->Tail = node;
	}

	queue->Count++;
	queue->Tail = ListNode_AppendTail(node, queue->Tail);
}

ListNode* Queue_Pop(Queue* queue)
{
	if (queue->Count == 0)
		return NULL;

	queue->Count--;
	ListNode* poppedNode = queue->Head;

	queue->Head = ListNode_PopHead(queue->Head);

	return poppedNode;
}