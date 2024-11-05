// -------------------------------------------------------------
// Algoritmos e Estruturas de Dados 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// Example of how to use a the SinglyLinkedList<T> class
// Last update: 20/10/2024
// -------------------------------------------------------------

#include <iostream>

#include "singlyLinkedList.h"

template <typename T>
void print(SinglyLinkedList<T> & lst){
  std::cout << lst.toString() << std::endl;
}
  

int main(){
  // Create a list of integers
  SinglyLinkedList<int> list;

  // writing the list (at the start it is empty)
  print(list);

  // Checking whether it is empty
  std::cout << "isEmpty? " << list.isEmpty() << std::endl;
      
  // insert the numbers 1 to 5 at the end
  for (int i=1; i<=5; i++)
         list.addLast(i);  
  print(list);

  // insert the numbers 6 to 10 at the front of the list
  for (int i=6; i<=10; i++)
    list.addFirst(i);
  print(list);

  // checking the size of the list
  std::cout << "size = " <<  list.size() << std::endl;

  // Removing the first element
  list.removeFirst();
  print(list);

  // Removing the last element
  list.removeLast();
  print(list);

  // Checking whether it is empty
  std::cout << "isEmpty? " << list.isEmpty() << std::endl;

  // Writing the first and the last elements
  std::cout << "getFirst() = " << list.getFirst() << std::endl;
  std::cout << "getLast() = " <<  list.getLast() << std::endl;

  return 0;
}  

// 1.b
/* int main(){
  // Create a singly linked list of characters
  SinglyLinkedList<char> vowelList;

  // Add the 5 vowels to the list
  vowelList.addLast('a');
  vowelList.addLast('e');
  vowelList.addLast('i');
  vowelList.addLast('o');
  vowelList.addLast('u');

  // Print the list of vowels
  std::cout << "Singly linked list of vowels: ";
  print(vowelList);

  // Checking whether it is empty
  std::cout << "isEmpty? " << vowelList.isEmpty() << std::endl;

  // Checking the size of the list
  std::cout << "size = " <<  vowelList.size() << std::endl;

  // Accessing the first and last elements
  std::cout << "getFirst() = " << vowelList.getFirst() << std::endl;
  std::cout << "getLast() = " << vowelList.getLast() << std::endl;

  return 0;
} */

// 1.c
/* int main(){
  // Create an empty singly linked list of integers
  SinglyLinkedList<int> emptyList;

  // Try to remove the first element from the empty list
  std::cout << "Trying to remove first element from empty list..." << std::endl;
  emptyList.removeFirst();

  // Try to remove the last element from the empty list
  std::cout << "Trying to remove last element from empty list..." << std::endl;
  emptyList.removeLast();

  // Try to access the first element from the empty list (should trigger an assert failure)
  std::cout << "Trying to access first element from empty list..." << std::endl;
  try {
    emptyList.getFirst(); // This should trigger the assert and terminate the program
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  // Try to access the last element from the empty list (should trigger an assert failure)
  std::cout << "Trying to access last element from empty list..." << std::endl;
  try {
    emptyList.getLast(); // This should trigger the assert and terminate the program
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  return 0;
} */

