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

  // Read rotation asked and print before and after tree
  int x;
  std::cin >> x;
  t.printPreOrder();
  t.rightRotate(x);
  std::cout << "rightRotate(" << x << ")" << std::endl;
  t.printPreOrder();
  
  return 0;
}
