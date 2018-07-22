#include "TransportConnectionTCPServer.h"
#include "Error.h"
#include "NetworkAddress.h"
#include <iostream>
#include <errno.h>

#if DS_OS == DS_OSWINDOWS
#include <winsock2.h>
inline int getSocketError() { return ::WSAGetLastError() ;}
#ifndef EWOULDBLOCK
# define EWOULDBLOCK WSAEWOULDBLOCK
#endif
#ifndef EADDRINUSE
# define EADDRINUSE WSAEADDRINUSE
#endif
#else
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

static SOCKET
piper_creat_server_listener(const string &server,
    int			 resource,
    uint32      &piper_errno,
    uint32      &sys_error,
    DS::NetworkAddress const&   /* ip */
    )
{
    SOCKET              h;
    struct sockaddr_in     stLclAddr;
    int                 wAddrLen = sizeof(stLclAddr);
    unsigned long       wOpt = 1;

    h = socket(PF_INET, SOCK_STREAM, 0);
    if (h == INVALID_SOCKET)
    {
        piper_errno = DS::Error::ResourceNotFound;
        sys_error = ::getSocketError();
        return INVALID_SOCKET;
    }

#if DS_OS == DS_OSWINDOWS
	stLclAddr.sin_addr.S_un.S_addr = inet_addr(server.c_str()); // inet_addr()
#else
    if (inet_aton(server.c_str(), &stLclAddr.sin_addr) == 0) {
    	sys_error = ::getSocketError();
        return INVALID_SOCKET;
    }
#endif
    sys_error = ::getSocketError();
    stLclAddr.sin_family = PF_INET;
    stLclAddr.sin_port = (u_short)htons((u_short)resource);
    wOpt = 1;
    if(::setsockopt(h, SOL_SOCKET, SO_REUSEADDR, (char *) &wOpt, sizeof wOpt)==SOCKET_ERROR) {
        sys_error = ::getSocketError();
        piper_errno = Error::SocketError;
        ::closesocket(h);
        return INVALID_SOCKET;
    }
    if (::bind(h, (struct ::sockaddr *) &stLclAddr, wAddrLen) == SOCKET_ERROR)
    {
        sys_error = ::getSocketError();
        if (sys_error == EADDRINUSE)
        {
            piper_errno = DS::Error::ResourceInUse;
        }
        else
        {
            piper_errno = DS::Error::ResourceNotFound;
        }

        ::closesocket(h);
        return INVALID_SOCKET;
    }

    if (::listen(h, 10) == SOCKET_ERROR)
    {
        piper_errno = DS::Error::ResourceNotFound;
        sys_error = ::getSocketError();
        ::closesocket(h);
        return INVALID_SOCKET;
    }


	piper_errno = Error::OK;
    sys_error = 0;
    return h;
}                         

TransportConnectionTCPServer::TransportConnectionTCPServer(string const &resource)
{
    _status = 0;
    _service = atoi(resource.c_str());
    _service_str = resource;
//	_socket = piper_creat_server_listener(getIPByName(getLocalName()), _service, _errno, _sys_errno, _peer_ip);
	_socket = piper_creat_server_listener(getIPByName("0.0.0.0"), _service, _errno, _sys_errno, _peer_ip);
    if (_socket==INVALID_SOCKET)
	{
        cout << "setsockopt error occured: " << Error::explain(_errno) << " " << "syserr=" << _sys_errno << "\n";
		throw(Error::explain(_errno));
	}
	cout << "Server address: " << getIPByName(getLocalName()) << "\n";
}

TransportConnectionTCPServer::~TransportConnectionTCPServer()
{
    close();
}

TransportConnection *TransportConnectionTCPServer::waitIncomingAndAcceptIt(NetworkAddress &addr)
{
    struct sockaddr_in  stRemAddr;
#if DS_OS == DS_OSWINDOWS
    typedef         int socklen_t;
#endif
    socklen_t         wAddrLen = sizeof(stRemAddr);

    if (_socket == 0)
    {
		cout << "NULL Socket \n";
        return NULL;
    }

	SOCKET  connect_socket;

	for (;;)
	{
		if ((connect_socket = ::accept((SOCKET)_socket, (struct ::sockaddr *) &stRemAddr, (socklen_t *)&wAddrLen))==INVALID_SOCKET)
		{
			_sys_errno = ::getSocketError();
			if ((_sys_errno!=EINTR)||(_sys_errno == EWOULDBLOCK))
				continue;

	        if (_sys_errno == EADDRINUSE)
		    {
			    _errno = Error::ResourceInUse;
			}
			else
			{
				_errno = Error::ResourceNotFound;
			}
            cout << "waitIncoming error occured: " << Error::explain(_errno) << " " << "syserr=" << _sys_errno << "\n";
			return NULL;
		}
		else
			break;
	}
    NetworkAddress   temp_ip;
    string buf;
    buf = inet_ntoa(stRemAddr.sin_addr);

    temp_ip.set(buf);
    _peer_ip.set(buf);
    addr.set(buf);
    _errno = Error::OK;
    _sys_errno = 0;
    //return new RTPiperConnection(connect_socket, _service, _peer_ip);
    return new TransportConnectionTCP(connect_socket, _service_str, _peer_ip);  
}

} // end of namespace DS


