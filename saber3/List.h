#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string>
#include <memory>

struct ListNode;
using NodePointer = std::shared_ptr<ListNode>;

struct ListNode {
  NodePointer prev;
  NodePointer next;
  NodePointer rand;
  std::string data;
};


class List {
  public:
    List();
    void Serialize(FILE* file);
    void Deserialize (FILE* file);
    void PushBack(const std::string& str);
    void Print();
  private:
    void PushBack(NodePointer node);
    NodePointer _head = nullptr;
    NodePointer _tail = nullptr;
    size_t _count = 0;
    char _formatForSize_t[sizeof("%.du")];
};

#endif // LIST_H

