#pragma once

#include "TesterServer.h"
#include "Client.h"
class DSMTester
{
public:
    DSMTester();
    ~DSMTester();
    bool executeCommand(string const &cmd);
private:
    void commandStartServer();
    void commandStopServer();
    void commandClientOpen(string const &name);
    void comandHelp();
    void commandRun(string const &arg);
    DS::Server *_server;
    DS::Client *_client;
};
