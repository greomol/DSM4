#ifndef _CRC32Coder_H_
#define _CRC32Coder_H_ 1

#include "Types.h"
#include <vector>
using namespace std;

namespace DS
{
	class CRC32
	{
	public:
		CRC32()
		{
			initTable();
			_value = 0xFFFFFFFFU;
		}
		
        void update(const void* data, size_t size);
		uint32		final()
		{
			return _value ^ 0xFFFFFFFFU;
		}
        
        uint32 getTableCode(int x)
        {
            if (x >= 0 && x < 256)
            {
                return _table[x];
            }
            return 0x55AA;
        }
	private:
		uint32          _value;
		void initTable();
		static uint32   _table[0x100];
	};
};

#endif


