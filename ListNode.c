#include "ListNode.h"

static ListNode* ListNode_FindTail(ListNode* head);
static ListNode* ListNode_CompareAndAddNode(ListNode** list1, ListNode** list2, int(*compFunc)(ListNode*, ListNode*));

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

ListNode* ListNode_FindTail(ListNode* head)
{
	if (head == NULL)
		return NULL;

	while (head->Next != NULL)
	{
		head = head->Next;
	}

	return head; // Now the tail
}

ListNode* ListNode_AppendTail(ListNode* node, ListNode* listTail)
{
	assert(node != NULL); // Make sure you don't add a NULL node!

	if (listTail == NULL)
		return ListNode_FindTail(node);

	listTail->Next = node;

	return ListNode_FindTail(node);
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

// Compares the head's of two lists and returns the lesser of the two.
// Also moves along the pointer of the list grabbed from.
static ListNode* ListNode_CompareAndAddNode(ListNode** list1, ListNode** list2, int(*compFunc)(ListNode*, ListNode*))
{
	assert(*list1 != NULL || *list2 != NULL); // DONT TRY TO ADD ANY NULL LISTS!

	ListNode* addNode = NULL;

	if (compFunc(*list1, *list2) >= 1)
	{
		addNode = *list1;
		(*list1) = (*list1)->Next;
	}
	else
	{
		addNode = *list2;
		(*list2) = (*list2)->Next;
	}

	return addNode;
}

ListNode* ListNode_MergeSortedLists(ListNode* list1, ListNode* list2, int(*compFunc)(ListNode*, ListNode*))
{
	// Check for NULL inputs and handle correctly
	if (list1 == NULL && list2 == NULL)
		return NULL;
	if (list1 == NULL)
		return list2;
	if (list2 == NULL)
		return list1;

	ListNode* newHead = NULL;
	ListNode* newTail = NULL;
	
	// Add the first node
	newTail = ListNode_AppendTail(ListNode_CompareAndAddNode(&list1, &list2, compFunc), newTail);

	// Assign the head of the list correctly
	newHead = newTail;

	// Add the rest of the nodes until one list is NULL
	while (list1 != NULL && list2 != NULL)
	{
		newTail = ListNode_AppendTail(ListNode_CompareAndAddNode(&list1, &list2, compFunc), newTail);
	}

	// Add the entire rest of the non-NULL list to the end of the final list
	if (list1 == NULL)
	{
		newTail = ListNode_AppendTail(list2, newTail);
	}
	else
	{
		newTail = ListNode_AppendTail(list1, newTail);
	}

	return newHead;
}

int ListNode_CompDurTask(ListNode* node1, ListNode* node2)
{
	return Event_CompDurTask(node1->Event, node2->Event);
}