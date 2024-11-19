#include <iostream>
#include <string>

#include "binarySearchTree.h"

int main() {
  BSTree<int> t;

  // Read tree by inserting numbers
  int n;
  std::cin >> n;
  for (int i=0; i<n; i++) {
    int x;
    std::cin >> x;
    t.insert(x);
  }

  // Call method to check if tree is an AVL Tree
  std::cout << "t.isAVL() = " << (t.isAVL()?"true":"false") << std::endl;
  
  return 0;
}
