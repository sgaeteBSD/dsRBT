#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>

using namespace std;

enum Color { RED, BLACK };

class Node {
 public:
  Node(int newData);
  ~Node();

  Node* &getLeft();
  Node* &getRight();
  int getData();

  Node* &getParent();
  Color getColor();

  void setLeft(Node* leftNode);
  void setRight(Node* rightNode);
  void setData(int newData);
  void setParent(Node* parentNode);
  void setColor(Color newColor);
  
 private:
  int data;
  Node* left;
  Node* right;

  Node* parent;
  Color color;
};

#endif
