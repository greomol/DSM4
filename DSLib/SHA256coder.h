#ifndef _SHA256coder_H_
#define _SHA256coder_H_ 1

#include "CLBase.h"
#include <vector>
using namespace std;

namespace CLib
{
    class CSHA256Coder
    {
    public:
        enum {DIGESTSIZE = 32};
        CSHA256Coder()
        {
	    Init();
        }

        void Init();
        void Update(const void* data, size_t size);
        vector<char>    Final();
    private:
        static const unsigned int K[64];
        unsigned int _state[8];
        CLib::uint64 _count;
        char        _buffer[64];
        static void Transform(unsigned int *digest, const unsigned int *data);
        void        WriteByteBlock();
    };
};

#endif


