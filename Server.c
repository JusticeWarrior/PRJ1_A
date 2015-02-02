#include "Server.h"


Server* Server_Create(int processors)
{
  Server* server = malloc(sizeof(Server));
  server -> Available = processors;
  server -> Processors = processors;
  server -> Tasks = NULL;
  return server;
}

void Server_Destroy(Server* server)
{
  ListNode_DestroyList(server->Tasks);
  free(server);
}

//Returns a 1 if busy, a 0 if not
int Server_IsBusy(Server* server)
{
  return (1-server->Available);
}



//Attempts to make the server busy, returns 1 if successful, 0 if the server is alread busy
int Server_AddTask(Server* server, Event* event)
{
  if(server -> Available == 0){return 0;} //Failure, server not available
  if(event == NULL ){return 0;}           //No event was given

  ListNode* node = ListNode_Create(event);
  server->Tasks = ListNode_AppendTail(node, server->Tasks);
  server -> Available = 0;
  return 1;
}

//Removes task from server
void Server_RemoveTask(Server* server, Event* event)
{
  ListNode* shortenedList;

  shortenedList = ListNode_PopHead(server->Tasks);
  ListNode_DestroyList(server->Tasks);
  server->Tasks = shortenedList;

  server -> Available = 1;
}

