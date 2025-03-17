#include <iostream>
#include <cstring>
#include "BTnode.h"

using namespace std;

BTNode::BTNode(int newData) {
  // constructor
  data = newData;
  left = NULL; // setting pointer to null
  right = NULL;
}
BTNode::~BTNode(){
  // destructor
  left = NULL;
  right = NULL;
}
BTNode* BTNode::getLeft() {
  return left;
}
BTNode* BTNode::getRight() {
  return right;
}
int BTNode::getData() {
  return data;
}
void BTNode::setLeft(BTNode* leftNode) {
  left = leftNode;
}
void BTNode::setRight(BTNode* rightNode) {
  right = rightNode;
}
void BTNode::setData(int newData) {
  data = newData;
}
