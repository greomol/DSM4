#include "PacketHeader.h"
#include "Serializer.h"

namespace DS {

PacketHeader::PacketHeader(const byte *bytes, uint32 size)
{
    Deserializer des(bytes, size);
    try 
    {
        magic = des.getUint32();
        length = des.getUint32();
        flags = des.getUint32();
        crc32 = des.getUint32();
		timestamp = des.getUint64();
    } catch (Exception & /*ex*/)
    {
        // Malformed packet
        magic = 0;
    }
    
}

PacketHeader::~PacketHeader()
{
}


bytevector PacketHeader::serialize()
{
    Serializer ser;
    ser.putUint32(MAGIC);
    ser.putUint32(length);
    ser.putUint32(flags);
    ser.putUint32(crc32);
	ser.putUint64(timestamp);
    return ser.get();
}

} // end of namespace DS

