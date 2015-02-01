#include <stdlib.h>
#include <stdio.h>
#include "ListNode.h"
#include "Event.h"

#define TRUE 1;
#define FALSE 0;

int main(int argc, char** argv)
{
	int success;
	fprintf(stdout, "Test 1:\n\n");
	Event* testEvent1 = Event_Create('t', 0, 5);
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

	/*if (testNode1 == NULL && success == TRUE)
	{

	}*/
	//{
	//	//fprintf(stdout, "\nSuccess\n");
	//}
	//else
	//{
	//	//fprintf(stdout, "\nFailure\n");
	//}
	

	return EXIT_SUCCESS;
}