#include "Queue.h"

Queue* Queue_Create()
{
	Queue* queue = malloc(sizeof(Queue));

	queue->Count = DEFAULTCOUNT;
	queue->Head = NULL;
	queue->Tail = NULL;

	return queue;
}

void Queue_Destroy(Queue* queue)
{
	if (queue == NULL)
		return;

	ListNode_DestroyList(queue->Head);

	free(queue);
}

ListNode* Queue_Append(Queue* queue, ListNode* node)
{
	

	return NULL;
}

ListNode* Queue_Pop()
{
	return NULL;
}