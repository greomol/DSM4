#ifndef _CLIENT_H_
#define _CLIENT_H_ 1

// Клиент для подключения к серверам

#include "Types.h"
#include "TransportConnection.h"
#include "Serializer.h"

namespace DS {


class Client
{
public:
    Client();
    ~Client();
    uint32 connect(string const &name, string const &resource);
    uint32 disconnect(string const &name);
    uint32 call(string const &name, Serializer const &ser, Deserializer &des);
private:
    TransportConnection *conn;
	uint64 _timestamp;
};

}  // end of namespace DS

#endif // _CLIENT_H_

