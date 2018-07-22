#include "ServerContext.h"
#include "ServerClientContext.h"
#include "Mutex.h"
#include "PacketHeader.h"
//#include "builtinRPC.h"



namespace DS {


DS_THREAD_PROC clientThreadProc(void *_this)
{
    ServerClientContext *t = reinterpret_cast<ServerClientContext *>(_this);
    fprintf(stderr,"ClientThread started\n");
    // Получаем сообщения от клиентов и обрабатываем их.
    try
    {

        while (!t->serv->needStop())
        {
            uint32 code;
            if ( (code = t->readInput()) != Error::OK)
            {
                fprintf(stderr,"ClientThread: readInput failed with code '%s'\n", Error::explain(code).c_str());
                break;
            }
            if ( (code = t->serveRequest()) != Error::OK)
            {
                fprintf(stderr,"ClientThread: serveRequest failed with code '%s'\n", Error::explain(code).c_str());
            }
            if ( (code = t->sendResults()) != Error::OK)
            {
                fprintf(stderr,"ClientThread: sendResults failed with code '%s'\n", Error::explain(code).c_str());
            }
        }
    } 
    catch (Exception const &ex)
    {
        fprintf(stderr,"ClientThread: caught exception code='%s'\n", Error::explain(ex.getCode()).c_str());
        // Какой-то лог
    }
    catch (Error::Code &e)
    {
        fprintf(stderr,"ClientThread: caught error code='%s'\n", Error::explain(e).c_str());
        // Какой то другой лог
    }
    // @@ Должны убрать клиента из списка клиентов.
    if (t->conn != NULL)
    {
        t->conn->close();
        delete t->conn;
    }

    fprintf(stderr,"ClientThread: ended\n");
    return 0;
}

DS_THREAD_PROC
ServerContext::listenWorkingThread(void *_this)
{
    ServerContext *t = reinterpret_cast<ServerContext *>(_this);
    NetworkAddress clientAddress;
    fprintf(stderr,"listenThread: started\n");
    try
    {
        while (!t->_stopEvent.isSet())
        {
            TransportConnection *conn = t->getListenConnection()->waitIncomingAndAcceptIt(clientAddress);
            if (conn != NULL)
            {
                Thread *clientThread = new Thread();
                ServerClientContext *clientThreadData = new ServerClientContext();
                clientThreadData->clientAddress = clientAddress;
                clientThreadData->conn = conn;
                clientThreadData->serv = t;
                clientThreadData->thread = clientThread;
                clientThread->start(clientThreadProc, clientThreadData);
                // Добавить клиента к активным
                t->addClient(clientThreadData);
            }
            Thread::sleep(10);
        }
    }
    catch (Exception const &ex)
    {
        fprintf(stderr,"listenThread: caught exception code='%s'\n", Error::explain(ex.getCode()).c_str());
        // Какой-то лог
    }
    catch (Error::Code &e)
    {
        fprintf(stderr,"listenThread: caught error code='%s'\n", Error::explain(e).c_str());
        // Какой то другой лог
    }
    fprintf(stderr,"listenThread ended\n");
    return 0;
}


uint32
ServerContext::addProcedure(string const &name, executorPtr proc, void *procedureContext)
{
	void *oldContext;
    if (_RPCTable.find(name, &oldContext) != NULL)
    {
        return Error::DuplicateItems;
    }
    _RPCTable.feed(name, proc, procedureContext);
    return Error::OK;
}


ServerContext::ServerContext(string const &resource)  : _RPCTable(73)
{
	_timestamp = 0;
    _stopEvent.reset();
    // initServerContext();
    _listenConnection = new TransportConnectionTCPServer(resource);
    _listenThread = new Thread();
    _listenThread->start(listenWorkingThread, this);
}

ServerContext::~ServerContext()
{
    _stopEvent.set();
    _listenThread->wait();
    delete _listenThread;
    _listenThread = NULL;

    delete _listenConnection;
    _listenConnection = NULL;
}

uint32
ServerContext::addClient(ServerClientContext *client)
{
    _clients.push_back(client);
    return 0;
}

} // end of namespace DS
