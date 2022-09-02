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
  if (_count){
      node->prev = _tail->prev;
      node->next = _tail;
      node->rand = node->prev; //megaPseudoRand
      _tail->prev->next = node;
      _tail->prev = node;
      ++_count;

      return;
    }

  _head = node;
  _head->prev = nullptr;
  _head->rand = _head;
  _tail = std::make_shared<ListNode>();
  _tail->prev = _head;
  _head->next = _tail;
  ++_count;
}

void List::Print(){
  NodePointer currNode = _head;

  while (currNode != _tail){
      std::cout << currNode->data << "-";
      if (currNode->rand) std::cout << currNode->rand->data;
      std::cout << std::endl;
      currNode = currNode->next;
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
          fprintf(file, "%p ", &*(node->rand));
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

  while (countNode-- != 0){
      NodePointer node(new ListNode);

      void* nodeOldPointRaw;
      fscanf(file, "%p", &nodeOldPointRaw);
      char nodeOldPoint[20];
      sprintf(nodeOldPoint, "%p", nodeOldPointRaw);
      oldAndNewNodePoiners[nodeOldPoint] = node;

      size_t nodeDataSize = 0;
      fscanf(file, _formatForSize_t, &nodeDataSize);
      char* nodeData = new char(nodeDataSize);
      fgets(nodeData, nodeDataSize, file);
      node->data.assign(nodeData, nodeDataSize);
      PushBack(node);

      if (fgetc(file) == 'Y'){
          fscanf(file, "%p ", &nodeOldPointRaw);
          sprintf(nodeOldPoint, "%p", nodeOldPointRaw);
          RestoreRandInNodes(nodeOldPoint, node);
        }
    }

  for(const auto& [oldRand, node]: nodesWaitingRandNode){
      if (auto needNode = oldAndNewNodePoiners[oldRand]){
           node->rand = needNode;
        }
    }
}

