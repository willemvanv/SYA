#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;
//Constructor
Node::Node(char* a) {
  childR = NULL;
  childL = NULL;
  value = new char[20];
  strcpy(value, a);
}
//Unused deconstructor
Node::~Node() {

}
//Get right child of node
Node* Node::getRchild() {
  return childR;
}
//Get left child of node
Node* Node::getLchild() {
  return childL;
}
//Set right child of node
void Node::setRchild(Node* a) {
  childR = a;
}
//Set left child of node
void Node::setLchild(Node* a) {
  childL = a;
}
//Get value of node
char* Node::getValue() {
  return value;
}
