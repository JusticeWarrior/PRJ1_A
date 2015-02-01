#include <stdlib.h>
#include <stdio.h>
#include "ListNode.h"
#include "Event.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char** argv)
{
	int success;

	fprintf(stdout, "Test 1: Creating and Destroying a node\n");
	Event* testEvent1 = Event_Create(ARRIVAL, 0, 5);
	ListNode* testNode1 = ListNode_Create(testEvent1);

	if (testNode1 != NULL)
	{
		success = TRUE;
	}
	else
	{
		success = FALSE;
	}
	ListNode_PrintList(testNode1);
	ListNode_DestroyList(testNode1);

	if (success == TRUE)
	{
		fprintf(stdout, "\nSuccess\n");
	}
	else
	{
		fprintf(stdout, "\nFailure\n");
	}
	
	fprintf(stdout, "Test 2:\n");
	Event* testEvent2 = Event_Create(DEPARTURE, 0, 1);
	Event* testEvent3 = Event_Create(DEPARTURE, 0, 2);
	Event* testEvent4 = Event_Create(DEPARTURE, 0, 3);
	Event* testEvent5 = Event_Create(DEPARTURE, 0, 4);
	ListNode* testNode2 = ListNode_Create(testEvent2);
	ListNode* testNode3 = ListNode_Create(testEvent3);
	ListNode* testNode4 = ListNode_Create(testEvent4);
	ListNode* testNode5 = ListNode_Create(testEvent5);

	return EXIT_SUCCESS;
}