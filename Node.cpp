#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

Node::Node(int newData) {
  // constructor
  data = newData;
  left = NULL; // setting pointer to null
  right = NULL;
  parent = NULL;
  color = RED;
}
Node::~Node(){
  // destructor
  left = NULL;
  right = NULL;
}
Node*& Node::getLeft() {
  return left;
}
Node*& Node::getRight() {
  return right;
}
int Node::getData() {
  return data;
}
void Node::setLeft(Node* leftNode) {
  left = leftNode;
}
void Node::setRight(Node* rightNode) {
  right = rightNode;
}
void Node::setData(int newData) {
  data = newData;
}


Node*& Node::getParent() {
  return parent;
}
void Node::setParent(Node* parentNode) {
  parent = parentNode;
}
Color Node::getColor() {
  return color;
}
void Node::setColor(Color newColor) {
  color = newColor;
}
