#ifndef _SERVER_CONTEXT_H_
#define _SERVER_CONTEXT_H_ 1

#include "Serializer.h"
#include "Thread.h"
#include "Mutex.h"
#include "ServerClientContext.h"
#include "TransportConnectionTCPServer.h"
#include "ExecutorHashTable.h"
#include "ObjectHashTable.h"
#include <string>

#include <vector>
using namespace std;

namespace DS {

class ServerContext
{
public:
    ServerContext(string const &resource);
    virtual ~ServerContext();
    bool needStop() {
        return _stopEvent.isSet();
    }

    TransportConnectionTCPServer *getListenConnection() const {
        return _listenConnection;
    }

    executorPtr find(const string &name, void **context) {
        return _RPCTable.find(name, context);
    }

    uint64 getTimestamp() const {
        return _timestamp;
    }

    void setTimestamp(uint64 timestamp) {
        _timestamp = timestamp;
    }

    uint32 addProcedure(string const &name, executorPtr proc, void *procedureContext);
    uint32 removeProcedure(string const &name);


private:
    uint32 addClient(ServerClientContext *);
    
    static DS_THREAD_PROC listenWorkingThread(void *_this);
    Thread  *_listenThread;
    virtual void  initServerContext() = 0;
    TransportConnectionTCPServer *_listenConnection;
    vector<ServerClientContext *> _clients;   // Не лучшее решение
    ExecutorHashTable _RPCTable;
    Event   _stopEvent;
    uint64 _timestamp;
};

} // end of namespace

#endif // _SERVVER_CONTEXT_H_
