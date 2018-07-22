#pragma once

#include "Server.h"
#include "Client.h"
#include "MetaServer.h"

class MetaControlServer
{
public:
    MetaControlServer();
    ~MetaControlServer();
    void commandStartServer();
    void commandStopServer();
    void commandClientOpen(string const &name);
    void commandHelp();
    void commandRun(string const &arg);
    bool commandGridOperation(vector<string> const &args);
    bool metaStatus();
    bool metaStart();
    MetaScheduler * getMetaScheduler();
private:
    MetaServer *_server;
    DS::Client *_client;

};
