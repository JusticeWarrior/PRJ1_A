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
