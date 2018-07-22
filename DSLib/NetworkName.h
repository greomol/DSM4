#ifndef _NETWORK_NAME_H_
#define _NETWORK_NAME_H_ 1

#include <string>
using namespace std;

namespace DS {

class NetworkName
{
public:
    NetworkName() {}
    NetworkName(string const &) {}
    virtual string toString() const = 0;
    virtual void   set(string const &) = 0;

    virtual bool operator ==(NetworkName const &) const = 0;
    virtual bool operator ==(string const &addr) const = 0;
    virtual bool operator !=(NetworkName const &) const = 0;
    virtual bool operator !=(string const &peer_addr) const = 0;

	virtual ~NetworkName() {};
};

} // end of namespace DS

#endif // _NETWORK_NAME_H_


