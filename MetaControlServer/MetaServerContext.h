#ifndef _META_SERVER_CONTEXT_H_
#define _META_SERVER_CONTEXT_H_	1

#include "ServerContext.h"
#include "MetaScheduler.h"
#include <string>

class MetaServerContext :
	public DS::ServerContext
{
public:
	MetaServerContext(string const &resource);
	virtual ~MetaServerContext();
	void initServerContext();
	void initProcedureTables(void *context);
	MetaScheduler *getMetaScheduler() const { return _scheduler; }
private:
	MetaScheduler *_scheduler;
};

#endif
