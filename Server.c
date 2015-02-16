#include "Server.h"


Server* Server_Create(int processors)
{
  Server* server = malloc(sizeof(Server));
  server -> Available = processors;
  server -> Processors = processors;
  server -> SubTasks = NULL;
  return server;
}

void Server_Destroy(Server* server)
{
  ListNode_DestroyList(server->SubTasks);
  free(server);
}

//Returns a 1 if busy, a 0 if not
int Server_IsBusy(Server* server)
{
  return (server->Available == server->Processors ? 0 : 1);
}



void Server_AddTask(Server* server, ListNode* task)
{
  /*  FIX THIS STUFF
  if(server -> Available == 0){return 0;} //Failure, server not available
  if(event == NULL ){return 0;}           //No event was given

  ListNode* node = ListNode_Create(event);
  server->Tasks = ListNode_AppendTail(node, server->Tasks);
  server -> Available = 0;
  return 1;
  */
}

//DEPRICATED Removes task from server
void Server_RemoveTask(Server* server, Event* event)
{
  ListNode* shortenedList;

  shortenedList = ListNode_PopHead(server->SubTasks);
  ListNode_DestroyList(server->SubTasks);
  server->SubTasks = shortenedList;

  server -> Available = 1;
  
  Event_Destroy(event);
}

void Server_RemoveSubTask(Server* server, ListNode* departure)
{

}
