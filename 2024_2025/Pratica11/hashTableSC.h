// -------------------------------------------------------------
// Algoritmos e Estruturas de Dados 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// A simple lightweight implemetation of hash tables
// (using separate chaining, a.k.a. open hashing)
// Last update: 08/12/2024
// -------------------------------------------------------------

#ifndef _HASHTABLESC_H_
#define _HASHTABLESC_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <functional>

template <class KeyType> class HashTableSC {
  int size;                                      // Size of the hash table
  int numberKeys;                                // Number of inserted keys
  std::vector<std::list<KeyType>> table;         // The hash table itself
  std::function<unsigned(const KeyType &)> hash; // Hash function: key -> unsigned

public:
  // Constructor: receives the table size n and the hash function h
  HashTableSC(int n, std::function<unsigned(const KeyType&)> h) :
    size(n), numberKeys(0), table(n), hash(h) {}
  
  // Show contents of hash table (to check if implementation is correct)
  void showContents() {
    std::cout << "Size: " << size << " | Number of keys: " << numberKeys << " | Load Factor: "
              << std::fixed << std::setprecision(3) << (double)numberKeys / size << std::endl;
    for (int i=0; i<size; i++) {
      std::cout << i << ":";
      if (table[i].size() == 0) std::cout << " EMPTY";
      else for (auto it : table[i]) std::cout << " " << it;
      std::cout << std::endl;
    }
  }
  
  // ---------------------------------------------------------
  // TO DO: functions to implement in this exercise
  // ---------------------------------------------------------

  // Does it contain key k?
  bool contains(const KeyType & k) {
    // TO DO
    int index = hash(k) % size; // Compute the bucket index
    for (const auto &key : table[index]) {
      if (key == k) return true; // Key found
    }
    return false; // Key not found
    
  }
  
  // Insert key k (true if successful)
  bool insert(const KeyType & k) {
    // TO DO
    int index = hash(k) % size; // Compute the bucket index
    if (contains(k)) return false; // Key already exists
    table[index].push_back(k);     // Add key to the bucket
    numberKeys++;                  // Increment the number of keys
    return true;
  }

  // Remove key k (true if successful)
  bool remove(const KeyType & k) {
    // TO DO
    int index = hash(k) % size; // Compute the bucket index
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
      if (*it == k) {
        table[index].erase(it); // Remove key from the bucket
        numberKeys--;           // Decrement the number of keys
        return true;
      }
    }
    return false; // Key not found
  }
};

#endif
