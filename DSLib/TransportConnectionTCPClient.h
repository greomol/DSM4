#ifndef _TRANSPORT_CONNECTION_TCP_CLIENT_H_
#define _TRANSPORT_CONNECTION_TCP_CLIENT_H_ 1
 
#include "TransportConnectionTCP.h"

#if DS_OS == DS_OSWINDOWS
#include <winsock2.h>
#else
#include <errno.h>
#include <unistd.h>
inline int getSocketError() { return errno; }
inline int closesocket(int h) { return close(h); }
typedef int SOCKET;
const int INVALID_SOCKET = -1;
const int SOCKET_ERROR = -1;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

namespace DS {

class TransportConnectionTCPClient :
    public TransportConnectionTCP
{
public:
    TransportConnectionTCPClient(string const &name, string const &resource);
    virtual ~TransportConnectionTCPClient();
	int	ConnectNonBlocking(int socket, struct ::sockaddr* serverAddress, int serverLen);
    int	ConnectBlocking(int socket, struct ::sockaddr* serverAddress, int serverLen);
};

} // end of namespace DS

#endif // _TRANSPORT_CONNECTION_TCP_CLIENT_H_
