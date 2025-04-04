#include "Node.h"
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

void bst::insert(Node* &pass, int &data) {
  if (pass == NULL) { //whenever the passed node is NULL, create it
    pass = new Node(data);
    pass->setLeft(NULL);
    pass->setRight(NULL);
    pass->setColor(RED);
    if (!root) {
      root = pass;
      root->setColor(BLACK);
    }
  }
  else if (pass->getData() > data) {
    insert(pass->getLeft(), data);
  }
  else {
    insert(pass->getRight(), data);
  }
}

bool bst::remove(Node* &root, int key) {
  if (!root) {
    return false; //doesn't exist or empty tree
  }
  Node* parent;
  parent = search(key, false); //grab parent
  int direction = 0;
  Node* toRemove;
  if (root->getData() == key) {
    toRemove = root;
    parent = NULL; //root got no parents
  }
  else if (parent) {
    if (parent->getLeft() && parent->getLeft()->getData() == key) {
      toRemove = parent->getLeft();
      direction = 1;
    }
    else if (parent->getRight() && parent->getRight()->getData() == key) {
      toRemove = parent->getRight();
      direction = 2;
    }
  }
  else {
    return false;
  }
  //case 1: no children, leaf
    if (toRemove->getLeft() == NULL && toRemove->getRight() == NULL) { //leaf removal
      if (parent) {
	if (direction == 1) {
           parent->setLeft(NULL);
        }
	else {
           parent->setRight(NULL);
        }
      }
      else { //if root
	root = NULL;
      }
      delete toRemove;
    }

    //case 2: if one child, inherit
    else if (toRemove->getLeft() != NULL && toRemove->getRight() == NULL) {
      if (parent) {
	if (direction == 1) { //child will go to left
	parent->setLeft(toRemove->getLeft());
	}
	else {
	  parent->setRight(toRemove->getLeft());
	}
      } else {
	root = toRemove->getLeft();
      }
      delete toRemove;
    }
    else if (toRemove->getLeft() == NULL && toRemove->getRight() != NULL) {
      if (parent) {
	if (direction == 1) { //child will go to left
	parent->setLeft(toRemove->getRight());
	}
	else {
	  parent->setRight(toRemove->getRight());
	}
      } else {
	root = toRemove->getRight();
      }
      delete toRemove;
    }

    //case 3: two children!
    else if (toRemove->getLeft() != NULL && toRemove->getRight() != NULL) {
      Node* inorderLeaf = toRemove->getRight(); //go to right first
      Node* parent = toRemove; //start parent here
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
    return true;
  }

Node* bst::search(int key, bool self) { //if true get self, if false get parent
  return trueSearch(root, key, self);
}

Node* bst::trueSearch(Node* root, int key, bool self) {
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

Node*& bst::getRoot() {
  return root;
}
