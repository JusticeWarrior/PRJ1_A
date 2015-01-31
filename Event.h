#ifndef EVENT_INCLUDED
#define EVENT_INCLUDED

typedef struct Event_st Event;

typedef struct Event_st{
	char Type;
	int Priority;
	int Time;
} Event;

#endif /* EVENT_INCLUDED */