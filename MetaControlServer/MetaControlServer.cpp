#include <iostream>
using namespace std;
#include "MetaControlServer.h"
#include "MetaServer.h"
#include "Types.h"
#include "Error.h"
#include "Serializer.h"
#include "Exception.h"
#include <cmath>
#pragma warning(disable: 4127)
#pragma warning(disable: 4244)
#pragma warning(disable: 4100)
#pragma warning(disable: 4189)
#pragma warning(disable: 4996)

MetaControlServer::MetaControlServer() {
    _server = NULL;
}

MetaControlServer::~MetaControlServer()	{ }

void 
MetaControlServer::commandStartServer() {
    if (_server == NULL) {
        _server = new MetaServer();
    }
    DS::uint32 code = _server->start();
    cout << "return code is " << DS::Error::explain(code) << endl;
}

void 
MetaControlServer::commandStopServer() {
    DS::uint32 code = DS::Error::ObjectIsNULL;
    if (_server != NULL) {
        code = _server->stop();
        delete _server;
    }
    _server = NULL;
    cout << "return code is " << DS::Error::explain(code) << endl;
}


bool MetaControlServer::metaStatus() {
	string status = _server->getMetaScheduler()->getStatus();
	cout << "Meta status: " << status << endl;
	return true;
}

bool MetaControlServer::metaStart()	{
	return true;
}

MetaScheduler * MetaControlServer::getMetaScheduler() {
	return _server->getMetaScheduler();
}

