#ifndef LISTNODE_INCLUDED
#define LISTNODE_INCLUDED

// A structure to hold a node of singley linked-list of event data.
typedef struct ListNode_st ListNode;

#include "Event.h"

struct ListNode_st{
	struct ListNode_st* Next;
	Event* Event;
};

// Creates an instance of a list node with the given event.
ListNode* ListNode_Create(Event* event);

// Destroys the instance of list node.
void ListNode_Destroy(ListNode* node);

// Inserts the list node into the list in a sorted manner where the head has the lowest event time
// and the tail has the greatest event time. Returns the new list head in case the insert changes it.
ListNode* ListNode_InsertSorted(ListNode* node, ListNode* listhead);

// Appends the node to the head of the list. Returns the new head of the list.
ListNode* ListNode_Append(ListNode* node, ListNode* listhead);

// Pops off the tail node of the list.
void ListNode_TailPop(ListNode* tailNode);

#endif /* LISTNODE_INCLUDED */
