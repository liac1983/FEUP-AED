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

// number leafs
int numberLeafs() {
    return numberLeafs(root);
}

int numberLeafs(Node *n) {
    if (n == nullptr) return 0; // raiz não é uma folha
    if (n->left == nullptr && n->right == nullptr) return 1; // enontra uma folha conta 1
    return numberLeafs(n->left) + numberLeafs(n->right); // soma todas as folhas da subárvore
}

//binary tree
bool strict() {
    return isStrict(root);
}

bool isStrict(Node *n) {
    if (n == nullptr) return true; // arvore vazia (binária)
    if (n->left == nullptr && n->right == nullptr) return true; // folha (binária)
    if (n->left != nullptre && n->right != nullptr) // se tem dois filhos, verifica ambos
        return isStrict(n->left) && isStrict(n->right);
    return false; // caso de nó com um filho 
}

// retorna uma referencia para o valor guardado no seguinte path
T &path(std::string s) {
    if (s == "_" ) return root->value; // raiz da arvores
    return findPath(root, s, 0);
}

T &findPath(Node *n, std::string &s, int pos) {
    if (por == s.length() ) return n->value; // quando chega ao final do caminho retorna o valor do nó
    if (s[pos] == 'L') return findPath(n->left, s, pos+1); // caminho à esquerda
    return findPath(n->right, s, por+1); // caminho à direita
}

// numero do nos no nivel k
int nodesLevel(int k) {
    return countNodesAtLevel(root,0,k); // inicia a contagem a partir do nivel 0
}

int countNodesAtLevel(Node *n, int depth, int targetDepth) {
    if (n==nullptr) return 0; // nó nulo não comtribui para a contagem
    if (depth == targetDepth) return 1; // se estamos no vivel desejado conta1
    // soma dos nos nas subarvores da esquerda e da direita no proximo nivel
    return countNodesAtLevel(n->left, depth+1, targetDepth) +
            countAtLevel(n->right, depth + 1, targetDepth);
}

// conta o numero de nós com numeros pares
int countEven() {
    return countEvenNodes(root); // chma a função auxiliar com o nó raiz
}

int countEvenNodes(Node * n) {
    if (n == nullptr) return 0; // nó nulo não conta
    int count = (n->value %2 == 0) ? 1 : 0; // conta 1 se o nó for par
    // soma os nós pares da esquerda e da direita
    return count + countEvenNodes(n->left) + countEvenNodes(n->right);
}

// soma dos nós num determinado nivel
std::vector<int> sumLevels() {
    int h = height(); // altura da arvore
    std::vector<int> sums(h+1, 0); // inicia o vetor de somas com zero para cada nivel
    sumAtLevels(root, 0, sums); //popula o vetor de somas com a raiz
    return sums;
}

void sumAtLevels(Node *n, int depth, std::vector<int> &sums) {
    if (n == nullptr) return; // nó nulo não soma
    sums[depth] += n->value; // adiciona o valor da raiz
    sumAtLevels(n->left, depth+1, sums); // soma os valores da arvore da direita 
    sumAtLevels(n->right, depth+1, sums);
}

//retorna o caminho com L e R para a sequencia de nós com a maior soma
std::string maxSum() {
    int maxSum = 0; // maxima soma encontrada
    std::string maxPath = ""; // caminho para a soma correspondente
    findPath(root,0, "", maxSum, maxPath); // busca a partir da raiz
    return maxPath;
}

void findMaxSumPath(Node *n, int currentSum, std::string currentPath, int &maxSum, std::string &maxPath) {
    if (n == nnullptr) return; // nó nulo
    currentSum += n->value; //incluir o valor na soma atual 
    if (left == nullptr && n->right == nullptr) { // virifica se é folha
        if (currentSum > maxSum) { // se a soma atual for maior que a soma maxima stualiza
            maxSum = currentSum;
            maxPath = currentPath; // atualiza o caminho 
        }
        return;
    }
    if (n->left != nullptr) { // continua na subárvore da esquerda
        findMaxSumPath(n->left, currentSum, currentPath + "L" , maxSum, maxPath);

    }
    if (n->right != nullptr) {
        findMaxSumPath(n->right, currentSum, currentPath+"R", maxSum, maxPath);
    }
}


};

#endif