#include "BTNode.h"
#include <iostream>

using namespace std;

class bst {
public:
  bst();
  ~bst();
  void insert(BTNode* &root, int &data);
  int remove(int &key);
  BTNode* search(int key);
  void print();
private:
  BTNode* root;
  BTNode* trueSearch(BTNode* node, int &key);
};

//constructor
//destructor

void bst::insert(BTNode* &root, int &data) {
  if (!root) { //whenever the passed node is NULL, create it
    BTNode* root = new BTNode;
    root->setData(data);
    root->setLeft(NULL);
    root->setRight(NULL);
  }
  else if (root->getData() > data) {
    insert(root->getLeft(), data);
  }
  else {
    insert(root->getRight(), data);
  }
}

BTNode* bst::search(int key) {
  return trueSearch(root, key);
}

BTNode* bst::trueSearch(BTNode* root, int &key) {
  if (!root) {
    return NULL; //doesn't exist or empty tree
  }
  if (root->getData() == key) {
    return root; //found
  }

  if (key < root->getData()) {
    return search(root->getLeft(), key); //search left
  }
  else {
    return search(root->getRight(), key); //search right
  }
}
