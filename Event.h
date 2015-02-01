#ifndef EVENT_INCLUDED
#define EVENT_INCLUDED
#define ARRIVAL A
#define DEPARTURE D

// A structure to hold event data of a particular event.
typedef struct Event_st Event;

#include<stdlib.h>

struct Event_st{
	// Either an ARRIVAL or a DEPARTURE
	char Type;
	int Priority;
	int Time;
};

// Creates and instance of Event given the type, priority, and time.
Event* Event_Create(char type, int priority, int time);

// Destroys the current instance of Event.
void Event_Destroy(Event* event);

// Compares two events according to their time. Returns a positive integer if
// event1 has a lower time than event2, a negative integer if event2 has a lower
// time than event1, and 0 if they are equal.
int Event_CompTime(Event* event1, Event* event2);

#endif /* EVENT_INCLUDED */