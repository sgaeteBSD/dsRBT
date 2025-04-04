/*
 * Santiago Gaete
 * 3/21/25
 * Data Structures - Red Black Tree Insertion
 */

#include <fstream>
#include "Node.h"
#include "bst.h"
#include <stdio.h>

using namespace std;

void addFile(bst &tree);
void print(Node* current, int depth);
void quitter(bool &input);

int main() {
  bst tree;
  bool input = true;
  while (input == true) { //command selector

    bool exist = false;
    if (tree.getRoot() != NULL) {
      exist = true;
    }
    
    cout << "Your commands are ADD_MANUAL, ADD_FILE, PRINT, SEARCH, REMOVE, and QUIT." << endl;
    cout << endl;
    cout << "Input a command." << endl;
    char command[15] = ""; //make sure to fit chars + 1 terminating

    cin >> command; 
    cin.ignore();
    
    
    if (strcmp(command, "ADD_MANUAL") == 0) {
	int add = 0;
	cout << "Number to add:" << endl;
	cin >> add;
	tree.insert(tree.getRoot(), add);
    }
    else if (strcmp(command, "ADD_FILE") == 0) {
      addFile(tree);
    }
    else if (strcmp(command, "SEARCH") == 0) {
      if (exist == true) {
	int key = 0;
	cout << "Number to search:" << endl;
	cin >> key;
	if (tree.search(key, true) != NULL) {
	  cout << "The number " << key << " exists in the tree." << endl;
	}
      }
      else {
	cout << "Your tree is empty!" << endl;
      }
    }
    else if (strcmp(command, "PRINT") == 0) {
      if (exist == true) {
	print(tree.getRoot(), 0);
      }
      else {
	cout << "Your tree is empty!" << endl;
      }
    }
    else if (strcmp(command, "REMOVE") == 0) {
      if (exist == true) {
	int key;
	cout << "Number to remove:" << endl;
	cin >> key;
	tree.remove(tree.getRoot(), key);
      }
      else { 
	cout << "Your tree is empty!" << endl;
      }
    }
    else if (strcmp(command, "QUIT") == 0) {
      quitter(input);
    }
    else {
      cout << "Invalid input! Try again." << endl;
    }
  }
}

void addFile(bst &tree) {
  cout << "Please enter the full name of your file. (ex: 'bst-numbers.txt')" << endl;
  string fileName;
  int fileVal;
  cin >> fileName;
  cin.ignore();
  fstream BstNumbers(fileName);
  while (BstNumbers >> fileVal) { //read from file, spaces separating
    tree.insert(tree.getRoot(), fileVal);
    cout << fileVal << endl;
  }
  BstNumbers.close();

  cout << "Numbers from " << fileName << " have been added." << endl;
  cout << endl;
}
  
void quitter(bool &input) { //quit
  cout << "Goodbye!" << endl;
  input = false;
}

void print(Node* current, int depth) {
  if (current->getRight() != NULL) {
    print(current->getRight(), depth + 1);
  }
  for (int a = 0; a < depth; a++) {
    cout << "\t";
  }
    if (current->getColor() == RED) {
        cout << "\033[31m" << current->getData() << "\033[0m" << endl;  // Red text
    }
    
    else if (current->getColor() == BLACK) {
        cout << "\033[34m" << current->getData() << "\033[0m" << endl;  // Blue text
    }
  if (current->getLeft() != NULL) {
    print(current->getLeft(), depth + 1);
  }
}
