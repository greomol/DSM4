#include "ExecutorHashTable.h"
#include "CRC32.h"

namespace DS {

void 
ExecutorHashTable::feed(string const &name, executorPtr ptr, void *context) 
{
  void *oldcontext;
  if (find(name, &oldcontext) != NULL) return; // Уже есть такое имя
  if (_items+1 > _table.size() / 2) 
  {
    resize(_items+1); // Поддерживаем fill-factor < 50%
  } 
  uint32 h = hash(name) % _table.size(); 
  hashItem *it = _table[h];
  if (it == NULL) 
  {
    _table[h] = new hashItem(name, ptr, context);
    _items++;
    return;
  }
  while (it->link != NULL) 
  {
    it = it->link;
  }
  it->link = new hashItem(name, ptr, context);
  _items++;
}

executorPtr ExecutorHashTable::find(string const &name, void **context) 
{
  uint32 h = hash(name) % _table.size();
  hashItem *it = _table[h];
  while (it != NULL) 
  {
    if (it->name == name) 
    {
		*context = it->context;
		return it->executor;
    }
    it = it->link;
  }
  return NULL;
}

uint32 
ExecutorHashTable::hash(const std::string &name)
{
    CRC32 crc;
    crc.update(name.c_str(), name.size());
    return crc.final();
}

uint32
ExecutorHashTable::calcNewTableSize(uint32 desiredElements)
{
    return desiredElements * 8 / 5;
}

void
ExecutorHashTable::dispose(vector<hashItem *>)
{
  // @@
}

void 
ExecutorHashTable::resize(uint32 items)
{
  // Создать новую таблицу с размером, равным простому 
  // числу и fill-factor не более 30%
  uint32 newTableSize = calcNewTableSize(items);
  vector<hashItem *> oldTable(_table);
  _table.resize(newTableSize);
  for (size_t i = 0; i < newTableSize; i++) 
  {
    _table[i] = NULL;
  }
  // Скопировать старую таблицу в новую 
  // с использованием нового хеширования
  for (size_t i = 0; i < oldTable.size(); i++) 
  {
    hashItem *it = oldTable[i];
    while (it != NULL) 
    {
      feed(it->name, it->executor, it->context);
      it = it->link;
    }
  }
  dispose(oldTable);
} 

ExecutorHashTable::ExecutorHashTable(int size)
{
    _items = 0;
    resize(size);
}

ExecutorHashTable::~ExecutorHashTable()
{

}

} // end of namespace

