#include "MetaServerContext.h"
#include "MetaRPC.h"

MetaServerContext::MetaServerContext(string const &resource) : ServerContext(resource)
{
	_scheduler = new MetaScheduler();
	initServerContext();
}

MetaServerContext::~MetaServerContext()
{
	delete _scheduler;
}

void
MetaServerContext::initServerContext()
{
	initProcedureTables((void *)_scheduler);
}

void MetaServerContext::initProcedureTables(void *context)
{
	addProcedure("Meta_AnnounceNodeReady", RPC_Meta_AnnounceNodeReady, context);
	addProcedure("Meta_AnnounceNodeLeave", RPC_Meta_AnnounceNodeLeave, context);
	addProcedure("Meta_PrepareTask", RPC_Meta_PrepareTask, context);
	addProcedure("Meta_LaunchTask", RPC_Meta_LaunchTask, context);
	addProcedure("Meta_TaskCompleted", RPC_Meta_TaskCompleted, context);
}

