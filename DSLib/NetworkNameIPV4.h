#ifndef _NETWORK_NAME_IPV4_H_
#define _NETWORK_NAME_IPV4_H_ 1

#include "NetworkName.h"


namespace DS {

class NetworkNameIPV4 :
    public NetworkName
{
public:
    NetworkNameIPV4();
    virtual ~NetworkNameIPV4();
    NetworkNameIPV4(string const &);
    string toString() const;
    void   set(string const &);

    bool operator ==(NetworkName const &) const;
    bool operator ==(string const &addr) const;
    bool operator !=(NetworkName const &) const;
    bool operator !=(string const &peer_addr) const;

private:
    string _name;
};

} // end of namespace DS

#endif // _NETWORK_NAME_IPV4_H_

