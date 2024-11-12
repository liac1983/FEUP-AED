// -------------------------------------------------------------
// Algoritmos e Estruturas de Dados 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// Example of how to use a the BTree<T> class
// Last update: 09/11/2024
// -------------------------------------------------------------

#include "binaryTree.h"

int main() {

  BTree<int> t; // Create an empty tree of integers
  t.read("N");  // Read contents from stdin, using "N" as nullptr

  // Call some of the methods the class provides
  std::cout << "numberNodes = " << t.numberNodes() << std::endl;  
  std::cout << "height = "      << t.height() << std::endl;
  std::cout << "contains(2) = " << t.contains(2) << std::endl;
  std::cout << "contains(3) = " << t.contains(3) << std::endl;

  // Print nodes in several possible orders
  t.printPreOrder();
  t.printInOrder();
  t.printPostOrder();
  t.printBFS();
  t.printDFS();
  
  return 0;
}
/*
#include "binaryTree.h"
#include <string> // Inclui suporte a std::string

int main() {

  BTree<std::string> t; // Cria uma árvore binária de strings
  t.read("N");  // Lê o conteúdo da árvore a partir da entrada padrão, com "N" representando nullptr

  // Chamadas de métodos para testar funcionalidades
  std::cout << "numberNodes = " << t.numberNodes() << std::endl;  
  std::cout << "height = " << t.height() << std::endl;
  std::cout << "contains(\"orange\") = " << t.contains("orange") << std::endl;
  std::cout << "contains(\"banana\") = " << t.contains("banana") << std::endl;

  // Imprime os nós em várias ordens de travessia
  t.printPreOrder();
  t.printInOrder();
  t.printPostOrder();
  t.printBFS();
  t.printDFS();
  
  return 0;
}*/

