#include "TransportConnectionTCPClient.h"
#include "Error.h"
#include "Exception.h"
#include <iostream>

#if DS_OS == DS_OSWINDOWS
#include <winsock2.h>
inline int getSocketError() { return ::WSAGetLastError() ;}
#endif

namespace DS {

TransportConnectionTCPClient::TransportConnectionTCPClient(string const &name, string const &resource)
{
    _peer_ip = name;
    _service = atoi(resource.c_str());
    SOCKET             h;
    struct sockaddr_in  stLclAddr;
//  int                 wAddrLen = sizeof(stLclAddr);
    unsigned long       wOpt = 1;
    h = ::socket(PF_INET, SOCK_STREAM, 0);
    if (h == INVALID_SOCKET)
    {
        _errno = Error::ResourceNotFound;
        _sys_errno = ::getSocketError();
        //cout << "socket error occured: " << Error::explain(_errno) << " " << "syserr=" << _sys_errno << "\n";
		throw Exception(Error::SocketError, "TransportConnectionTCPClient: Can't create socket");
    }

    stLclAddr.sin_addr.s_addr = ::inet_addr(name.c_str());
    stLclAddr.sin_family = AF_INET;
    stLclAddr.sin_port = (u_short)htons((u_short)_service);
    wOpt = 1;
    if(::setsockopt(h, SOL_SOCKET, SO_REUSEADDR, (char *) &wOpt, sizeof wOpt)==SOCKET_ERROR)
	{
        _sys_errno = ::getSocketError();
        _errno = Error::SocketError;
        ::closesocket(h);
        //cout << "setsockopt error occured: " << Error::explain(_errno) << " " << "syserr=" << _sys_errno << "\n";
		throw Exception(Error::SocketError, "TransportConnectionTCPClient: setsockopt failed");
    }
 
	if (::setsockopt(h, SOL_SOCKET,SO_KEEPALIVE,(char *) &wOpt, sizeof wOpt))
	{
        _sys_errno = ::getSocketError();
        _errno = Error::SocketError;
        ::closesocket(h);
		throw Exception(Error::SocketError, "TransportConnectionTCPClient: setsockopt failed");
    }
 

    if (ConnectBlocking(h, (struct ::sockaddr *) &stLclAddr, sizeof(stLclAddr))==SOCKET_ERROR)
    {
        ::closesocket(h);
		throw Exception(Error::ConnectionFailed, "TransportConnectionTCPClient: connect failed");
    }
    else
    {
        _errno = Error::OK;
        _sys_errno = 0;
    }
    _socket = h;
}

TransportConnectionTCPClient::~TransportConnectionTCPClient()
{
    ::closesocket((SOCKET)_socket);
}

int TransportConnectionTCPClient::ConnectBlocking(int socket, struct ::sockaddr* serverAddress, int serverLen)
{
    int result;

    result = ::connect(socket, serverAddress, serverLen);

    if (result < 0)
    {
        _sys_errno = getSocketError();
        _errno = Error::SocketError;
        closesocket(socket);
        //cout << "Connect error ocurred: " << Error::explain(_errno) << " " << "syserr=" << _sys_errno << "\n";
        return SOCKET_ERROR;
    }

    else
    {
        return 0;
    }

}

} // end of namespace DS
