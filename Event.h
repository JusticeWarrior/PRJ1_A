#ifndef EVENT_INCLUDED
#define EVENT_INCLUDED

// A structure to hold event data of a particular event.
typedef struct Event_st Event;

struct Event_st{
	char Type;
	int Priority;
	int Time;
};

// Creates and instance of Event given the type, priority, and time.
Event* Event_Create(char type, int priority, int time);

// Destroys the current instance of Event.
void Event_Destroy(Event* event);



#endif /* EVENT_INCLUDED */