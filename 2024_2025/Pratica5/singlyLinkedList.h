// -------------------------------------------------------------
// Algoritmos e Estruturas de Dados 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// Singly Linked List
// Last update: 20/10/2024
// -------------------------------------------------------------

#ifndef SLLIST_H
#define SLLIST_H

#include <iostream>
#include <sstream>
#include <cassert>
#include <string>


// -------------------------------------------------------------
// Simple Node<T> class with a link to the next node
// -------------------------------------------------------------

template <class T>
class Node {
  
private:
  T value;   // value in the node
  Node<T> *next;  // pointer to next node

public:
  Node(const T & v, Node<T> *n): value(v), next(n) {}

  T & getValue() {
    return value;
  }
  
  Node<T> *getNext() {
    return next;
  }
  
  void setValue(T & v) {
    value=v;
  }
  
  void setNext(Node<T> *n) {
    next = n;
  }
};


// -------------------------------------------------------------
// Implementation of a SinglyLinkedList<T>
// -------------------------------------------------------------

template <class T>
class SinglyLinkedList {

private:
  Node<T> *first;    // first element
  int length;         // length
  
public:

  // Construtor (creates empty list)
  SinglyLinkedList(): first(nullptr), length(0) {}
  
  // Destrutor
  ~SinglyLinkedList() {
    while(!isEmpty()) {
      assert(first != nullptr && "length bigger than what it should be");
      removeFirst();
    }
    assert(first == nullptr && "length smaller than what it should be");
  }
  
  // Returns the length of the list
  int size() {
    return length;
  }

  // Returns true iff the list is empty
  bool isEmpty() {
    return (length == 0);
  }
   
  // Adds v to the head of the list
  void addFirst(const T & v) {
    Node<T> *newNode = new Node<T>(v, first); 
    first = newNode;
    length++;
  }

  // Adds v to the end of the list
  void addLast(const T & v) {
    Node<T> *newNode = new Node<T>(v, nullptr); 
    if (isEmpty()) {
      first = newNode;
    } else {
      Node<T> *cur = first;
      while (cur->getNext() != nullptr)
        cur = cur->getNext();
      cur->setNext(newNode);
    }
    length++;
  }

  // Returns the reference to the first value
  T & getFirst() {
    assert(!isEmpty() && "trying to get first from empty list");
    return first->getValue();
  }

  // Returns the last value
  T & getLast() {
    assert(!isEmpty() && "trying to get last from empty list");
    Node<T> *cur = first;
    while (cur->getNext() != nullptr)
      cur = cur->getNext();
    return cur->getValue();      
  }

  // Removes the first element (does nothing if the list is empty)
  void removeFirst() {
    if (isEmpty()) return;
    Node<T> *victim = first;
    first = first->getNext();
    delete victim;
    length--;
  }

  // Removes the last element (does nothing if the list is empty)
  void removeLast() {
    if (isEmpty()) return;
    if (length == 1) {
      delete first;
      first = nullptr;
    } else {
      // Using length and a for loop to show an alternative to while loop
      Node<T> *cur = first;
      for (int i=0; i<length-2; i++)  
        cur = cur->getNext();
      Node<T> *victim = cur->getNext();
      cur->setNext(victim->getNext());
      delete victim;
    }
    length--;
  }

  // Convert a list to a string
  std::string toString() {
    if (isEmpty()) return "{}";
    std::stringstream sstr;
    sstr <<  "{" <<  first->getValue();
    Node<T> *cur = first->getNext();
    while (cur != nullptr) {
      sstr << "," << cur->getValue();
      cur = cur->getNext();
    }
    sstr <<  "}";
    std::string str;
    std::getline(sstr,str);
    return str;
  }

  
  // ------------------------------------------------------------
  // TODO: put the functions you need to implement below this
  // ------------------------------------------------------------
  T & get(int pos) {
    assert(pos >= 0 && pos < length && "Position out of bounds");

    Node<T> *cur = first;
    for (int i = 0; i < pos; i++) {
      cur = cur->getNext();
    }
    return cur->getValue();
  }

  // ------------------------------------------------------------
  // Method to count occurrences of value v in the list
  // ------------------------------------------------------------
  int count(const T & v) {
    int count = 0;
    Node<T> *cur = first;

    // Traverse the list
    while (cur != nullptr) {
      if (cur->getValue() == v) {
        count++;  // Increment count if value matches
      }
      cur = cur->getNext();  // Move to the next node
    }

    return count;
  }

    // ------------------------------------------------------------
  // Method to remove element at position pos
  // ------------------------------------------------------------
  void remove(int pos) {
    if (pos < 0 || pos >= length) {
      return; // Position is invalid
    }
    
    if (pos == 0) {
      removeFirst(); // If it's the first element, use the removeFirst method
      return;
    }
    
    // Traverse the list to find the element before the one to remove
    Node<T> *cur = first;
    for (int i = 0; i < pos - 1; i++) {
      cur = cur->getNext();
    }
    
    // cur is now the node before the one to remove
    Node<T> *victim = cur->getNext();
    cur->setNext(victim->getNext()); // Bypass the node to be removed
    delete victim; // Free the memory of the removed node
    length--; // Decrease the size of the list
  }

    // ------------------------------------------------------------
  // Method to insert element with value v at position pos
  // ------------------------------------------------------------
  void insert(int pos, const T & v) {
    if (pos < 0 || pos > length) {
      return; // Position is invalid
    }
    
    if (pos == 0) {
      addFirst(v); // If it's the first position, use the addFirst method
      return;
    }
    
    if (pos == length) {
      addLast(v); // If it's the last position, use the addLast method
      return;
    }
    
    // Traverse the list to find the element before the insertion point
    Node<T> *cur = first;
    for (int i = 0; i < pos - 1; i++) {
      cur = cur->getNext();
    }
    
    // Create a new node and insert it at the position
    Node<T> *newNode = new Node<T>(v, cur->getNext());
    cur->setNext(newNode);
    length++; // Increase the size of the list
  }

    // ------------------------------------------------------------
  // Method to duplicate each element in the list
  // ------------------------------------------------------------
  void duplicate() {
    Node<T> *cur = first;

    while (cur != nullptr) {
      // Cria um novo nó duplicado com o mesmo valor de cur
      Node<T> *duplicateNode = new Node<T>(cur->getValue(), cur->getNext());
      
      // Inserir o nó duplicado após o nó atual
      cur->setNext(duplicateNode);
      
      // Avançar para o próximo nó original (pulando o duplicado)
      cur = duplicateNode->getNext();
      
      // Incrementar o tamanho da lista
      length++;
    }
  }

  // ------------------------------------------------------------
// Method to remove all occurrences of value v in the list
// ------------------------------------------------------------
void removeAll(const T & v) {
  // Caso especial: remover os primeiros elementos que coincidirem
  while (first != nullptr && first->getValue() == v) {
    removeFirst();  // Usa o método removeFirst para lidar com o primeiro nó
  }

  // Agora lidamos com o restante da lista
  Node<T> *cur = first;

  while (cur != nullptr && cur->getNext() != nullptr) {
    if (cur->getNext()->getValue() == v) {
      // Remover o nó seguinte se seu valor for igual a v
      Node<T> *victim = cur->getNext();
      cur->setNext(victim->getNext());
      delete victim; // Liberar a memória do nó removido
      length--;      // Decrementar o tamanho da lista
    } else {
      // Se não for igual, apenas avance
      cur = cur->getNext();
    }
  }
}



  
};


#endif