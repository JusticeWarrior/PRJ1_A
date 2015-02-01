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
	// If the list is emtpy
	if (listHead == NULL)
		return node;

	// If the node has higher or equal authority than the head of the list
	if (compFunc(node, listHead) >= 0)
	{
		node->Next = listHead;
		return node; // Return the new head of the list
	}

	// Check each node until one of lower authority is found
	ListNode* current = listHead;
	while (current->Next != NULL)
	{
		if (compFunc(node, current->Next) >= 0)
		{
			// If a node of lower or equal authority is found
			node->Next = current->Next;
			current->Next = node;

			return listHead;
		}

		current = current->Next; // Iterate to the next node
	}

	// If the node has the lowest authority
	current->Next = node; // set the tail to the node

	return listHead;
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

void ListNode_PrintList(ListNode* head)
{
	fprintf(stdout, "Printing List...\n");
	int node = 1;

	while (head != NULL)
	{
		fprintf(stdout, "Node %d: %ds %c %d", node, head->Event->Time, head->Event->Type, head->Event->Priority);
		
		node++;
		head = head->Next;
	}
}