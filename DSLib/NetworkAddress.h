#ifndef _NETWORK_ADDRESS_H_
#define _NETWORK_ADDRESS_H_ 1

#include <string>
using namespace std;

namespace DS {

class NetworkAddress
{
public:
    NetworkAddress();
    NetworkAddress(string const &name);
    virtual ~NetworkAddress();
    virtual string toString() const;
    void set( string const& name );
private:
    string _name;
};

} // end of namespace DS

#endif // _NETWORK_ADDRESS_H_
