#ifndef _SERVER_CLIENT_CONTEXT_H_
#define _SERVER_CLIENT_CONTEXT_H_ 1

#include "NetworkAddress.h"
#include "Types.h"
#include "PacketHeader.h"
#include "Serializer.h"

namespace DS {

class ServerContext;
class TransportConnection;
class Thread;

// —ерверный контекст клиента. 
class ServerClientContext
{
public:
    ServerClientContext();
    ~ServerClientContext();
    uint32 readInput();
    uint32 serveRequest();
    uint32 sendResults();
    ServerContext *serv;
    TransportConnection *conn;
    NetworkAddress clientAddress;
    Thread         *thread;
    byte *inputBuffer;  // тело пакета
    uint32 inputBufferUsed;
    uint32 inputBufferAllocated;
    Deserializer inputArguments;
    Serializer  outputResults;
    static const uint32 MAX_BODY_SIZE = 65536*4;
    byte header[PacketHeader::size];
};

}

#endif // _SERVER_CLIENT_CONTEXT_H_
