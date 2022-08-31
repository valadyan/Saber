#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string>

struct ListNode {
  ListNode* prev;
  ListNode* next;
  ListNode* rand;
  std::string data;
};

class List {
  public:
    List(){}
    void Serialize(FILE* file);
    void Deserialize (FILE* file);
    void PushFront(const std::string& str);
    void Print();
  private:
    ListNode* _head = nullptr;
    ListNode*_tail = nullptr;
    int _count = 0;
};

#endif // LIST_H
