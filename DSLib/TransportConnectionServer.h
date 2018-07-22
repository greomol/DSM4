#pragma once

#include "TransportConnection.h"

namespace DS {

class TransportConnectionServer :
    public TransportConnection
{
public:
    TransportConnectionServer(string const &resource);      // Либо имя сокета либо номер порта
    virtual ~TransportConnectionServer();
    virtual TransportConnection     *waitIncomingAndAcceptIt() = 0;
    virtual uint32          close () = 0;
    virtual uint32          read (void *data, uint32 bytes) = 0;
    virtual uint32          readPeek (void *data, uint32 bytes) = 0;
    virtual uint32          write (const void *data, uint32 bytes) = 0;    // to peer
    virtual uint32          bytesCouldRead () = 0; 
private:
    typedef uint64 SOCKET_HOLDER;
    SOCKET_HOLDER _server_socket;
};

} // end of namespace DS
