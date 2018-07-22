#ifndef _TRANSPORT_CONNECTION_TCP_SERVER_H_
#define _TRANSPORT_CONNECTION_TCP_SERVER_H_ 1

#include "TransportConnectionTCP.h"
#include "NetworkAddress.h"

namespace DS {

class TransportConnectionTCPServer :
    public TransportConnectionTCP
{
public:
    TransportConnectionTCPServer(string const &resource);
    virtual ~TransportConnectionTCPServer();
    TransportConnection     *waitIncomingAndAcceptIt(NetworkAddress &);
};

} // end of namespace DS

#endif // _TRANSPORT_CONNECTION_TCP_SERVER_H_
