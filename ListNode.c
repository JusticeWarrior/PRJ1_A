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

ListNode* ListNode_Append(ListNode* node, ListNode* listhead)
{
	return NULL;
}

void ListNode_TailPop(ListNode* tailNode) { }