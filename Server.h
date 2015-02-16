#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED 

typedef struct Server_st Server;

#include "Event.h"
#include "FEL.h"
#include "Queue.h"
#include "SimulationData.h"
#include "ListNode.h"

struct Server_st{
  int Processors;  //The total number of processors this server has
  int Available;   //The number of available processors
  ListNode* SubTasks; //A list of subtasks currently in the server
};

//Create a Server structure with the given number of processors
Server* Server_Create(int processors);

//Destroy the given Server structure
void Server_Destroy(Server* server);

//Returns a 1 if there is anything in the server
int Server_IsBusy(Server* server);

//Adds a list of subtasks to the server, assuming there are an ample number
//of processors available
void Server_AddTask(Server* server, ListNode* task);

//DEPRICATED Removes task from server
void Server_RemoveTask(Server* server, Event* event);

//Remove a subtask from a server correspoding to the departure given
void Server_RemoveSubTask(Server* server, ListNode* departure);



#endif /* SERVER_INCLUDED */
