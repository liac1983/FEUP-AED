#include <iostream>
#include <vector>
#include <unordered_map>

class BinaryTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int leafCount;

    // Recursive function to reconstruct the tree
    Node* buildTree(const std::vector<int>& preorder, int preStart, int preEnd,
                    const std::vector<int>& inorder, int inStart, int inEnd,
                    std::unordered_map<int, int>& inorderIndexMap) {
        if (preStart > preEnd || inStart > inEnd) return nullptr;

        // The root node value is the first element in preorder range
        int rootValue = preorder[preStart];
        Node* node = new Node(rootValue);

        // Find the index of the root in inorder array
        int inRootIndex = inorderIndexMap[rootValue];
        int leftTreeSize = inRootIndex - inStart;

        // Recursively build left and right subtrees
        node->left = buildTree(preorder, preStart + 1, preStart + leftTreeSize,
                               inorder, inStart, inRootIndex - 1, inorderIndexMap);
        node->right = buildTree(preorder, preStart + leftTreeSize + 1, preEnd,
                                inorder, inRootIndex + 1, inEnd, inorderIndexMap);

        return node;
    }

    // Postorder traversal to get the output
    void postorderTraversal(Node* node, std::vector<int>& result) {
        if (node == nullptr) return;
        postorderTraversal(node->left, result);
        postorderTraversal(node->right, result);
        result.push_back(node->value);
    }

    // Count leaf nodes
    int countLeaves(Node* node) {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

public:
    BinaryTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
        int n = preorder.size();
        std::unordered_map<int, int> inorderIndexMap;
        for (int i = 0; i < n; ++i) {
            inorderIndexMap[inorder[i]] = i;
        }
        root = buildTree(preorder, 0, n - 1, inorder, 0, n - 1, inorderIndexMap);
        leafCount = countLeaves(root);
    }

    std::vector<int> getPostorder() {
        std::vector<int> result;
        postorderTraversal(root, result);
        return result;
    }

    int getLeafCount() {
        return leafCount;
    }
};

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<int> preorder(N), inorder(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> preorder[i];
        }
        for (int i = 0; i < N; ++i) {
            std::cin >> inorder[i];
        }

        // Build the binary tree from preorder and inorder
        BinaryTree tree(preorder, inorder);

        // Get postorder representation
        std::vector<int> postorder = tree.getPostorder();
        for (size_t i = 0; i < postorder.size(); ++i) {
            if (i > 0) std::cout << " ";
            std::cout << postorder[i];
        }
        std::cout << std::endl;

        // Print the number of leaf nodes
        std::cout << "leafs = " << tree.getLeafCount() << std::endl;
    }

    return 0;
}

