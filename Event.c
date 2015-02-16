#include "Event.h"

Event* Event_Create(char type, int priority, int time, int duration, Task* task)
{
	Event* event = malloc(sizeof(Event));

	event->Type = type;
	event->Priority = priority;
	event->Time = time;
	event->Duration = duration;
	event->Task = task;

	return event;
}

void Event_Destroy(Event* event)
{
	event->Task->SubTasks--;
	if (event->Task->SubTasks == 0)
		Task_Destroy(event->Task);
	free(event);
}

int Event_CompTimePriority(Event* event1, Event* event2)
{
	assert(event1 != NULL && event2 != NULL);

	int comp = event2->Time - event1->Time;

	if (comp == 0)
		return event2->Priority - event1->Priority;

	return comp;
}

Task* Task_Create(int subTasks, int minDuration, int maxDuration)
{
	return NULL;
}

void Task_Destroy(Task* task) { }