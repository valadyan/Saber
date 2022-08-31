#include "List.h"
#include <iostream>

void List::PushFront(const std::string& str){
  ListNode* node = new ListNode();
  node->data.assign(std::move(str));

  if (_count){
    node->next = _head;
    _head->prev = node;
    _head = node;
    ++_count;

    return;
    }
  _head = node;
  _tail = node;
  ++_count;
  }

void List::Print(){
  ListNode* next = _head;
  while(next){
      std::cout << next->data << std::endl;
      next = next->next;
    }
  }
