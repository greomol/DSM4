#ifndef _ERROR_H_
#define _ERROR_H_ 1


#include "Types.h"

#include <string>
using namespace std;

namespace DS {

class Error 
{
public:
  enum Code 
  {
    OK,
    NotExpectedType,
    ReadAttemptOutOfBounds,
    ObjectIsNULL,
    ResourceNotFound,
    ResourceInUse,
    PrematureEndOfStream,
    SizeTooBig,
    YetNotImplemented,
    DuplicateItems,
	ItemNotFound,
	QueueIsEmpty,


    // Network errors
    SocketError = 0x200,
	ConnectionFailed,
	ConnectionInUse,
    TimeOut,
	NotConnected,
  };
  
  static string explain(int32 code) 
  {
    switch (code) {
    case OK: return "OK";
    case NotExpectedType: return "Not expected type";
    case ObjectIsNULL: return "Object is NULL";
    case ResourceInUse: return "Resource In Use";
    case ResourceNotFound: return "Resource Not Found";
    case SizeTooBig: return "Size Too Big";
    case PrematureEndOfStream: return "Premature End Of Stream";
    case YetNotImplemented: return "Yet Not Implemented";
    case SocketError: return "Socket Error";
    case TimeOut: return "TimeOut";
    case DuplicateItems: return "Duplicate items";
	case ItemNotFound: return "Item not found";
	case QueueIsEmpty: return "Queue is empty";
	case NotConnected: return "Not connected";
    default: return "@Not known error@";
    }
  }
};

}; // End of namespace
#endif // _ERROR_H_
