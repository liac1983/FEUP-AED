// -------------------------------------------------------------
// Algoritmos e Estruturas de Dados 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// A simple lightweight implemetation of hash tables
// (using open addressing, a.k.a. closed hashing)
// Last update: 08/12/2024
// -------------------------------------------------------------

#ifndef _HASHTABLEOA_H_
#define _HASHTABLEOA_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>

template <class KeyType> class HashTableOA {
  enum EntryType {EMPTY, ACTIVE, DELETED}; // Type of table entry
  struct HashEntry {                       // One table entry
    EntryType state;
    KeyType key;
  };
  
  int size;                                      // Size of the hash table
  int numberActive;                              // Number of active table entries (with keys)
  int numberDeleted;                             // Number of deleted table entries
  std::vector<HashEntry> table;                  // The hash table itself
  std::function<unsigned(const KeyType &)> hash; // Hash function: key -> unsigned

public:
  // Constructor: receives the table size n and the hash function h
  HashTableOA(int n, std::function<unsigned(const KeyType&)> h) :
    size(n), numberActive(0), numberDeleted(0), table(n), hash(h) {
    for (int i=0; i<size; i++) table[i].state = EMPTY;
  }
  
  // Show contents of hash table (to check if implementation is correct)
  void showContents() {
    std::cout << "Size: " << size << " | Nr Active: " << numberActive
              << " | Nr Deleted: " << numberDeleted << " | Load Factor: "
              << std::fixed << std::setprecision(3)
              << (double)(numberActive + numberDeleted) / size << std::endl;
    std::cout << "Table:";
    for (int i=0; i<size; i++) {
      if (table[i].state == EMPTY) std::cout << " {}";
      else if (table[i].state == DELETED) std::cout << " DEL";
      else std::cout << " " << table[i].key;
    }
    std::cout << std::endl;
  }
  
  // ---------------------------------------------------------
  // TODO: functions to implement in this exercise
  // ---------------------------------------------------------

  
  // Does it contain key k?
  bool contains(const KeyType & k) {
    // TO DO
    int idx = hash(k) % size;
    int startIdx = idx;

    // Realiza a sondagem linear
    while (table[idx].state != EMPTY) {
        if (table[idx].state == ACTIVE && table[idx].key == k) return true;
        idx = (idx + 1) % size;
        if (idx == startIdx) break; // Evita loop infinito
    }
    return false;
  }
  
  // Insert key k (true if successful)
  bool insert(const KeyType & k) {
    // TO DO
    // Verifica se a chave já existe
    if (contains(k)) return false;

    // Verifica se há pelo menos um bucket EMPTY disponível
    if (numberActive + numberDeleted >= size) return false;

    int idx = hash(k) % size;
    while (table[idx].state == ACTIVE) {
        idx = (idx + 1) % size; // Linear probing
    }

    // Reutiliza um bucket DELETED, se necessário
    if (table[idx].state == DELETED) {
        numberDeleted--; // Reduz o número de buckets DELETED
    }

    table[idx].state = ACTIVE;
    table[idx].key = k;
    numberActive++; // Incrementa o número de entradas ativas
    return true;
  }

  // Remove key k (true if successful)
  bool remove(const KeyType & k) {
    // TO DO
    int idx = hash(k) % size;
    int startIdx = idx;

    // Realiza a sondagem linear para encontrar a chave
    while (table[idx].state != EMPTY) {
        if (table[idx].state == ACTIVE && table[idx].key == k) {
            table[idx].state = DELETED; // Marca como DELETED
            numberActive--; // Atualiza o número de entradas ativas
            numberDeleted++; // Atualiza o número de entradas deletadas
            return true;
        }
        idx = (idx + 1) % size;
        if (idx == startIdx) break; // Evita loop infinito
    }
    return false; // Chave não encontrada
  }
};

#endif