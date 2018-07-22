#include "CRC32.h"

namespace DS
{
	void
	CRC32::initTable()
	{
		if (_table[0] == 0)
		{
			uint32  *p =    _table;
			int             i, j;
			uint32   x;
			for (j = 0; j < 256; j++)
			{
				x = j;
				for (i = 0; i < 8; i++)
				{
					if ((x & 1) != 0)
					{
						x = (x >> 1) ^ 0xEDB88320L;
					}
					else
					{
						x = (x >> 1);
					}
				}

				*p++ = x;
			}
		}
	}

	void
	CRC32::update(const void *ptr, size_t length)
	{
		const uint8 *p = reinterpret_cast<const uint8 *>(ptr);
		uint32       ctmp;
		ctmp = _value;
		while (length >= 8)
		{
			ctmp ^= (uint32) (p[0]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			ctmp ^= (uint32) (p[1]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			ctmp ^= (uint32) (p[2]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			ctmp ^= (uint32) (p[3]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			ctmp ^= (uint32) (p[4]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			ctmp ^= (uint32) (p[5]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			ctmp ^= (uint32) (p[6]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			ctmp ^= (uint32) (p[7]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			p += 8;
			length -= 8;
		}

		while (length)
		{
			ctmp ^= (uint32) (p[0]);
			ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
			p++;
			length--;
		}

		_value = ctmp;
	}

	uint32 CRC32::_table[0x100] = { 0 };
};
