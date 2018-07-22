#include "Types.h"
#include <iostream>
#include <stdio.h>


#include "TransportConnectionTCP.h"
#include "Error.h"

#if DS_OS == DS_OSWINDOWS
#include <winsock2.h>
inline int getSocketError() { return ::WSAGetLastError() ;}
#else
#include <errno.h>
#include <unistd.h>
inline int getSocketError() { return errno; }
inline int closesocket(int h) { return close(h); }
typedef int SOCKET;
#include <netdb.h>
#endif

namespace DS {

static void windowsStartup()
{
#if DS_OS == DS_OSWINDOWS
    static bool started = false;
    if (!started)
    {
        WSADATA wdata;

        for (WORD ver = 3; ver > 0; ver--)
        {
            for (WORD subver = 255; subver >= 1; subver--)
            {
                if (::WSAStartup(ver + subver * short(256), &wdata) == 0)
                {
                    started = true;
                    return;
                }
            }
        } 
    }
#endif
}
  
string            
TransportConnectionTCP::getLocalName()
{
    static string _my_name;
	windowsStartup();
    char    name[256]; 
    if (_my_name.empty())
    {   
        ::gethostname(name, sizeof name);
        _my_name = name;
    }
    return _my_name;
}

string
TransportConnectionTCP::getIPByName(string const &name)
{
    struct hostent  *he = ::gethostbyname(name.c_str());
    if (he)
    {
        char        *z = he->h_addr;
        char buf[128];
        sprintf(buf, "%d.%d.%d.%d", z[0] & 0xFF, z[1] & 0xFF, z[2] & 0xFF, z[3] & 0xFF);
        return buf;
    }
    return "";
}


TransportConnectionTCP::TransportConnectionTCP()  : _peer_ip("")
{
    windowsStartup();
    _socket = 0;
    _errno = 0;
    _sys_errno = 0;
    _service = 0;
    _status = 0;
}

TransportConnectionTCP::~TransportConnectionTCP()
{
}

uint32
TransportConnectionTCP::close()
{
    _errno = Error::OK;
    _sys_errno = 0;
    ::closesocket((SOCKET)_socket);
    _socket = 0;
    _status = 0;
    _peer_ip.set("");
    return 0;
}

uint32
TransportConnectionTCP::read(void *data, uint32 bytes)
{
	int result;

    result = ::recv((SOCKET)_socket, (char *)data, bytes, 0);
		
	if (result < (int)bytes)
    {
        _sys_errno = getSocketError();
		_errno = Error::SocketError;
		cout << "Read error occured: " << Error::explain(_errno) << " " << "syserr=" << _sys_errno << "\n";
		return 0;
    }
	else 
	{
    	 _sys_errno = 0;
		 _errno = Error::OK;
		 return bytes;
	}
}

uint32
TransportConnectionTCP::write(const void *data, uint32 bytes)
{
    int result;

    result = send((SOCKET)_socket, (const char *)data, bytes, 0);

    if (result < (int)bytes)
    {
        _sys_errno = getSocketError();
        _errno = Error::SocketError;
        cout << "Write error occured: " << Error::explain(_errno) << " " << "syserr=" << _sys_errno << "\n";
        return 0;
    }
    else 
    {
        _sys_errno = 0;
        _errno = Error::OK;
        return bytes;
    }
}


} // end of namespace DS

