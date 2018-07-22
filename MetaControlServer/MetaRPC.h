// Прототипы встроенных RPC процедур
#ifndef _META_RPC_H_
#define _META_RPC_H_ 1

#include "Serializer.h"
using namespace DS;
#define METARPC_TRACE 1

int32 RPC_Meta_AnnounceNodeReady(void *context, Deserializer const &des, Serializer &ser);
int32 RPC_Meta_AnnounceNodeLeave(void *context, Deserializer const &des, Serializer &ser);
int32 RPC_Meta_PrepareTask(void *context, Deserializer const &des, Serializer &ser);
//int32 RPC_Meta_GetTaskData(void *context, Deserializer const &des, Serializer &ser);
int32 RPC_Meta_LaunchTask(void *context, Deserializer const &des, Serializer &ser);
int32 RPC_Meta_TaskCompleted(void *context, Deserializer const &des, Serializer &ser);

// Some control API-s
//int32 RPC_Meta_AddTask(void *context, Deserializer const &des, Serializer &ser);
//int32 RPC_Meta_GetQueueStatus(void *context, Deserializer const &des, Serializer &ser);



#endif
