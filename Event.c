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
	Task* task = malloc(sizeof(Task));
	task->SubTasks = subTasks;
	task->MinDuration = minDuration;
	task->MaxDuration = maxDuration;

	return task;
}

void Task_Destroy(Task* task)
{
	free(task);
}

int Event_CompDurTask(Event* event1, Event* event2)
{
	if (event1->Task == event2->Task && event1->Duration == event2->Duration)
		return TRUE; // They are the same
	else
		return FALSE;
}