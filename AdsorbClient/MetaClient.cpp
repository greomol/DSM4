#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <assert.h>
#include <time.h>

#include <vector>
using namespace std;

#include "MetaClient.h"
#include "Thread.h"
using namespace DS;

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

MetaClient::MetaClient()
{
    _client = NULL;
}

MetaClient::~MetaClient()
{
}

DS::uint32 
MetaClient::connectToServer(string const &serverName)
{
    _client = new DS::Client();
    _client->connect(serverName, "5555");
    return DS::Error::OK;
}

DS::uint32 
MetaClient::disconnectFromServer(string const &serverName)
{
    _client->disconnect(serverName);
    delete _client;
    return DS::Error::OK;
}

DS::uint32 
MetaClient::announceReady(string const &nodeName, string const &nodeOS, DS::uint32 nodeBitness, DS::uint32 nodeMemMB,
   DS::uint32 numOfCPUs)
{
    DS::Serializer ser;
    DS::Deserializer des;
    ser.putString(nodeName);
    ser.putString(nodeOS);
    ser.putUint32(nodeBitness);
    ser.putUint32(nodeMemMB);
    ser.putUint32(numOfCPUs);
    _client->call("Meta_AnnounceNodeReady", ser, des);
    DS::uint32 res = des.getUint32();
    cout << "Call announceNodeReady = " << res << endl;
    return DS::Error::OK;
}

DS::uint32 
MetaClient::announceLeave(string const &nodeName, DS::uint32 flags)
{
    DS::Serializer ser;
    DS::Deserializer des;
    ser.putString(nodeName);
    ser.putUint32(flags);
    _client->call("Meta_AnnounceNodeLeave", ser, des);
    DS::uint32 res = des.getUint32();
    cout << "Call announceNodeLeave = " << res << endl;
    return DS::Error::OK;
}

//int32 RPC_Meta_PrepareTask(void *context, Deserializer const &des, Serializer &ser);
////int32 RPC_Meta_GetTaskData(void *context, Deserializer const &des, Serializer &ser);
//int32 RPC_Meta_LaunchTask(void *context, Deserializer const &des, Serializer &ser);
//int32 RPC_Meta_TaskCompleted(void *context, Deserializer const &des, Serializer &ser);

DS::uint32 
MetaClient::prepareTask(string const &nodeName, DS::Deserializer &des)
{
    DS::Serializer ser;
    ser.putString(nodeName);
    _client->call("Meta_PrepareTask", ser, des);
    return DS::Error::OK;
}

DS::uint32 
MetaClient::launchTask(string const &nodeName, DS::Deserializer &des)
{
    DS::Serializer ser;
    ser.putString(nodeName);
    _client->call("Meta_LaunchTask", ser, des);
    return DS::Error::OK;
}

DS::uint32 
MetaClient::taskCompleted(string const &nodeName, DS::Serializer &ser)
{
    DS::Deserializer des;
    DS::Serializer s2;
    s2.putString(nodeName);
    s2.putSerializer(ser);
    _client->call("Meta_TaskCompleted", s2, des);
    return DS::Error::OK;
}

