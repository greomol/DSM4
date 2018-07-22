#pragma once

#include "Client.h"
#include <string>
using namespace std;

class MetaClient
{
public:
    MetaClient();
    ~MetaClient();
    DS::uint32 connectToServer(string const &serverName);
    DS::uint32 disconnectFromServer(string const &serverName);
    DS::uint32 announceReady(string const &nodeName, string const &nodeOS, DS::uint32 nodeBitness, DS::uint32 nodeMemMB,
		DS::uint32 numOfCPUs);
    DS::uint32 announceLeave(string const &nodeName, DS::uint32 flags);
    DS::uint32 prepareTask(string const &nodeName, DS::Deserializer &des);
    DS::uint32 launchTask(string const &nodeName, DS::Deserializer &des);
    DS::uint32 taskCompleted(string const &nodeName, DS::Serializer &ser);
public:
    DS::Client *_client;
};
