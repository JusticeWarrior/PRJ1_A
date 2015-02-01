#ifndef LISTNODE_INCLUDED
#define LISTNODE_INCLUDED

// A structure to hold a node of singley linked-list event data.
typedef struct ListNode_st ListNode;

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
// A lower comparison value equates to a position closer to the head of the list.
// Returns the new list head in case the insert changes it.
ListNode* ListNode_InsertSorted(ListNode* node, ListNode* listHead, int (*compFunc)(ListNode*, ListNode*));

// Appends the node to the tail of the list. Returns the new tail of the list.
ListNode* ListNode_AppendTail(ListNode* node, ListNode* listTail);

// Pops off the head node of the list. Returns the new list head.
ListNode* ListNode_PopHead(ListNode* headNode);

// Compares two ListNodes according to the event time. Returns a positive integer if
// node1 has a lower event time than node2, negative integer if node2 has a lower event time
// than node1, and 0 if they have the same event time.
int ListNode_CompEventTime(ListNode* node1, ListNode* node2);

// Prints the entire list starting with the head and prints the provided name.
// Used for testing purposes.
void ListNode_PrintList(ListNode* head, const char* name);

// Gets the length of the list and returns it as an integer.
int ListNode_GetLength(ListNode* head);

// Strips the Event structure from the current node and returns the Event.
// Destroys only the current instance of the ListNode. MAKE SURE THE NODE IS
// POPPED FROM THE LIST ALREADY!!
Event* ListNode_StripEvent(ListNode* node);

#endif /* LISTNODE_INCLUDED */
