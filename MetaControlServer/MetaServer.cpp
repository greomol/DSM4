#include "MetaServer.h"
#include "MetaServerContext.h"

MetaServer::MetaServer() 
{
	_context = new MetaServerContext("5555");
}

MetaServer::~MetaServer()
{
	delete _context;
}

DS::uint32 MetaServer::start()
{
	return DS::Error::OK;
}

DS::uint32 MetaServer::stop()
{
	return DS::Error::OK;
}

MetaScheduler * MetaServer::getMetaScheduler() const
{
	MetaServerContext *c = dynamic_cast<MetaServerContext *>(_context);
	return c->getMetaScheduler();
}

