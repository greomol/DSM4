#include "NetworkNameIPV4.h"

namespace DS {

NetworkNameIPV4::NetworkNameIPV4()
{
    _name = "";
}

NetworkNameIPV4::~NetworkNameIPV4()
{
}


NetworkNameIPV4::NetworkNameIPV4(string const &name)
{
    _name = name;
}

string 
NetworkNameIPV4::toString() const
{
    return _name;
}

void   
NetworkNameIPV4::set(string const &name)
{
    _name = name;
}

bool 
NetworkNameIPV4::operator ==(NetworkName const &oth) const
{
    return _name == oth.toString(); 
}

bool 
NetworkNameIPV4::operator ==(string const &addr) const
{
    return _name == addr;
}

bool 
NetworkNameIPV4::operator !=(NetworkName const &oth) const
{
    return _name != oth.toString();
}

bool 
NetworkNameIPV4::operator !=(string const &addr) const
{
    return _name != addr;
}


} // end of namespace DS

