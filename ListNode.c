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
	assert(node != NULL); // Make sure you don't add a NULL node!

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
	assert(node != NULL); // Make sure you don't add a NULL node!

	if (listTail == NULL)
		return node;

	listTail->Next = node;

	return node;
}

ListNode* ListNode_PopHead(ListNode* headNode)
{
	assert(headNode != NULL); // Make sure you don't pop a NULL node!

	ListNode* newHead = headNode->Next;

	headNode->Next = NULL;

	return newHead;
}

int ListNode_CompEventTimePriority(ListNode* node1, ListNode* node2)
{
	assert(node1 != NULL && node2 != NULL); // Don't compare against any NULL nodes!
	return Event_CompTimePriority(node1->Event, node2->Event);
}

void ListNode_PrintList(ListNode* head, const char* name)
{
	fprintf(stdout, "Printing %s...\n", name);
	int node = 1;

	while (head != NULL && head->Event != NULL)
	{
		fprintf(stdout, "Node %d: %ds %c %d %ds\n", node, head->Event->Time, head->Event->Type,
			head->Event->Priority, head->Event->Duration);
		
		node++;
		head = head->Next;
	}
}

void ListNode_PrintToTestFile(ListNode* head, const char* testFileName)
{
	FILE* testFile = fopen(testFileName, "wb");

	while (head != NULL && head->Event != NULL)
	{
		fprintf(testFile, "%d %d %d\n", head->Event->Time, head->Event->Priority, head->Event->Duration);

		head = head->Next;
	}

	fclose(testFile);
}

int ListNode_GetLength(ListNode* head)
{
	int length = 0;

	while (head != NULL)
	{
		head = head->Next;
		length++;
	}

	return length;
}

Event* ListNode_StripEvent(ListNode* node)
{
	if (node == NULL)
		return NULL; // Make sure you don't strip a NULL node!
	assert(node->Next == NULL); // Make sure that you Pop the node off from the list before trying to strip it!

	Event* event = node->Event;
	node->Event = NULL;

	ListNode_DestroyList(node);

	return event;
}

ListNode* ListNode_MergeSortedLists(ListNode* list1, ListNode* list2)
{
	return NULL;
}