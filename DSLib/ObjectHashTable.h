#pragma once
#include <vector>

using namespace std;

#include "Serializer.h"
#include "Mutex.h"

namespace DS {

struct objhashItem
{
	string name;
	void* object;
	objhashItem *link;
	
	objhashItem(string const &name, void* object, objhashItem *link = NULL)
	{
		this->name   = name;
		this->object = object;
		this->link   = link;
	}
};


struct objhashBucket
{
	objhashItem* list;
	Mutex mutex;

	objhashBucket()
	{
		list = NULL;
	}
};


// Fixed size hash table for getting pointer to object (e.g. mutex) by its name
class ObjectHashTable
{
public:
	ObjectHashTable(int32 size);
	~ObjectHashTable();

	bool insert(string const &name, void *object);
	void* find(string const &name);
	void* remove(string const &name);

private:
	uint32 hash(string const &name);
	vector<objhashBucket*> _table;
};


} // End of namespace

