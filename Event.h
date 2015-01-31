#ifndef EVENT_INCLUDED
#define EVENT_INCLUDED

typedef struct Event_st Event;

struct Event_st{
	char Type;
	int Priority;
	int Time;
};

#endif /* EVENT_INCLUDED */