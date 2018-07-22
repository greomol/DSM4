#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_ 1

#include "Error.h"

namespace DS {

class Exception 
{
public:
    Exception(Error::Code code, string info) 
    {
        _code = code; _info = info;
    }

    Error::Code getCode() const
    {
        return _code;
    }
 
    string getInfo() const
    {
        return _info;
    }
private: 
    Error::Code _code;
    string _info;
};

} // End of namespace;

#endif
