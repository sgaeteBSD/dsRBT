#include "BTNode.h"
#include <iostream>

using namespace std;

class bst {
public:
  bst();
  ~bst();
  void insert(BTNode* &root, int &data);
  bool remove(BTNode* &root, int key);
  BTNode* search(int key);
  void print();
private:
  BTNode* root;
  BTNode* trueSearch(BTNode* node, int key);
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

bool bst::remove(BTNode* &root, int key) {
  if (!root) {
    return false; //doesn't exist or empty tree
  }
  BTNode* parent = new BTNode;
  parent = search(key, false); //grab parent
  int direction = 0;
  if (parent) {
    BTNode* toRemove = new BTNode;
    if (parent->getLeft()->getData() == key) {
      toRemove = parent->getLeft();
      direction = 1;
    }
    else {
      toRemove = parent->getRight();
      direction = 2;
    }

    if (toRemove->getLeft() == NULL && toRemove->getRight() == NULL) { //leaf removal
      if (direction == 1) {
	delete toRemove;
	parent->setLeft(NULL);
      }
      else {
	delete toRemove;
	parent->setRight(NULL);
      }
    }

    //if one child, inherit
    else if (toRemove->getLeft() != NULL && toRemove->getRight == NULL) {
      if (direction == 1) { //child will go to left
	parent->setLeft(toRemove->getLeft());
	delete toRemove;
      }
      else {
	parent->setRight(toRemove->getLeft());
	delete toRemove;
      }
    }
    else if (toRemove->getLeft() == NULL && toRemove->getRight != NULL) {
      if (direction == 1) { //child will go to left
	parent->setLeft(toRemove->getRight());
	delete toRemove;
      }
      else {
	parent->setRight(toRemove->getRight());
	delete toRemove;
      }
    }

    else if (toRemove->getLeft() != NULL && toRemove->getRight() != NULL) {
      BTNode* inorderLeaf = new BTNode;
      inorderLeaf = toRemove->getRight(); //go to right first
      while (inorderLeaf->getLeft() != NULL) {
	inorderLeaf = inorderLeaf->getLeft(); //walk to inorder leaf
      }
      parent = search(inorderLeaf->getData(), false); //get parent of leaf
      toRemove->setData(inorderLeaf->getData()); //replace toRemove's data with that of leaf

      parent->setLeft(NULL); //clear that bottom leaf
      delete inorderLeaf;
    }
  }
}

BTNode* bst::search(int key, bool self) { //if true get self, if false get parent
  return trueSearch(root, key, self);
}

BTNode* bst::trueSearch(BTNode* root, int key, bool self) {
  if (!root) {
    return NULL; //doesn't exist or empty tree
  }
  if (root->getData() == key && self == true) {
    return root; //return self
  }
  else if (root->getLeft()->getData() == key || root->getRight()->getData() == key && self == false) {
    return root; //return parent
  }

  if (key < root->getData()) {
    return search(root->getLeft(), key); //search left
  }
  else {
    return search(root->getRight(), key); //search right
  }
}
