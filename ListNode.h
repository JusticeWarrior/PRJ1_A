#ifndef LISTNODE_INCLUDED
#define LISTNODE_INCLUDED

// A structure to hold a node of singley linked-list of event data.
typedef struct ListNode_st ListNode;

#include <stdlib.h>
#include "Event.h"

struct ListNode_st{
	struct ListNode_st* Next;
	Event* Event;
};

// Creates an instance of a list node with the given event.
ListNode* ListNode_Create(Event* event);

// Destroys the entire list of nodes by recursively calling to destroy the next node. Also calls
// for the destruction of the Event structure associated with each node.
void ListNode_DestroyList(ListNode* head);

// Inserts the list node into the list in a sorted manner according to a comparison function.
// Returns the new list head in case the insert changes it.
ListNode* ListNode_InsertSorted(ListNode* node, ListNode* listhead, int* compFunc(ListNode*, ListNode*));

// Appends the node to the tail of the list. Returns the new tail of the list.
ListNode* ListNode_AppendTail(ListNode* node, ListNode* listTail);

// Pops off the head node of the list. Returns the new list head.
ListNode* ListNode_PopHead(ListNode* headNode);

#endif /* LISTNODE_INCLUDED */
