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
  enum Direction { LEFT, RIGHT };
    Node* child;
  
  if (!root) {
    return false; //doesn't exist or empty tree
  }
  Node* parent;
  parent = search(key, false); //grab parent (old method from before RBT)
  Direction direction;
  Node* toRemove;
  if (root->getData() == key) { //ROOT CASE
    toRemove = root;
    parent = NULL; //root got no parents
  }
  else if (parent) {
    if (parent->getLeft() && parent->getLeft()->getData() == key) { //left child
      toRemove = parent->getLeft();
      direction = LEFT;
    }
    else if (parent->getRight() && parent->getRight()->getData() == key) { //right child
      toRemove = parent->getRight();
      direction = RIGHT;
    }
  }
  else {
    return false;
  }
  //case 1: no children, leaf
  if (toRemove->getLeft() == NULL && toRemove->getRight() == NULL) {
    if (toRemove->getColor() == RED || toRemove == root) { //red leaf and root removal
      if (parent) { //red leaf
	if (direction == LEFT) {
	  parent->setLeft(NULL);
	}
	else {
	  parent->setRight(NULL);
	}
      }
      else { //root
	root = NULL;
      }
      delete toRemove;
    }
    else if (toRemove->getColor() == BLACK && toRemove != root) { //black leaf
      remFix(toRemove);//requires rebalance!
      if (direction == LEFT) {
	parent->setLeft(NULL);
      }
      else {
	parent->setRight(NULL);
      }
      delete toRemove;
    }
  }

  //case 2: if one child, inherit
  else if ((toRemove->getLeft() != NULL && toRemove->getRight() == NULL) || (toRemove->getLeft() == NULL && toRemove->getRight() != NULL)) {
  if (toRemove->getLeft() != NULL && toRemove->getRight() == NULL) { child = toRemove->getLeft(); }
  if (toRemove->getLeft() == NULL && toRemove->getRight() != NULL) { child = toRemove->getRight(); }
  if (toRemove->getColor() == BLACK) {
    if (child && child->getColor() == RED) {
	child->setColor(BLACK);
      }
      else {
	remFix(toRemove);
      }
    }
    if (parent) {
      if (direction == LEFT) { //child will go to left
	parent->setLeft(child);
      }
      else {
	parent->setRight(child);
      }
    } else {
      root = child;
    }
    if (child) { child->setParent(parent); }
    delete toRemove;
  }

  //case 3: two children!
  else if (toRemove->getLeft() != NULL && toRemove->getRight() != NULL) {
    Node* leaf = toRemove->getRight();
    Node* p = toRemove;
    Node* o = toRemove;

    while (leaf->getLeft() != NULL) {
      p = leaf;
      leaf = leaf->getLeft();
    }

    toRemove->setData(leaf->getData());
    Node* c = leaf->getRight();
    if (p == toRemove) {
      p->setRight(c);
    } else {
      p->setLeft(c);
    }
    if (c) { c->setParent(p); }
    if ((!c) && toRemove->getLeft()) {
      c = toRemove->getLeft();
    }

    if (leaf->getColor() == RED) {
      delete leaf;
      return true;
    }
    
    if (toRemove->getColor() == BLACK) {
      if ((c) && (c->getColor() == RED)) {
        if (leaf->getColor() == BLACK && (c == leaf->getLeft() || c == leaf->getRight())) {
	  c->setColor(BLACK);
	}
      }
      else {
	if ((c) && (c != toRemove->getLeft())) {
	  remFix(c);
	}
	else if ((c) && (c->getColor() == BLACK) && ((c->getParent()->getRight() == NULL) || c->getParent()->getLeft() == NULL)) {
	  if ((c->getRight() && c->getRight()->getColor() == RED) || (c->getLeft() && c->getLeft()->getColor() == RED)) {
	    if (c->getParent()->getLeft() == NULL) {
	      leftRotate(p);
	      c->getRight()->setColor(BLACK);
	    } else if (c->getParent()->getRight() == NULL) {
	      rightRotate(p);
	      c->getLeft()->setColor(BLACK);
	    }
	  } else {
	    c->setColor(RED);
	    remFix(p);
	  }
	}
	else if (toRemove != root) { //here
	  remFix(p);
	}
      }
    }
    if (toRemove != root && p->getColor() == RED && (c) && (c->getColor() == BLACK)) {
      if (c) { c->setColor(RED); }
      p->setColor(BLACK);
    }
    delete leaf;
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
      Node* unc = grandpa->getLeft();

      if (unc != NULL && unc->getColor() == RED) {
        //case: parent and uncle are red
        grandpa->setColor(RED);
        parent->setColor(BLACK);
        unc->setColor(BLACK);
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

void bst::remFix(Node* n) {
  enum Direction { LEFT, RIGHT };
  while (n != root) {
    Node* p;
    if (n->getParent()) { p = n->getParent(); }
    Node* s = NULL;
    Node* c = NULL;
    Node* d = NULL;
    Direction nDir;

    //case 1
    if (!p) {
      break;
    }

    if (((s) && s->getColor() == BLACK && p->getColor() == RED) &&
	  ((!c) && (!d) || ((c) && (c->getColor() == BLACK) && (!d)) ||
	   ((d) && (d->getColor() == BLACK) && (!c)) ||
	   ((c) && (d) && (c->getColor() == BLACK) && (d->getColor() == BLACK)))) {
	//case 4
	s->setColor(RED);
	p->setColor(BLACK);
	break;
      }
    
    if (p->getRight() != NULL && p->getRight() == n) { // s = sibling, c = close nephew, d = distant nephew
      if (p->getLeft()) { s = p->getLeft(); }
      if (s->getRight()) { c = s->getRight(); }
      if (s->getLeft()) { d = s->getLeft(); }
      nDir = RIGHT;
      cout<<"test1" <<endl;
    } else if (p->getLeft() == n) {
      if (p->getRight()) { s = p->getRight(); }
      if (s->getLeft()) { c = s->getLeft(); }
      if (s->getRight()) { d = s->getRight(); }
      nDir = LEFT;
    }

    if (s != NULL && s->getColor() == RED) {
      //case 3
      if (nDir == LEFT) {
	leftRotate(p);
	if (s->getRight()) { d = s->getRight(); }
      } else {
	rightRotate(p);
	if (s->getLeft()) { d = s->getLeft(); }
      }
      p->setColor(RED);
      if (s) { s->setColor(BLACK); }
      continue; //case 3 connects to other cases
    }
      if (d != NULL && d->getColor() == RED) {
	//case 6
	if (nDir == RIGHT) {
	  rightRotate(p);
	} else {
	  leftRotate(p);
	}
	s->setColor(p->getColor());
	p->setColor(BLACK);
	d->setColor(BLACK);
	break;
      }
      
      /*if (nDir == RIGHT) {
	c = s->getRight();
      } else {
	c = s->getLeft();
	}*/
      if (c != NULL && c->getColor() == RED) {
	//case 5
	if (nDir == RIGHT) {
	  leftRotate(s);
	} else {
	  rightRotate(s);
	}
	s->setColor(RED);
	c->setColor(BLACK);
	continue;
      }
      
      cout << "here" << endl;
    //case 2
      if ((s) && ((((c) && c->getColor() == BLACK) && (!d)) || (((d) && d->getColor() == BLACK && (!c))) || ((!c) && (!d))
		  || (((c) && c->getColor() == BLACK) && ((d) && (d->getColor() == BLACK))))) {
      s->setColor(RED);
    }
    n = p;
  }
  //if (n) { n->setColor(BLACK); }
}
