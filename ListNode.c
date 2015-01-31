#include "ListNode.h"

ListNode* ListNode_Create(Event* event)
{
	ListNode* node = malloc(sizeof(ListNode));

	node->Event = event;
	node->Next = NULL;

	return node;
}

void ListNode_DestroyList(ListNode* head)
{
	if (head == NULL)
		return;

	ListNode_DestroyList(head->Next);
	Event_Destroy(head->Event);

	free(head);
}

ListNode* ListNode_InsertSorted(ListNode* node, ListNode* listhead)
{
	return NULL;
}

ListNode* ListNode_AppendTail(ListNode* node, ListNode* listTail)
{
	node->Next = listTail;

	return node;
}

ListNode* ListNode_PopHead(ListNode* headNode)
{
	ListNode* newHead = headNode->Next;

	headNode->Next = NULL;

	return newHead;
}