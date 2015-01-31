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

ListNode* ListNode_InsertSorted(ListNode* node, ListNode* listHead, int (*compFunc)(ListNode*, ListNode*))
{
	if (listHead == NULL)
		return node;

	if (compFunc(node, listHead) >= 0)
	{
		node->Next = listHead;
		return node;
	}

	ListNode* current = listHead;
	ListNode* prevNode = listHead;

	while (current != NULL)
	{
		if (compFunc(node, current) >= 1)
		{
			
		}
	}

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

int ListNode_CompEventTime(ListNode* node1, ListNode* node2)
{
	return Event_CompTime(node1->Event, node2->Event);
}