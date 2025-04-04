#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>

using namespace std;

class Node {
 public:
  Node(int newData);
  ~Node();

  Node* &getLeft();
  Node* &getRight();
  int getData();

  void setLeft(Node* leftNode);
  void setRight(Node* rightNode);
  void setData(int newData);
  
 private:
  int data;
  Node* left;
  Node* right;
};

#endif
