#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;
//Header class
class Node {
  //Public functions
 public:
  Node(char* a);
  ~Node();
  Node* getRchild();
  Node* getLchild();
  void setRchild(Node* a);
  void setLchild(Node* a);
  char* getValue();
  //Private variables
 private:
  Node* childL;
  Node* childR;
  char* value;
};
#endif
