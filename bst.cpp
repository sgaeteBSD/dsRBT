#include "BTNode.h"
#include <iostream>

using namespace std;

class bst {
public:
  bst();
  ~bst();
  int insert(const int &data);
  int remove(const int &key);
  int search(const int &key);
  void print();
private:
  BTNode* root;
};
