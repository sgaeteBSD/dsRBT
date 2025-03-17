#ifndef BTNODE_H
#define BTNODE_H

#include <iostream>
#include <cstring>

using namespace std;

class BTNode {
 public:
  BTNode(char newData);
  ~BTNode();

  BTNode* getLeft();
  BTNode* getRight();
  char getData();

  void setLeft(BTNode* leftNode);
  void setRight(BTNode* rightNode);
  void setData(char newData);
  
 private:
  char data;
  BTNode* left;
  BTNode* right;
};

#endif
