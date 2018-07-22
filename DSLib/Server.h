#ifndef _SERVER_H_
#define _SERVER_H_ 1

#include "ServerContext.h"

namespace DS {


class Server
{
public:
    Server();
    virtual ~Server();
    virtual uint32 start();
    virtual uint32 stop();
protected:
    ServerContext *_context;
};

} // end of namespace

#endif // _SERVER_H_
