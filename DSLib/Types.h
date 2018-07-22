#ifndef _DS_TYPES_H_
#define _DS_TYPES_H_ 1

#define DS_OSWINDOWS 1
#define DS_OSLINUX   2
#define DS_OSMACOS   3

#undef DS_OS
#ifdef _WIN32
#define DS_OS DS_OSWINDOWS
#endif
#ifdef _MACOSX
#define DS_OS DS_OSMACOS
#endif

#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
#define DS_OS DS_OSMACOS
#endif


#include <vector>
using namespace std;
namespace DS {
    typedef int int32 ;
    typedef unsigned uint32 ;
    typedef unsigned char byte  ;
    typedef unsigned char uint8;
    typedef signed char   int8;
    typedef long long int64 ;
    typedef unsigned long long uint64 ;
    typedef vector<byte> bytevector;
}

#endif
