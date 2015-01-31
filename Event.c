#include "Event.h"

Event* Event_Create(char type, int priority, int time)
{
	Event* event = malloc(sizeof(Event));

	event->Type = type;
	event->Priority = priority;
	event->Time = time;

	return event;
}

void Event_Destroy(Event* event)
{
	free(event);
}

int Event_CompTime(Event* event1, Event* event2)
{
	return event2->Time - event1->Time;
}