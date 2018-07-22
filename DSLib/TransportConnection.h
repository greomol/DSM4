#ifndef _TRANSPORT_CONNECTION_H_
#define _TRANSPORT_CONNECTION_H_ 1

#include "Types.h"

namespace DS {

class TransportConnection
{
public:
    TransportConnection(void);
    virtual ~TransportConnection(void);
    // Ìועמהא open חהוסü םוע!
    virtual uint32          close () = 0;
    virtual uint32          read (void *data, uint32 bytes) = 0;
//    virtual uint32          readPeek (void *data, uint32 bytes) = 0;
    virtual uint32          write (const void *data, uint32 bytes) = 0;    // to peer
//    virtual uint32          bytesCouldRead () = 0; 
};

} // end of namespace DS


#endif // _TRANSPORT_CONNECTION_H_

