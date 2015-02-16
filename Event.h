#ifndef EVENT_INCLUDED
#define EVENT_INCLUDED
#define ARRIVAL 'A'
#define DEPARTURE 'D'
#define TRUE 1
#define FALSE 0

// A structure to hold event data of a particular event.
typedef struct Event_st Event;

// A structure to hold information about an entire task.
// This includes many subtasks in a single structure.
typedef struct Task_st Task;

#include<stdlib.h>
#include <assert.h>

struct Event_st{
	// Either an ARRIVAL or a DEPARTURE
	char Type;
	int Priority;
	int Time;
	int Duration;
	// The task that the event belongs to.
	Task* Task;
};

struct Task_st{
	int SubTasks;
	int MinDuration;
	int MaxDuration;
};

// Creates an instance of a Task object.
Task* Task_Create(int subTasks, int minDuration, int maxDuration);

// Destroys an instance of a Task object.
void Task_Destroy(Task* task);

// Creates and instance of Event given the type, priority, time, and duration.
Event* Event_Create(char type, int priority, int time, int duration, Task* task);

// Destroys the current instance of Event and clicks down the number of subtasks
// inside of it's task. If the subtasks becomes 0, then the function calls
// Task_Destroy.
void Event_Destroy(Event* event);

// Compares two events according to their time. Returns a positive integer if
// event1 has a lower time than event2, a negative integer if event2 has a lower
// time than event1, and 0 if they are equal.
int Event_CompTimePriority(Event* event1, Event* event2);

// Compares two events according to the pointer they point to and their duration.
// If they point to different tasks or they have different durations, the
// function will return FALSE (they are not the same). Otherwise, the function
// will return TRUE (because they are the same).
int Event_CompDurTask(Event* event1, Event* event2);

#endif /* EVENT_INCLUDED */
