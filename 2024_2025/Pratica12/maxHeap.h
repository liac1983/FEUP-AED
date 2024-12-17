// -------------------------------------------------------------
// Algorithms and Data Structures 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// A simple lightweight (max) binary heap
// Last update: 14/12/2024
// -------------------------------------------------------------

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>

template <class T> class MaxHeap {
private:
  std::vector<T> data; // Items between 1 and size
  int size;            // Number of items
  T none;              // What to return when there are no items

  // Make an element go up until its position
  void upHeap(int i) {
    // While the element is greater than parent and not on root
    while (i>1 && data[i] > data[i/2]) {
      std::swap(data[i], data[i/2]);
      i = i/2;
    }
  }

  // Make an element go down until its position
  void downHeap(int i) {
    while (2*i <= size) { // While still on the limits of the heap
      int j = i*2;
      // Choose largest child (position i*2 or i*2+1)
      if (j<size && data[j+1] > data[j]) j++;
      // If node is already larger or equal than largest child, stop
      if (data[i] >= data[j]) break;
      // Otherwise, swap with largest child
      std::swap(data[i], data[j]);
      i = j;
    }
  }
  
public:
  // Capacity cap and value no used for indicating no element
  MaxHeap(int cap, T no) : data(cap+1), size(0), none(no) {}

  // Empty heap?
  bool isEmpty() {
    return (size==0);
  }
  
  // Return (without removing) maximum element
  T max() {
    if (isEmpty()) return none;
    return data[1];
  }

  // Insert an element in the heap (true on sucess)
  bool insert(T value) {
    if (size+1 >= (int)data.size()) return false;
    size++;
    data[size] = value;
    upHeap(size);
    return true;
  }

  // Remove and return maximum
  T removeMax() {
    if (isEmpty()) return none;
    T max = data[1];
    data[1] = data[size];
    size--;
    downHeap(1);
    return max;
  }
  
};

#endif
