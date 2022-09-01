#include "List.h"
#include <iostream>
#include <cstring>
#include <unordered_map>

List::List(){
  sprintf(_formatForSize_t, "%.%%du ", sizeof(size_t));
}


void List::PushBack(const std::string& str){
  NodePointer node(new ListNode);
  node->data.assign(std::move(str));
  PushBack(node);
}


void List::PushBack(NodePointer node){
  if (_count == 1){
      _tail = node;
      _head->next = _tail;
      _tail->prev = _head;
      _tail->next = nullptr;
      _tail->rand = _tail;
      ++_count;

      return;
    }

  if (_count){
      node->prev = _tail;
      node->next = nullptr;
      node->rand = _tail; //megaPseudoRand
      _tail->next = node;
      _tail = node;
      ++_count;

      return;
    }

  _head = node;
  _head->rand = _head;
  ++_count;
}

void List::Print(){
  NodePointer next = _head;

  while (next != _tail){
      std::cout << next->data << "-" << next->rand->data << std::endl;
      next = next->next;
    }
}


void List::Serialize(FILE* file){
  NodePointer node = _head;
  fprintf(file, _formatForSize_t, _count);

  while (node != _tail){
      const char* nodeData = node->data.c_str();
      size_t nodeDataSize = node->data.size() + 1;

      fprintf(file, "%p", &*node);
      fprintf(file, _formatForSize_t, nodeDataSize);
      fputs(nodeData, file);

      if (node->rand){
          fputs("Y", file);
          fprintf(file, "%p", &*(node->rand));
        }else{
          fputs("N", file);
        }

      node = node->next;
    }
}


void List::Deserialize (FILE* file){
  std::unordered_map<std::string, NodePointer> oldAndNewNodePoiners;
  std::unordered_map<std::string, NodePointer> nodesWaitingRandNode;
  const auto RestoreRandInNodes = [&oldAndNewNodePoiners, &nodesWaitingRandNode]
      (std::string oldRandPoint, NodePointer node)
  {
      if (auto needNode = oldAndNewNodePoiners[oldRandPoint]){
          node->rand = needNode;

          return;
        }

      nodesWaitingRandNode[oldRandPoint] = node;
   };

  size_t countNode = 0;
  fscanf(file, _formatForSize_t, &countNode);
  int sizeOfStringForPointerSize = sizeof(void**) *2; //2 char for hex byte

  while (countNode-- > 0 || !feof(file)){
      NodePointer node(new ListNode);

      char nodeOldPoint[sizeOfStringForPointerSize];
      fgets(nodeOldPoint, sizeOfStringForPointerSize, file);
      oldAndNewNodePoiners[nodeOldPoint] = node;
//      char* nodeOldPoint;
//      fscanf(file, "%p", &nodeOldPoint);

      puts(nodeOldPoint);

      size_t nodeDataSize = 0;
      fscanf(file, _formatForSize_t, &nodeDataSize);

      char* nodeData = new char(nodeDataSize);
      fgets(nodeData, nodeDataSize, file);
      node->data.assign(nodeData, nodeDataSize);

      if (fgetc(file) == 'Y'){
          char randOldPoint[sizeOfStringForPointerSize];
          fgets(randOldPoint, sizeOfStringForPointerSize, file);
          RestoreRandInNodes(randOldPoint, node);
        }

      PushBack(node);
    }

  for(const auto& [oldRand, node]: nodesWaitingRandNode){
      if (auto needNode = oldAndNewNodePoiners[oldRand]){
           node->rand = needNode;
        }
    }
}

