#include "Server.h"


Server* Server_Create(int processors)
{
  Server* server = malloc(sizeof(Server));
  server -> Available = processors;
  server -> Processors = processors;
  server -> SubTasks = NULL;
  server-> Tail = NULL;
  return server;
}

//Removes the specified node from the list, returning the new list.
//If the node to be removed is the head, then prev is NULL
static ListNode* Server_RemoveNode(ListNode* list, ListNode* prev, ListNode* node);

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
  int length = ListNode_GetLength(task);
  assert(length <= server->Available); //Too many subtasks, not enough processors
  assert(task->Event->Type == ARRIVAL); //Use Server_RemoveSubTask for departures

  if(server->SubTasks == NULL)
  {
    server-> Tail = ListNode_AppendTail(task, server->SubTasks);
    server->SubTasks = server->Tail;
  }
  else
  {
    server-> Tail = ListNode_AppendTail(task, server->Tail);
  }
  
  server -> Available -= length;
}

//DEPRICATED Removes task from server
void Server_RemoveTask(Server* server, Event* event)
{
  assert(0); //Depricated function!
  ListNode* shortenedList;

  shortenedList = ListNode_PopHead(server->SubTasks);
  ListNode_DestroyList(server->SubTasks);
  server->SubTasks = shortenedList;

  server -> Available = 1;
  
  Event_Destroy(event);
}

void Server_RemoveSubTask(Server* server, ListNode* departure)
{
  ListNode* node = server -> SubTasks;
  ListNode* prev = NULL;
  while(ListNode_CompDurTask(departure, node) != 1)
  {
    prev = node;
    node = node -> Next;
  }
  server-> SubTasks = Server_RemoveNode(server->SubTasks, prev, node);
  ListNode_DestroyList(node);
  server -> Available++;
}

void Server_PrintState(Server* server)
{
  printf("PRINTING SERVER DATA\n");
  printf("TOTAL CORES:     %d\n",server->Processors);
  printf("AVAILABLE CORES: %d\n",server->Available);
  printf("USED CORES:      %d\n",server->Processors - server->Available);
  ListNode_PrintList(server->SubTasks, "SERVER SUBTASK LIST"); 
}

static ListNode* Server_RemoveNode(ListNode* list, ListNode* prev, ListNode* node)
{
  if(node==NULL)
  {
    return list;
  }
  if(prev==NULL)
  {
    return node;
  }
  else
  {
    prev->Next = node->Next;
    node->Next = NULL;
    return list;
  }
}
