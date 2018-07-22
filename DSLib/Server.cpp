#include "Server.h"
#include "Thread.h"
#include "Error.h"


namespace DS {

Server::Server()
{
	_context = NULL; // new ServerContext();
}

Server::~Server()
{
    delete _context;
}

uint32
Server::start()
{
    return Error::OK;
}

uint32
Server::stop()
{
    return Error::OK;
}

} // end of namespace
