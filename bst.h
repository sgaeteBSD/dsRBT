#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

class bst {
public:
  bst();
  ~bst();
  void insert(Node* &pass, int &data, Node* parent);
  bool remove(Node* &root, int key);
  Node* search(int key, bool self);
  Node* &getRoot();
  void print();

  void rbTree(Node* &root, Node* newNode);
  void leftRotate(Node* x);
  void rightRotate(Node* y);
private:
  Node* root;
  Node* trueSearch(Node* node, int key, bool self);
};

#endif
