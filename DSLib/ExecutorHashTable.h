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
  string name; // ��� ��� �������������
  executorPtr executor; // �������, ������� ���� �����
  hashItem *link; // ������, ������� ���� 
                  // ����������� ��� ��������
  
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

  // �������� ���������� � �������
  void feed(string const &name, executorPtr, void *context);
  // ����� ���������� � ������� 
  executorPtr find(string const &name, void **context); 

private:
  // ������ �������� ����������� �������������
  uint32 hash(string const &name); 
  vector<hashItem *> _table;
  uint32 _items;                // ���������� ����������� ������
  void resize(uint32 items);
  // ���������� ������� ����������� ������
  void dispose(vector<hashItem *>); 
private:
    uint32 calcNewTableSize(uint32 desiredElements);
};

} // End of namespace
#endif
