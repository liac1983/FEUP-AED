// -------------------------------------------------------------
// Algoritmos e Estruturas de Dados 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// Binary Search Tree
// Last update: 16/11/2024
// -------------------------------------------------------------

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

template <class T> class BSTree {
private:
  struct Node {
    T value;            // The value stored on the node
    Node *left, *right; // Pointers to left and right child
  };
  
  Node *root;
  
public:

  // Constructor: initially the tree is empty
  BSTree() {
    root = nullptr;
  }

  // Destructor: delete all nodes (garbage collection)
  ~BSTree() {
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
  // Count the number of nodes
  // ---------------------------------------------------------
  
  int numberNodes() {
    return numberNodes(root);
  }   
  
  int numberNodes(Node *n) {
    if (n == nullptr) return 0;
    return 1 + numberNodes(n->left) + numberNodes(n->right);
  }

  // ---------------------------------------------------------
  // Height of the tree
  // ---------------------------------------------------------

  int height() {
    return height(root);
  }
  
  int height(Node *n) {
    if (n == nullptr) return -1;
    return 1 + std::max(height(n->left), height(n->right));
  }

  // ---------------------------------------------------------
  // Does the tree contain value 'val' ?
  // ---------------------------------------------------------

  bool contains(const T & val) {
    return contains(root, val);
  }

  bool contains(Node *n, const T & val) {
    if (n == nullptr) return false;
    if (val < n->value) return contains(n->left, val);
    if (val > n->value) return contains(n->right, val);
    return true;
  }

  // ---------------------------------------------------------
  // Insert value 'val' in the tree
  // ---------------------------------------------------------
  
  bool insert(const T & val) {
    if (contains(val)) return false;
    root = insert(root, val);
    return true;
  }

  Node *insert(Node *n, const T & val) {
    if (n == nullptr) {
      Node *aux = new Node;
      aux->value = val;
      aux->left = aux->right = nullptr;
      return aux;
    } else if (val < n->value) {
      n->left = insert(n->left, val);
    } else if (val > n->value) {
      n->right = insert(n->right, val);
    }
    return n;
  }

  // ---------------------------------------------------------
  // Remove value 'val' from the tree
  // ---------------------------------------------------------

  bool remove(const T & val) {
    if (!contains(val)) return false;
    root = remove(root, val);
    return true;
  }

  Node *remove(Node *n, const T & val) {
    if (val < n->value) n->left = remove(n->left, val);
    if (val > n->value) n->right = remove(n->right, val);
    else if (n->left == nullptr) {
      Node *tmp = n->right;
      delete n;
      return tmp;
    } else if (n->right == nullptr) {
      Node *tmp = n->left;
      delete n;
      return tmp;
    } else {
      Node *max = n->left;
      while (max->right != nullptr) max = max->right;
      n->value = max->value;
      n->left = remove(n->left, max->value);
    }
    return n;
  }
  
  // ---------------------------------------------------------
  // Print tree in preorder, incluing N for the null values
  // ---------------------------------------------------------  
  
  void printPreOrder() {
    std::cout << "preOrder:";
    printPreOrder(root);
    std::cout << std::endl;
  }

  void printPreOrder(Node *n) {
    if (n == nullptr)
      std::cout << " N";
    else {
      std::cout << " " << n->value;
      printPreOrder(n->left);
      printPreOrder(n->right);
    }
  }
  
  // ---------------------------------------------------------
  // TODO: put the functions you need to implement below this
  // ---------------------------------------------------------
  
  // ---------------------------------------------------------
  // Method to calculate the imbalance of a node
  // ---------------------------------------------------------
  // Função para calcular o fator de balanceamento de um nó em uma arvore binaria ou AVL
  int balance(const T & val) {
    // nó correspondente ao valor val na arvore, começando pela raiz
    Node *node = findNode(root, val);
    // Se o nó for encontrado, retorna 0 ( arvore balanceada em relação a esse valor inexistente)
    if (node == nullptr) return 0;
    // Retorna o fator de balanceamento
    // diferença entre a altura da subarvore direita e a altura da subarvore esquerda do nó
    return height(node->right) - height(node->left);
  }
  // Função para encontrar um nó val na arvore binaria
  Node *findNode(Node *n, const T & val) {
    // Se o nó for nulo, o valor está na arvore
    if (n == nullptr) return nullptr;
    // Se o valor procurado for menor que o valor do nó atual, busca na subarvore esq
    if (val < n->value) return findNode(n->left, val);
    if (val > n->value) return findNode(n->right, val);
    return n; // Se o valor do nó for igual ao valor procurado, retorna nó
  }

    // ---------------------------------------------------------
    // Check if the tree is an AVL tree
    // ---------------------------------------------------------
    bool isAVL() {
        return isAVL(root).first;
    }

    // Helper function to check AVL property and calculate height
    std::pair<bool, int> isAVL(Node *n) {
        if (n == nullptr) {
            return {true, -1}; // An empty tree is AVL with height -1
        }

        // Check left and right subtrees
        auto left = isAVL(n->left);
        auto right = isAVL(n->right);

        // Calculate balance factor
        int balance = std::abs(left.second - right.second);

        // The tree is AVL if:
        // 1. Both left and right subtrees are AVL
        // 2. The balance factor at this node is <= 1
        bool isAVLTree = left.first && right.first && (balance <= 1);

        // Height of the current node
        int height = 1 + std::max(left.second, right.second);

        return {isAVLTree, height};
    }
    // ---------------------------------------------------------
    // Right Rotate at the node with value x
    // ---------------------------------------------------------
    void rightRotate(const T &x) {
        root = rightRotate(root, x);
    }

    // Helper function to perform the right rotation
    Node* rightRotate(Node *n, const T &x) {
        if (n == nullptr) return n; // Base case: node not found

        if (x < n->value) {
            // Search in the left subtree
            n->left = rightRotate(n->left, x);
        } else if (x > n->value) {
            // Search in the right subtree
            n->right = rightRotate(n->right, x);
        } else {
            // Node found, perform the rotation if possible
            if (n->left == nullptr) return n; // Rotation not possible without a left child

            Node *newRoot = n->left;        // The left child becomes the new root
            n->left = newRoot->right;      // Right subtree of the left child becomes the left subtree of the original node
            newRoot->right = n;            // Original node becomes the right child of the new root
            return newRoot;                // Return the new root
        }

        return n; // Return the unchanged node
    }



  
};



#endif
