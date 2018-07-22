#ifndef _METAQUEUEITEM_H_
#define _METAQUEUEITEM_H_ 1

#include "Serializer.h"
class MetaQueueItem
{
public:
	MetaQueueItem();
	virtual ~MetaQueueItem();
	DS::Serializer ser;
	DS::Deserializer des;
};

#endif
 
