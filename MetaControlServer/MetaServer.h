#ifndef _META_SERVER_H_
#define _META_SERVER_H_ 1
#include "Server.h"
#include "MetaScheduler.h"

class MetaServer :
	public DS::Server
{
public:
	MetaServer();
	virtual ~MetaServer();
	virtual DS::uint32 start();
	virtual DS::uint32 stop();
	MetaScheduler *getMetaScheduler() const;
};

#endif // _META_SERVER_H_
