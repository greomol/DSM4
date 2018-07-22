#ifndef _TRANSPORT_CONNECTION_TCP_H_
#define _TRANSPORT_CONNECTION_TCP_H_  1


#include "TransportConnection.h"
#include "NetworkAddress.h"
#include <stdlib.h>

namespace DS {

class TransportConnectionTCP :
    public TransportConnection
{
protected:
    typedef uint64 SOCKET_HOLDER;
public:
    TransportConnectionTCP();
    TransportConnectionTCP(SOCKET_HOLDER socket, string const &service, NetworkAddress const &peer) :
      _socket(socket), _service_str(service), _peer_ip(peer)
    {
        _service = atoi(_service_str.c_str());
    }
    virtual ~TransportConnectionTCP();
    virtual uint32          close ();
    virtual uint32          read (void *data, uint32 bytes);
//    virtual uint32          readPeek (void *data, uint32 bytes);
    virtual uint32          write (const void *data, uint32 bytes);    // to peer
//    virtual uint32          bytesCouldRead (); 
    static string            getLocalName();
    static string            getIPByName(string const &name);
protected:
    SOCKET_HOLDER   _socket;
    uint32          _errno;
    uint32          _sys_errno;
    NetworkAddress  _peer_ip;
    uint32          _service;
    string          _service_str;
    uint32          _status;

};

} // end of namespace DS

#endif // _TRANSPORT_CONNECTION_TCP_H_
