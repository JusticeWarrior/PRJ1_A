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

void Queue_Add(Queue* queue, ListNode* node)
{
	queue->Tail = ListNode_AppendTail(node, queue->Tail);
}

ListNode* Queue_Pop(Queue* queue)
{
	ListNode* poppedNode = queue->Head;

	queue->Head = ListNode_PopHead(queue->Head);

	return poppedNode;
}