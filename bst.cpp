#include "BTNode.h"
#include "bst.h"
#include <iostream>

using namespace std;

//constructor
bst::bst() {
  root = NULL;
}
//destructor
bst::~bst() {
  delete root;
}

void bst::insert(BTNode* &pass, int &data) {
  if (pass == NULL) { //whenever the passed node is NULL, create it
    pass = new BTNode(data);
    pass->setLeft(NULL);
    pass->setRight(NULL);
    if (!root) {
      root = pass;
    }
  }
  else if (pass->getData() > data) {
    insert(pass->getLeft(), data);
  }
  else {
    insert(pass->getRight(), data);
  }
}

bool bst::remove(BTNode* &root, int key) {
  if (!root) {
    return false; //doesn't exist or empty tree
  }
  BTNode* parent;
  parent = search(key, false); //grab parent
  int direction = 0;
  if (parent) {
    BTNode* toRemove;
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
	parent->setLeft(NULL);
      }
      else {
	parent->setRight(NULL);
      }
    }

    //if one child, inherit
    else if (toRemove->getLeft() != NULL && toRemove->getRight() == NULL) {
      if (direction == 1) { //child will go to left
	parent->setLeft(toRemove->getLeft());
	delete toRemove;
      }
      else {
	parent->setRight(toRemove->getLeft());
	delete toRemove;
      }
    }
    else if (toRemove->getLeft() == NULL && toRemove->getRight() != NULL) {
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
      BTNode* inorderLeaf = toRemove->getRight(); //go to right first
      BTNode* parent = toRemove; //start parent here
      while (inorderLeaf->getLeft() != NULL) {
	parent = inorderLeaf;
	inorderLeaf = inorderLeaf->getLeft(); //walk to inorder leaf
      }
      toRemove->setData(inorderLeaf->getData()); //replace toRemove's data with that of leaf

      if (parent == toRemove) {
	parent->setRight(inorderLeaf->getRight());
      }
      else {
	parent->setLeft(inorderLeaf->getRight());
      }
      delete inorderLeaf;
    }
    else {
    root = NULL;
    }
    delete toRemove;
    return true;
  }
  return false;
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
  else if (self == false) {
    if (root->getLeft() && root->getLeft()->getData() == key) return root;
    if (root->getRight() && root->getRight()->getData() == key) return root;
  }

  if (key < root->getData()) {
    return trueSearch(root->getLeft(), key, self); //search left
  }
  else {
    return trueSearch(root->getRight(), key, self); //search right
  }
}

BTNode*& bst::getRoot() {
  return root;
}
