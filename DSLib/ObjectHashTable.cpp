#include "ObjectHashTable.h"
#include "CRC32.h"


namespace DS {

bool ObjectHashTable::insert(string const &name, void *object)
{
	if (object == NULL)
	{
		return false;
	}
	uint32 h = hash(name) % _table.size(); 
	objhashBucket *b = _table[h];
	AutoReleaser l(b->mutex);
	objhashItem *it = b->list;
	if (it == NULL)
	{
		_table[h]->list = new objhashItem(name, object);
		return true;
	}
	if (it->name == name)
	{
		return false;
	}
	while (it->link != NULL)
	{
		if (it->link->name == name)
		{
			return false;
		}
		it = it->link;
	}
	it->link = new objhashItem(name, object);
	return true;
}


void* ObjectHashTable::find(string const &name)
{
	uint32 h = hash(name) % _table.size();
	objhashBucket *b = _table[h];
	AutoReleaser l(b->mutex);
	objhashItem *it = b->list;
	while (it != NULL)
	{
		if (it->name == name) 
		{
			return it->object;
		}
		it = it->link;
	}
	return NULL;
}


void* ObjectHashTable::remove(string const &name)
{
	uint32 h = hash(name) % _table.size();
	objhashBucket *b = _table[h];
	AutoReleaser l(b->mutex);
	objhashItem *prev = b->list;
	if (prev == NULL)
	{
		return NULL;
	}
	if (prev->name == name)
	{
		void *result = prev->object;
		delete prev;
		b->list = NULL;
		return result;
	}
	objhashItem *it = prev->link;
	while (it != NULL)
	{
		if (it->name == name)
		{
			void *result = it->object;
			prev->link = it->link;
			delete it;
			return result;
		}
		prev = it;
		it = it->link;
	}
	return NULL;
}


uint32 ObjectHashTable::hash(const std::string &name)
{
    CRC32 crc;
    crc.update(name.c_str(), name.size());
    return crc.final();
}


ObjectHashTable::ObjectHashTable(int size)
{
	_table.resize(size);
	for (int i = 0; i < size; i++)
	{
		_table[i] = new objhashBucket;
	}
}

ObjectHashTable::~ObjectHashTable()
{
	for (uint32 i = 0; i < _table.size(); i++)
	{
		objhashItem *it = _table[i]->list, *next;
		while (it != NULL)
		{
			next = it->link;
			delete it;
			it = next;
		}
		delete _table[i];
	}
}

} // end of namespace
