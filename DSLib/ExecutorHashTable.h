#ifndef _EXECUTORHASHTABLE_H_
#define _EXECUTORHASHTABLE_H_ 1

#include <vector>


using namespace std;

#include "Serializer.h"

namespace DS {

typedef int32 (*executorPtr)(void *context, Deserializer const &des, 
       Serializer &ser);

struct hashItem
{
  string name; // имя для сопоставления
  executorPtr executor; // функция, которую надо найти
  hashItem *link; // запись, которую надо 
                  // просмотреть при коллизии
  
  void     *context;
  hashItem(string const &name, executorPtr executor, void *context,
    hashItem *link = NULL) 
  {
    this->name = name;
    this->executor = executor;
    this->link = link;
	this->context = context;
  }
};

class ExecutorHashTable
{
public:
  ExecutorHashTable(int32 initialSize);
  ~ExecutorHashTable();

  // Добавить ассоциацию в таблицу
  void feed(string const &name, executorPtr, void *context);
  // Найти ассоциацию в таблице 
  executorPtr find(string const &name, void **context); 

private:
  // Должен выдавать равномерное распределение
  uint32 hash(string const &name); 
  vector<hashItem *> _table;
  uint32 _items;                // Количество заполненных входов
  void resize(uint32 items);
  // Освободить занятую указателями память
  void dispose(vector<hashItem *>); 
private:
    uint32 calcNewTableSize(uint32 desiredElements);
};

} // End of namespace
#endif
