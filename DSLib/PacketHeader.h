#ifndef _PACKET_HEADER_H_
#define _PACKET_HEADER_H_ 1

#include "Types.h"

namespace DS {

class PacketHeader
{
public:
    PacketHeader(const byte *bytes, uint32 size);
    PacketHeader(uint32 _length, uint32 _flags, uint32 _crc32, uint64 _timestamp) :length(_length), flags(_flags), crc32(_crc32), timestamp(_timestamp) {}
    ~PacketHeader();
    bytevector serialize();
    static const uint32 size = 4*(1 + sizeof(uint32)) + 1 + sizeof(uint64);
    bool isValid() const { return magic == MAGIC; }
    uint32 magic;
    uint32 length;
    uint32 flags;
    uint32 crc32;
	uint64 timestamp;
    static const uint32 MAGIC = 0x45564332;
};

} // end of namespace DS

#endif // _PACKET_HEADER_H_

