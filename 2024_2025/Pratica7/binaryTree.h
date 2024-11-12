// -------------------------------------------------------------
// Algoritmos e Estruturas de Dados 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// Binary Tree
// Last update: 09/11/2024
// -------------------------------------------------------------

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <queue>
#include <stack>

template <class T> class BTree {
private:
  struct Node {
    T value;            // The value stored on the node
    Node *left, *right; // Pointers to left and right child
  };

  // The tree 
  Node *root;           // Pointer to the root node
  
public:

  // Constructor: initially the tree is empty
  BTree() {
    root = nullptr;
  }

  // Destructor: delete all nodes (garbage collection) [see slide 33]
  ~BTree() {
    destroy(root);
  }

  // Recursively delete left and right subtrees and then current node
  void destroy(Node *n) {
    if (n == nullptr) return;
    destroy(n->left);
    destroy(n->right);
    delete n;
  }


  // ---------------------------------------------------------
  // Count the number of nodes (see slides 13 and 14)
  // ---------------------------------------------------------
  
  int numberNodes() {
    return numberNodes(root);
  }   
  
  int numberNodes(Node *n) {
    if (n == nullptr) return 0;
    return 1 + numberNodes(n->left) + numberNodes(n->right);
  }

  // ---------------------------------------------------------
  // Height of the tree (see slides 15 and 16)
  // ---------------------------------------------------------

  int height() {
    return height(root);
  }
  
  int height(Node *n) {
    if (n == nullptr) return -1;
    return 1 + std::max(height(n->left), height(n->right));
  }

  // ---------------------------------------------------------
  // Does the tree contain value 'val'? (see slides 17 and 18)
  // ---------------------------------------------------------
  
  bool contains(const T & val) {
    return contains(root, val);
  }

  bool contains(Node *n, const T & val) {
    if (n == nullptr) return false;
    if (n->value == val) return true;
    return contains(n->left, val) || contains(n->right, val);
  }  

  // ---------------------------------------------------------
  // Print tree in PreOrder (see slides 20 and 21)
  // ---------------------------------------------------------

  void printPreOrder() {
    std::cout << "PreOrder:";
    printPreOrder(root);
    std::cout << std::endl;
  }

  void printPreOrder(Node *n) {
    if (n == nullptr) return;
    std::cout << " " << n->value;
    printPreOrder(n->left);
    printPreOrder(n->right);
  }

  // ---------------------------------------------------------
  // Print tree in InOrder (see slides 22 and 23)
  // ---------------------------------------------------------
  
  void printInOrder() {
    std::cout << "InOrder:";
    printInOrder(root);
    std::cout << std::endl;
  }

  void printInOrder(Node *n) {
    if (n == nullptr) return;
    printInOrder(n->left);
    std::cout << " " << n->value;
    printInOrder(n->right);
  }

  // ---------------------------------------------------------
  // Print tree in PostOrder (see slides 22 and 24)
  // ---------------------------------------------------------
  
  void printPostOrder() {
    std::cout << "PostOrder:";
    printPostOrder(root);
    std::cout << std::endl;
  }

  void printPostOrder(Node *n) {
    if (n == nullptr) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    std::cout << " " << n->value;
  } 

  // ---------------------------------------------------------
  // Print tree in Breadt-First order using a queue
  // (see slides 25, 26 and 27)
  // ---------------------------------------------------------

  void printBFS() {
    std::cout << "BFS:";

    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
      Node *cur = q.front();
      q.pop();
      if (cur != nullptr) {
        std::cout << " " << cur->value;
        q.push(cur->left);
        q.push(cur->right);
      }
    }
    
    std::cout << std::endl;
  }

  // ---------------------------------------------------------
  // Print tree in Depth-First order using a stack
  // (see slides 28 and 29)
  // ---------------------------------------------------------
  
  void printDFS() {
    std::cout << "DFS:";

    std::stack<Node *> s;
    s.push(root);
    while (!s.empty()) {
      Node *cur = s.top();
      s.pop();
      if (cur != nullptr) {
        std::cout << " " << cur->value;
        s.push(cur->left);
        s.push(cur->right);
      }
    }
    
    std::cout << std::endl;
  }

  // ---------------------------------------------------------
  // Read a tree in PreOrder from standard input
  // (see slides 30, 31 and 32)
  // ---------------------------------------------------------

  void read(std::string null) {
    root = readNode(null);
  }
  
  Node *readNode(std::string null) {
    std::string buffer;
    std::cin >> buffer;
    if (buffer == null) return nullptr;
    Node *n = new Node;
    std::istringstream ss(buffer);
    ss >> n->value;
    n->left = readNode(null);
    n->right = readNode(null);    
    return n;
  }

  // ---------------------------------------------------------
  // TODO: put the functions you need to implement below this
  // ---------------------------------------------------------

    // ---------------------------------------------------------
    // Count the number of leaf nodes in the tree
    // ---------------------------------------------------------
    int numberLeafs() {
    return numberLeafs(root); // Chama a função auxiliar com o nó raiz
    }

    int numberLeafs(Node *n) {
    if (n == nullptr) return 0;             // Caso base: nó nulo, não é folha
    if (n->left == nullptr && n->right == nullptr) return 1; // Caso folha, conta 1
    return numberLeafs(n->left) + numberLeafs(n->right);     // Soma das folhas das subárvores
    }

    // ---------------------------------------------------------
    // Check if the tree is strictly binary
    // ---------------------------------------------------------
    bool strict() {
    return isStrict(root); // Chama a função auxiliar com o nó raiz
    }

    bool isStrict(Node *n) {
    if (n == nullptr) return true; // Árvore vazia é estritamente binária
    if (n->left == nullptr && n->right == nullptr) return true; // Folha é estritamente binária
    if (n->left != nullptr && n->right != nullptr) // Se tem dois filhos, verifica ambos
        return isStrict(n->left) && isStrict(n->right);
    return false; // Caso de nó com um filho
    }

    // ---------------------------------------------------------
    // Access the value at a given path in the tree
    // ---------------------------------------------------------
    T &path(std::string s) {
    if (s == "_") return root->value; // Caminho especial "_" refere-se à raiz
    return findPath(root, s, 0);      // Chama a função auxiliar com a raiz e caminho
    }

    T &findPath(Node *n, std::string &s, int pos) {
    if (pos == s.length()) return n->value; // Se chegamos ao final do caminho, retorna o valor do nó
    if (s[pos] == 'L') return findPath(n->left, s, pos + 1); // Caminho à esquerda
    return findPath(n->right, s, pos + 1); // Caminho à direita
    }

    // ---------------------------------------------------------
    // Count the number of nodes at a certain depth
    // ---------------------------------------------------------
    int nodesLevel(int k) {
    return countNodesAtLevel(root, 0, k); // Inicia a contagem a partir do nível 0
    }

    int countNodesAtLevel(Node *n, int depth, int targetDepth) {
    if (n == nullptr) return 0; // Caso base: nó nulo não contribui
    if (depth == targetDepth) return 1; // Se estamos no nível desejado, conta 1
    // Soma dos nós nas subárvores esquerda e direita no próximo nível
    return countNodesAtLevel(n->left, depth + 1, targetDepth) +
            countNodesAtLevel(n->right, depth + 1, targetDepth);
    }

    // ---------------------------------------------------------
    // Count the number of nodes with even values in the tree
    // ---------------------------------------------------------
    int countEven() {
    return countEvenNodes(root); // Chama a função auxiliar com o nó raiz
    }

    int countEvenNodes(Node *n) {
    if (n == nullptr) return 0; // Caso base: nó nulo não conta
    int count = (n->value % 2 == 0) ? 1 : 0; // Conta 1 se o valor do nó for par
    // Soma os nós pares nas subárvores esquerda e direita
    return count + countEvenNodes(n->left) + countEvenNodes(n->right);
    }

    // ---------------------------------------------------------
    // Sum of nodes at each level in the tree
    // ---------------------------------------------------------
    std::vector<int> sumLevels() {
    int h = height(); // Calcula a altura da árvore
    std::vector<int> sums(h + 1, 0); // Inicializa o vetor de somas com zeros para cada nível
    sumAtLevels(root, 0, sums); // Popula o vetor de somas começando da raiz
    return sums;
    }

    void sumAtLevels(Node *n, int depth, std::vector<int> &sums) {
    if (n == nullptr) return; // Se o nó é nulo, não contribui para a soma
    sums[depth] += n->value; // Adiciona o valor do nó à soma do nível atual
    sumAtLevels(n->left, depth + 1, sums); // Chama recursivamente para a subárvore esquerda
    sumAtLevels(n->right, depth + 1, sums); // Chama recursivamente para a subárvore direita
    }

    // ---------------------------------------------------------
    // Find the path with the maximum sum in the tree
    // ---------------------------------------------------------
    std::string maxSum() {
    int maxSum = 0;           // Armazena a soma máxima encontrada
    std::string maxPath = ""; // Armazena o caminho correspondente à soma máxima
    findMaxSumPath(root, 0, "", maxSum, maxPath); // Inicia a busca a partir da raiz
    return maxPath;
    }

    void findMaxSumPath(Node *n, int currentSum, std::string currentPath, int &maxSum, std::string &maxPath) {
    if (n == nullptr) return; // Caso base: nó nulo não contribui para a soma

    // Atualiza a soma atual ao incluir o valor do nó atual
    currentSum += n->value;

    // Verifica se é uma folha
    if (n->left == nullptr && n->right == nullptr) {
        // Se a soma atual for maior que a soma máxima, atualiza
        if (currentSum > maxSum) {
        maxSum = currentSum;
        maxPath = currentPath; // Atualiza o caminho máximo com o caminho atual
        }
        return;
    }

    // Continua para a subárvore esquerda com o caminho "L"
    if (n->left != nullptr) {
        findMaxSumPath(n->left, currentSum, currentPath + "L", maxSum, maxPath);
    }

    // Continua para a subárvore direita com o caminho "R"
    if (n->right != nullptr) {
        findMaxSumPath(n->right, currentSum, currentPath + "R", maxSum, maxPath);
    }
    }




};



#endif
