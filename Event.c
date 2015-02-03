#include "Event.h"

Event* Event_Create(char type, int priority, int time, int duration)
{
	Event* event = malloc(sizeof(Event));

	event->Type = type;
	event->Priority = priority;
	event->Time = time;
	event->Duration = duration;

	return event;
}

void Event_Destroy(Event* event)
{
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