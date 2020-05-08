#include <iostream>
#include "Tree.h"
using namespace std;

int main() 
{
  typedef BNode<float> b_node;
  typedef Tree<b_node> b_tree;

  b_tree btree(4);
  
  btree.insert(10);
  btree.insert(2);
  btree.insert(4);
  btree.insert(41);
  btree.insert(15);
  btree.insert(26);
  btree.insert(19);
  btree.insert(11);
  
  cout << btree.find(10) << endl;
  cout << btree.find(2) << endl;
  cout << btree.find(4) << endl;
  cout << btree.find(41) << endl;
  cout << btree.find(15) << endl;
  cout << btree.find(26) << endl;
  cout << btree.find(19) << endl;
  cout << btree.find(11) << endl;
  cout << btree.find(22) << endl;
  cout << btree.find(10.2) << endl;
  cout << btree.find(0) << endl;

  cout << btree << endl;

  return 0;
}