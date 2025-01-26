/* Mustafa Can Caliskan
 * 150200097
 * BLG335E HW3 */

#include <iostream>

namespace BST {
    struct Node {
        int data;
        std::string name;
        Node *parent;
        Node *left;
        Node *right;
    };
}

class BinarySearchTree {
private:

    BST::Node* root; //Root of the tree

    int howManyNode(BST::Node* root) { //getTotalNodes, starts with the root
        if (root == nullptr) { //if the travel reaches the end
            return 0;
        }
        return 1 + howManyNode(root->left) + howManyNode(root->right); //The program travels to the left and right node
    }

    void preorderWalk(BST::Node* root, std::pair<std::string, int> orderedData[], int& index) { //Traversing the tree in preorder and writing the elements into the given array sequentially
        if (root != nullptr) {
            orderedData[index++] = std::make_pair(root->name, root->data);
            preorderWalk(root->left, orderedData, index);
            preorderWalk(root->right, orderedData, index);
        }
    }
    void inorderWalk(BST::Node* root, std::pair<std::string, int> orderedData[], int& index) { //Traversing the tree in inorder (also sorting) and writing the elements into the given array sequentially
        if (root != nullptr) {
            inorderWalk(root->left, orderedData, index);
            orderedData[index++] = std::make_pair(root->name, root->data);
            inorderWalk(root->right, orderedData, index);
        }
    }

    void postorderWalk(BST::Node* root, std::pair<std::string, int> orderedData[], int& index) { //Traversing the tree in postorder and writing the elements into the given array sequentially
        if (root != nullptr) {
            postorderWalk(root->left, orderedData, index);
            postorderWalk(root->right, orderedData, index);
            orderedData[index++] = std::make_pair(root->name, root->data);
        }
    }

    BST::Node* searchNode(int value) { //Searches given value in tree
        BST::Node* iterPtr = this->root; 
        while (iterPtr != nullptr && iterPtr->data != value) {
            if (value < iterPtr->data) {
                iterPtr = iterPtr->left;
            } else {
                iterPtr = iterPtr->right;
            }
        }
        return iterPtr; //If given value is found in tree or travel reaches the end (not found will return iterNode as nullptr)
    }

    BST::Node* findMinNode(BST::Node* root) { //getminimum
        if (root == nullptr) { //If the root is null, it does not have any childs.
            return nullptr;
        }

        while (root->left != nullptr) { //Goes as far left as it can
            root = root->left;
        }
        return root;
    }

    BST::Node* findMaxNode(BST::Node* root) { //getmaximum
        if (root == nullptr) { //If the root is null, it does not have any childs.
            return nullptr;
        }

        while (root->right != nullptr) { //Goes as far right as it can
            root = root->right;
        }
        return root;
    }

    int calculateHeight(BST::Node* node) {
        if (node == nullptr) {
            return -1; // Empty subtree (at the end, if whole tree is empty, the total height is -1 + 1 = 0)
        }

        int leftHeight = calculateHeight(node->left); //Finds the height of the left subtrees.
        int rightHeight = calculateHeight(node->right); //Finds the height of the right subtrees.

        return ((leftHeight >= rightHeight) ? leftHeight : rightHeight) + 1; //Finds the maximum value of the heights.
    }

    BST::Node* findSuccessor(BST::Node* node) {
        if (node == nullptr) { //If the node is null, it does not have successor.
            return nullptr;
        }

        if (node->right != nullptr) { //Continuously search for the smallest value of the largest node.
            return findMinNode(node->right);
        }

        BST::Node* successor = nullptr;
        BST::Node* current = this->root; //potencial successor

        while (current != nullptr) {
            if (node->data < current->data) {
                successor = current;
                current = current->left;
            } else { //>=
                current = current->right;
            } 
        }

        return successor;
    }

    BST::Node* findPredecessor(BST::Node* node) {
        if (node == nullptr) { //If the node is null, it does not have predecessor.
            return nullptr;
        }

        if (node->left != nullptr) { //Continuously search for the largest value of the smallest node.
            return findMaxNode(node->left);
        }

        BST::Node* predecessor = nullptr;
        BST::Node* current = this->root; //potential predecessor
        while (current != nullptr) {
            if (node->data > current->data) {
                predecessor = current;
                current = current->right;
            } else { //<=
                current = current->left;
            }
        }

        return predecessor;
    }

    BST::Node* insertNode(BST::Node* root, int value, const std::string& name) {
        if (root == nullptr) {
            root = new BST::Node{value, name, nullptr, nullptr, nullptr};
        } else if (value < root->data) {
            root->left = insertNode(root->left, value, name);
            root->left->parent = root;
        } else if (value >= root->data) { //If the values are equal, it will be successor automatically. We do not need to find its successor explicitly.
            root->right = insertNode(root->right, value, name);
            root->right->parent = root;
        }
        return root;
    }

    BST::Node* deleteNode(BST::Node*& root, int value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        } else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        } else {
            if (root->left == nullptr) {
                BST::Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BST::Node* temp = root->left;
                delete root;
                return temp;
            }

            BST::Node* temp = findMinNode(root->right);
            root->data = temp->data;
            root->name = temp->name;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }


public: //Public functions that called from main.cpp
    BinarySearchTree() {
        this->root = nullptr;
    }

    void preorder(std::pair<std::string, int> orderedData[], int index) {
        preorderWalk(this->root, orderedData, index);
    }

    void inorder(std::pair<std::string, int> orderedData[], int index) {
        inorderWalk(this->root, orderedData, index);
    }

    void postorder(std::pair<std::string, int> orderedData[], int index) {
        postorderWalk(this->root, orderedData, index);
    }

    BST::Node* searchTree(int value) {
        return searchNode(value);
    }

    BST::Node* successor(BST::Node* givenNode) {
        return findSuccessor(givenNode);
    }

    BST::Node* predecessor(BST::Node* givenNode) {
        return findPredecessor(givenNode);
    }

    void insert(const std::string& name, int value) {
        this->root = insertNode(this->root, value, name);
    }

    void deleteNode(int value) {
        this->root = deleteNode(this->root, value);
    }

    int getHeight() {
        return calculateHeight(this->root);
    }

    BST::Node* getMinimum() {
        return findMinNode(this->root);
    }

    BST::Node* getMaximum() {
        return findMaxNode(this->root);
    }

    int getTotalNodes() {
        return howManyNode(this->root);
    }
}; 
