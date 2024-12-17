// -------------------------------------------------------------
// Algorithms and Data Structures 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// An example on how to use the provided max heap class
// Last update: 14/12/2024
// -------------------------------------------------------------

#include <iostream>
#include "maxHeap.h"

int main() {

  // Create an empty max heap of integers with capacity for 100 integers
  // -1 is returned when there are no elements to return
  MaxHeap<int> h(100, -1); 

  // Insert 10 elements in the heap and print the maximum:
  auto v = {61,83,17,42,71,37,23,9,53,91};
  for (auto x : v) h.insert(x);
  std::cout << "h.max() = " << h.max() << std::endl;

  // Remove all elements one by one until the heap is empty
  while (!h.isEmpty()) std::cout << h.removeMax() << " ";
  std::cout << std::endl;

  // If the heap is empty, the "none" element is returned (-1)
  std::cout << "h.max() = " << h.max() << std::endl;
  
  return 0;
}
