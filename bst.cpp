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

void bst::insert(Node* &pass, int &data, Node* parent) {
  if (pass == NULL) { //whenever the passed node is NULL, create it
    pass = new Node(data);
    pass->setLeft(NULL);
    pass->setRight(NULL);
    pass->setColor(RED);
    pass->setParent(parent);
    if (!root) {
      pass->setColor(BLACK);
      root = pass;
    }
    else {
      rbTree(root, pass);
    }
  }
  else if (pass->getData() > data) {
    insert(pass->getLeft(), data, pass);
  }
  else {
    insert(pass->getRight(), data, pass);
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

//RED BLACK TREE CODE BELOW

void bst::rbTree(Node* &root, Node* newNode) {
  Node* parent = NULL;
  Node* grandpa = NULL;

  if (newNode == root) { //case 1: insert at root
    newNode->setColor(BLACK);
    return;
  }
  
  while (newNode != root && newNode->getColor() == RED && newNode->getParent()->getColor() == RED) { //no two reds
    parent = newNode->getParent();
    grandpa = parent->getParent();

    //LEFT SIDE CASES
    if (parent == grandpa->getLeft()) {
      Node* uncle = grandpa->getRight();

      if (uncle != NULL && uncle->getColor() == RED) {
	//case: parent and uncle are red
	grandpa->setColor(RED);
	parent->setColor(BLACK);
	uncle->setColor(BLACK);
        newNode = grandpa; //run again on grandpa
      }
      else if (newNode == parent->getRight()) {
	newNode = parent;
	leftRotate(newNode);
      }
      else {
	parent->setColor(BLACK);
	grandpa->setColor(RED);
	rightRotate(grandpa); //right rotate grandparent
      }
    }

    //RIGHT SIDE CASES
    if (parent == grandpa->getRight()) { //mirror
      Node* uncle = grandpa->getLeft();

      if (uncle != NULL && uncle->getColor() == RED) {
        //case: parent and uncle are red
        grandpa->setColor(RED);
        parent->setColor(BLACK);
        uncle->setColor(BLACK);
        newNode = grandpa; //run again on grandpa
      }
      else if (newNode == parent->getLeft()) {
        newNode = parent;
        rightRotate(newNode);
      }
      else {
        parent->setColor(BLACK);
        grandpa->setColor(RED);
        leftRotate(grandpa); //left rotate grandparent
      }
    }
    
    root->setColor(BLACK);
  }
}

void bst::leftRotate(Node* x) {
  Node* y = x->getRight(); //y is x's right child

  //swap y's left into x's right
  x->setRight(y->getLeft());
  if (y->getLeft() != NULL) {
    y->getLeft()->setParent(x); //update parent
  }

  //now update y's parent
  y->setParent(x->getParent());

  if (x->getParent() == NULL) { //if x is root
    root = y; //now y is root!
  }
  else if (x == x->getParent()->getLeft()) { //if x was left child
    x->getParent()->setLeft(y);
  }
  else { //if x was right child
    x->getParent()->setRight(y);
  }

  //put x on y's left
  y->setLeft(x);
  x->setParent(y);
}

void bst::rightRotate(Node* y) {
  Node* x = y->getLeft(); //x is y's left child

  //swap x's right into y's left
  y->setLeft(x->getRight());
  if (x->getRight() != NULL) {
    x->getRight()->setParent(y); //update parent
  }

  //now update x's parent
  x->setParent(y->getParent());

  if (y->getParent() == NULL) { //if y is root
    root = x; //now x is root!
  }
  else if (y == y->getParent()->getRight()) { //if y was right child
    y->getParent()->setRight(x);
  }
  else { //if y was left child
    y->getParent()->setLeft(x);
  }

  //put y on x's right
  x->setRight(y);
  y->setParent(x);
}

