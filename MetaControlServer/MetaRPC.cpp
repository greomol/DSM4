#include "Types.h"
#if DS_OS == DS_OSWINDOWS
#include <Windows.h>
#endif

#include "MetaRPC.h"
#include "MetaServerContext.h"
#include <iostream>
using namespace std;


int32 RPC_Meta_AnnounceNodeReady(void * context, Deserializer const &des, 
                Serializer &ser)
{
    MetaScheduler *s = (MetaScheduler *)context; s = s;
    string nodeName    = des.getString();
    string nodeOS      = des.getString();
    uint32 nodeBitness = des.getUint32();
    uint32 nodeMemMB   = des.getUint32();
    uint32 numOfCPUs   = des.getUint32();
    ser.putUint32(Error::OK);
    return 0;
}

int32 RPC_Meta_AnnounceNodeLeave(void * context, Deserializer const &des, 
							Serializer &ser)
{
    MetaScheduler *s = (MetaScheduler *)context;
    string nodeName = des.getString();
    uint32 flags    = des.getUint32();
    ser.putUint32(Error::OK);
    return 0;
}


int32 RPC_Meta_PrepareTask(void * context, Deserializer const &des, 
							Serializer &ser)
{
    MetaScheduler *s = (MetaScheduler *)context;
    string nodeName = des.getString();
    ser.putUint32(Error::OK);
    return 0;
}

int32 RPC_Meta_LaunchTask(void * context, Deserializer const &des, 
							Serializer &ser)
{
    MetaScheduler *s = (MetaScheduler *)context;
    string nodeName = des.getString();
    DS::uint64 serial;
    MetaQueueItem qi;
    DS::uint32 code = s->dequeueFromInputQueue(qi, serial);
    if (code == DS::Error::OK) {
        ser.putUint32(Error::OK);
        ser.putUint64(serial);
        ser.putSerializer(qi.ser);
        s->enqueueToPendingQueue(qi, serial);
    } else {
        ser.putUint32(code);
    }
    return 0;
}


int32 RPC_Meta_TaskCompleted(void * context, Deserializer const &des, 
						  Serializer &ser)
{
    MetaScheduler *s = (MetaScheduler *)context;
    string nodeName = des.getString();
    Deserializer d = des;
    Deserializer d2;
    d.getDeserializer(d2);
    DS::uint32 err    = d2.getUint32();
    DS::uint64 serial = d2.getUint64();
    s->transferFromPendingQueueToCompletedQueue(serial, des, err);
    ser.putUint32(Error::OK);
    return (int)err;
}

