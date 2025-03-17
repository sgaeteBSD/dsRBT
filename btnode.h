#ifndef BTNODE_H
#define BTNODE_H

#include <iostream>
#include <cstring>

using namespace std;

class BTNode {
 public:
  BTNode(int newData);
  ~BTNode();

  BTNode* getLeft();
  BTNode* getRight();
  int getData();

  void setLeft(BTNode* leftNode);
  void setRight(BTNode* rightNode);
  void setData(int newData);
  
 private:
  int data;
  BTNode* left;
  BTNode* right;
};

#endif
