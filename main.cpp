#include <fstream>
#include "BTNode.h"
#include "bst.h"

using namespace std;

void addFile(bst tree);
void print();
void quitter(bool &input);

int main() {
  bst tree;
  bool input = true;
  while (input == true) { //command selector
    cout << "Your commands are ADD_MANUAL, ADD_FILE, PRINT, REMOVE, and QUIT." << endl;
    cout << endl;
    cout << "Input a command." << endl;
    char command[15] = ""; //make sure to fit chars + 1 terminating

    cin >> command; 
    cin.ignore();
    
    bool exist = false;
    if (tree.getRoot()) {
      exist = true;
    }
    
    if (strcmp(command, "ADD_MANUAL") == 0) {
      if (exist == true) {
	int add = 0;
	cout << "Number to add:" << endl;
	cin >> add;
	tree.insert(tree.getRoot(), add);
      }
      else {
	cout << "Your tree is empty!" << endl;
      }
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
	//print(tree);
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

void addFile(bst tree) {
  cout << "Please enter the full name of your file. (ex: 'bst-numbers.txt')" << endl;
  string fileName;
  int fileVal;
  cin >> fileName;
  cin.ignore();
  fstream BstNumbers(fileName);
  while (BstNumbers >> fileVal) { //read from file, spaces separating
    tree.insert(tree.getRoot(), fileVal);
  }
  BstNumbers.close();

  cout << "Numbers from " << fileName << " have been added." << endl;
  cout << endl;
}
  
void quitter(bool &input) { //quit
  cout << "Goodbye!" << endl;
  input = false;
}
