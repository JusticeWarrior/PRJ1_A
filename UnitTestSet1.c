#include <stdlib.h>
#include <stdio.h>
#include "ListNode.h"
#include "Event.h"
#include "Queue.h"

#define TRUE 1
#define FALSE 0

// Tests Creating and Destroying a node.
void Test1()
{
	int success;

	fprintf(stdout, "Test 1: Creating and Destroying a node\n");
	Event* testEvent1 = Event_Create(ARRIVAL, 0, 5, 0);
	ListNode* testNode1 = ListNode_Create(testEvent1);

	if (testNode1 != NULL)
	{
		success = TRUE;
	}
	else
	{
		success = FALSE;
	}
	ListNode_PrintList(testNode1, "One Element List");
	ListNode_DestroyList(testNode1);

	if (success == TRUE)
	{
		fprintf(stdout, "\nSuccess\n");
	}
	else
	{
		fprintf(stdout, "\nFailure\n");
	}
}

// Tests inserting and popping nodes from a list.
void Test2()
{
	int success, success2, success3;

	fprintf(stdout, "\nTest 2: Inserting and Popping nodes from a list.\n");
	Event* testEvent2 = Event_Create(DEPARTURE, 0, 2, 0);
	Event* testEvent3 = Event_Create(DEPARTURE, 0, 3, 0);
	Event* testEvent4 = Event_Create(DEPARTURE, 0, 4, 0);
	Event* testEvent5 = Event_Create(DEPARTURE, 0, 5, 0);
	ListNode* testNode2 = ListNode_Create(testEvent2);
	ListNode* testNode3 = ListNode_Create(testEvent3);
	ListNode* testNode4 = ListNode_Create(testEvent4);
	ListNode* testNode5 = ListNode_Create(testEvent5);

	ListNode* tail = ListNode_AppendTail(testNode3, testNode2);
	tail = ListNode_AppendTail(testNode4, tail);
	tail = ListNode_AppendTail(testNode5, tail);

	if (ListNode_GetLength(testNode2) == 4)
		success = TRUE;
	else
		success = FALSE;

	ListNode_PrintList(testNode2, "4 Element List");

	ListNode* testNode6 = ListNode_PopHead(testNode2);
	ListNode_PrintList(testNode6, "3 Element List");
	ListNode_PrintList(testNode2, "Popped Head Node");

	if (ListNode_GetLength(testNode6) == 3)
		success2 = TRUE;
	else
		success2 = FALSE;

	testNode2, testNode3, testNode4, testNode5, tail = NULL;
	ListNode* testNode7 = ListNode_PopHead(testNode6);
	ListNode* testNode8 = ListNode_PopHead(testNode7);
	ListNode* testNode9 = ListNode_PopHead(testNode8);
	tail = ListNode_AppendTail(testNode8, tail);
	tail = ListNode_AppendTail(testNode7, tail);
	tail = ListNode_AppendTail(testNode6, tail);
	tail = ListNode_AppendTail(testNode2, tail);
	ListNode_PrintList(testNode8, "4 Element List");
	if (ListNode_GetLength(testNode8) == 4)
		success3 = TRUE;
	else
		success3 = FALSE;

	ListNode_DestroyList(testNode8);

	if (success == TRUE && success2 == TRUE && success3 == TRUE)
		fprintf(stdout, "\nSuccess\n");
	else
		fprintf(stdout, "\nFailure\n");
}

// Tests inserting nodes in a sorted manner.
void Test3()
{
	int success, success2;

	fprintf(stdout, "\nTest 3: Inserting in a Sorted Manner\n");

	Event* testEvent1 = Event_Create(ARRIVAL, 0, 2, 0);
	Event* testEvent2 = Event_Create(ARRIVAL, 0, 3, 0);
	Event* testEvent3 = Event_Create(ARRIVAL, 0, 5, 0);
	Event* testEvent4 = Event_Create(ARRIVAL, 0, 6, 0);
	ListNode* testNode1 = ListNode_Create(testEvent1);
	ListNode* testNode2 = ListNode_Create(testEvent2);
	ListNode* testNode3 = ListNode_Create(testEvent3);
	ListNode* testNode4 = ListNode_Create(testEvent4);
	ListNode* head = ListNode_InsertSorted(testNode1, testNode2, ListNode_CompEventTime);
	head = ListNode_InsertSorted(testNode3, head, ListNode_CompEventTime);
	head = ListNode_InsertSorted(testNode4, head, ListNode_CompEventTime);

	ListNode_PrintList(head, "4 Element List");

	Event* testEvent5 = Event_Create(ARRIVAL, 0, 3, 0);
	ListNode* testNode5 = ListNode_Create(testEvent5);
	head = ListNode_InsertSorted(testNode5, head, ListNode_CompEventTime);
	ListNode_PrintList(head, "Same List With Inserted 3 Second Event");
	if (head->Next->Event->Time == 3 && head->Next->Next->Event->Time == 3)
		success = TRUE;
	else
		success = FALSE;


	Event* testEvent6 = Event_Create(ARRIVAL, 0, 1, 0);
	ListNode* testNode6 = ListNode_Create(testEvent6);
	head = ListNode_InsertSorted(testNode6, head, ListNode_CompEventTime);
	ListNode_PrintList(head, "Same List With Inserted 1 Second Event");
	if (head->Event->Time == 1)
		success2 = TRUE;
	else
		success2 = FALSE;

	Event* testEvent7 = Event_Create(ARRIVAL, 0, 20, 0);
	ListNode* testNode7 = ListNode_Create(testEvent7);
	head = ListNode_InsertSorted(testNode7, head, ListNode_CompEventTime);
	ListNode_PrintList(head, "Same List With Inserted 20 Second Event");
	if (head->Next->Next->Next->Next->Next->Next->Event->Time == 20 && success == TRUE && success2 == TRUE)
		fprintf(stdout, "\nSuccess\n");
	else
		fprintf(stdout, "\nFailure\n");

	ListNode_DestroyList(head);
}

// Tests the strip node functionality
void Test4()
{
	int success, success2;

	fprintf(stdout, "\nTest 4: Stripping a Node\n");

	Event* testEvent1 = Event_Create(ARRIVAL, 0, 2, 0);
	Event* testEvent2 = Event_Create(ARRIVAL, 0, 3, 0);
	Event* testEvent3 = Event_Create(ARRIVAL, 0, 5, 0);
	Event* testEvent4 = Event_Create(ARRIVAL, 0, 6, 0);
	ListNode* testNode1 = ListNode_Create(testEvent1);
	ListNode* testNode2 = ListNode_Create(testEvent2);
	ListNode* testNode3 = ListNode_Create(testEvent3);
	ListNode* testNode4 = ListNode_Create(testEvent4);
	ListNode* head = ListNode_InsertSorted(testNode1, testNode2, ListNode_CompEventTime);
	head = ListNode_InsertSorted(testNode3, head, ListNode_CompEventTime);
	head = ListNode_InsertSorted(testNode4, head, ListNode_CompEventTime);
	ListNode_PrintList(head, "4 Element List");

	head = ListNode_PopHead(testNode1);
	Event* testEventStrip1 = ListNode_StripEvent(testNode1);
	if (testEventStrip1->Time == 2 && head->Event->Time == 3)
		success = TRUE;
	else
		success = FALSE;
	ListNode_PrintList(head, "One Element Popped");

	head = ListNode_PopHead(testNode2);
	Event* testEventStrip2 = ListNode_StripEvent(testNode2);
	if (testEventStrip2->Time == 3 && head->Event->Time == 5)
		success2 = TRUE;
	else
		success2 = FALSE;
	ListNode_PrintList(head, "Two Elements Popped");

	testEventStrip1->Priority = 1;
	testEventStrip2->Type = DEPARTURE;
	ListNode* testNode5 = ListNode_Create(testEventStrip1);
	ListNode* testNode6 = ListNode_Create(testEventStrip2);
	head = ListNode_InsertSorted(testNode5, head, ListNode_CompEventTime);
	head = ListNode_InsertSorted(testNode6, head, ListNode_CompEventTime);
	ListNode_PrintList(head, "Reconstructed with altered Events");
	if (head->Event->Time == 2 && head->Event->Priority == 1 && head->Next->Event->Time == 3
		&& head->Next->Event->Type == DEPARTURE && success == TRUE && success2 == TRUE)
		fprintf(stdout, "\nSuccess\n");
	else
		fprintf(stdout, "\nFailure\n");

	ListNode_DestroyList(head);
}

// Tests queue create and destroy functions.
void Test5()
{
	fprintf(stdout, "\nTest 5: Creating and Destroying a Queue\n");

	Queue* testQueue1 = Queue_Create(0);
	if (testQueue1->Count == DEFAULTCOUNT)
		fprintf(stdout, "\nQueue was created correctly.\n\nSuccess\n");
	else
		fprintf(stdout, "\nQueue was not created correctly.\n\nFailure\n");

	Queue_Destroy(testQueue1);
}

// Tests adding and popping from a queue.
void Test6()
{
	int success, success2;

	fprintf(stdout, "\nTest 6: Adding and Popping from a Queue\n");

	Queue* testQueue1 = Queue_Create(0);

	Event* testEvent1 = Event_Create(ARRIVAL, 0, 2, 0);
	Event* testEvent2 = Event_Create(ARRIVAL, 0, 3, 0);
	Event* testEvent3 = Event_Create(ARRIVAL, 0, 5, 0);
	Event* testEvent4 = Event_Create(ARRIVAL, 0, 6, 0);
	ListNode* testNode1 = ListNode_Create(testEvent1);
	ListNode* testNode2 = ListNode_Create(testEvent2);
	ListNode* testNode3 = ListNode_Create(testEvent3);
	ListNode* testNode4 = ListNode_Create(testEvent4);

	Queue_Add(testQueue1, testNode1);
	Queue_Add(testQueue1, testNode2);
	Queue_Add(testQueue1, testNode3);
	Queue_Add(testQueue1, testNode4);
	ListNode_PrintList(testQueue1->Head, "4 Element Queue List");
	if (testQueue1->Count == 4)
		success = TRUE;
	else
		success = FALSE;

	ListNode* testNode5 = Queue_Pop(testQueue1);
	ListNode* testNode6 = Queue_Pop(testQueue1);
	ListNode_PrintList(testQueue1->Head, "2 Element Queue List");
	if (testQueue1->Count == 2 && testNode5->Event->Time == 2 && testNode6->Event->Time == 3)
		success2 = TRUE;
	else
		success2 = FALSE;

	Queue_Add(testQueue1, testNode5);
	Queue_Add(testQueue1, testNode6);
	ListNode_PrintList(testQueue1->Head, "Reconstructed 4 Element Queue List");
	if (testQueue1->Count == 4 && testQueue1->Tail->Event->Time == 3 &&
		testQueue1->Head->Next->Next->Event->Time == 2 && success == TRUE
		&& success2 == TRUE)
		fprintf(stdout, "\nSuccess\n");
	else
		fprintf(stdout, "\nFailure\n");

	Queue_Destroy(testQueue1);
}

int main(int argc, char** argv)
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return EXIT_SUCCESS;
}