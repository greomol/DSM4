#include "NetworkAddress.h"

namespace DS {

NetworkAddress::NetworkAddress()
{
}

NetworkAddress::~NetworkAddress()
{
}

string 
NetworkAddress::toString() const
{
    return _name;
}

void NetworkAddress::set( string const& name )
{
    _name = name;
}

NetworkAddress::NetworkAddress(string const &name)
{
    _name = name;
}

} // end of namespace DS
