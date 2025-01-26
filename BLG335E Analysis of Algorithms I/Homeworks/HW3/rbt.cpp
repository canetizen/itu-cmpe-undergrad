/* Mustafa Can Caliskan
 * 150200097
 * BLG335E HW3 */

#include <iostream>

namespace RBT {
    enum Color {BLACK, RED}; //black = 0, red = 1
    struct Node {
        int data;
        std::string name;
        Node *parent;
        Node *left;
        Node *right;
        int color;
    };
}

class RedBlackTree {
private:
    RBT::Node* root;

    int howManyNode(RBT::Node* root) { //getTotalNodes, starts with the root
        if (root == nullptr) { //if the travel reaches the end
            return 0;
        }
        return 1 + howManyNode(root->left) + howManyNode(root->right); //The program travels to the left and right node
    }

    void preorderWalk(RBT::Node* root, std::pair<std::string, int> orderedData[], int& index) { //Traversing the tree in preorder and writing the elements into the given array sequentially
        if (root != nullptr) {
            orderedData[index++] = std::make_pair(root->name, root->data);
            preorderWalk(root->left, orderedData, index);
            preorderWalk(root->right, orderedData, index);
        }
    }

    void inorderWalk(RBT::Node* root, std::pair<std::string, int> orderedData[], int& index) { //Traversing the tree in inorder (also sorting) and writing the elements into the given array sequentially
        if (root != nullptr) {
            inorderWalk(root->left, orderedData, index);
            orderedData[index++] = std::make_pair(root->name, root->data);
            inorderWalk(root->right, orderedData, index);
        }
    }

    void postorderWalk(RBT::Node* root, std::pair<std::string, int> orderedData[], int& index) { //Traversing the tree in postorder and writing the elements into the given array sequentially
        if (root != nullptr) {
            postorderWalk(root->left, orderedData, index);
            postorderWalk(root->right, orderedData, index);
            orderedData[index++] = std::make_pair(root->name, root->data);
        }
    }

    RBT::Node* searchNode(int value) { //Searches given value in tree
        RBT::Node* iterPtr = this->root; 
        while (iterPtr != nullptr && iterPtr->data != value) {
            if (value < iterPtr->data) {
                iterPtr = iterPtr->left;
            } else {
                iterPtr = iterPtr->right;
            }
        }

        return iterPtr; //If given value is found in tree or travel reaches the end (not found will return iterNode as nullptr)
    }

    RBT::Node* findMinNode(RBT::Node* root) { //getminimum
        if (root == nullptr) { //If the root is null, it does not have any childs.
            return nullptr;
        }

        while (root->left != nullptr) { //Goes as far left as it can
            root = root->left;
        }
        return root;
    }

    RBT::Node* findMaxNode(RBT::Node* root) { //getmaximum
        if (root == nullptr) { //If the root is null, it does not have any childs.
            return nullptr;
        }

        while (root->right != nullptr) { //Goes as far right as it can
            root = root->right;
        }
        return root;
    }

    int calculateHeight(RBT::Node* node) {
        if (node == nullptr) {
            return -1; // Empty tree (at the end, the total height is -1 + 1 = 0)
        }

        int leftHeight = calculateHeight(node->left); //Finds the height of the left subtrees.
        int rightHeight = calculateHeight(node->right); //Finds the height of the right subtrees.

        return ((leftHeight >= rightHeight) ? leftHeight : rightHeight) + 1; //Returns the maximum of leftHeight and rightHeight + 1
    }

    RBT::Node* findSuccessor(RBT::Node* node) {
        if (node == nullptr) { //If the node is null, it does not have successor.
            return nullptr;
        }

        if (node->right != nullptr) { //Continuously search for the smallest value of the largest node.
            return findMinNode(node->right);
        }

        RBT::Node* successor = nullptr;
        RBT::Node* current = this->root; //potencial successor

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

    RBT::Node* findPredecessor(RBT::Node* node) {
        if (node == nullptr) { //If the node is null, it does not have predecessor.
            return nullptr;
        }

        if (node->left != nullptr) { //Continuously search for the largest value of the smallest node.
            return findMaxNode(node->left);
        }

        RBT::Node* predecessor = nullptr;
        RBT::Node* current = this->root; //potential predecessor
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

    RBT::Node* leftRotation(RBT::Node* root, RBT::Node *a) { //Rotation operations
        RBT::Node *b = a->right;
        a->right = b->left;
        if (b->left != nullptr) {
            b->left->parent = a;
        }
        b->parent = a->parent;
        if (a->parent == nullptr) {
            root = b;
        } else if (a == a->parent->left) {
            a->parent->left = b;
        } else {
            a->parent->right = b;
        }
        b->left = a;
        a->parent = b;
        return root;
    }

    RBT::Node* rightRotation(RBT::Node* root, RBT::Node *b) { //Rotation operations
        RBT::Node *a = b->left;
        b->left = a->right;
        if (a->right != nullptr) {
            a->right->parent = b;
        }
        a->parent = b->parent;
        if (b->parent == nullptr) {
            root = a;
        } else if (b == b->parent->left) {
            b->parent->left = a;
        } else {
            b->parent->right = a;
        }
        a->right = b;
        b->parent = a;
        return root;
    }

    void fixInserting(RBT::Node*& root, RBT::Node *c) {
        while (c != root && c->parent->color == RBT::Color::RED) {
            if (c->parent == c->parent->parent->left) {
                RBT::Node* b = c->parent->parent->right; // Node's parent is a left child
                if (b != nullptr && b->color == RBT::Color::RED) { //Uncle is red
                    c->parent->color = RBT::Color::BLACK;
                    b->color = RBT::Color::BLACK;
                    c->parent->parent->color = RBT::Color::RED;
                    c = c->parent->parent; 
                } else { //Uncle is black
                    if (c == c->parent->right) {
                        c = c->parent;
                        root = leftRotation(root, c);
                    }
                    //Uncle is BLACK and c is a left child
                    c->parent->color = RBT::Color::BLACK;
                    c->parent->parent->color = RBT::Color::RED;
                    root = rightRotation(root, c->parent->parent);
                }
            } else { // Node's parent is a right child
                RBT::Node* b = c->parent->parent->left;
                if (b != nullptr && b->color == RBT::Color::RED) { //Uncle is red
                    c->parent->color = RBT::Color::BLACK;
                    b->color = RBT::Color::BLACK;
                    c->parent->parent->color = RBT::Color::RED;
                    c = c->parent->parent;
                } else { //Uncle is black
                    if (c == c->parent->left) {
                        c = c->parent;
                        root = rightRotation(root, c);
                    }
                    c->parent->color = RBT::Color::BLACK; //Uncle is black and c is a right child
                    c->parent->parent->color = RBT::Color::RED;
                    root = leftRotation(root, c->parent->parent);
                }
            }
        }
        root->color = RBT::Color::BLACK; // Ensure the root remains black
    }

    RBT::Node* insertNode(RBT::Node* root, int value, const std::string& name) {
        RBT::Node *a = root;
        RBT::Node *b = nullptr;
        RBT::Node *c = new RBT::Node{value, name, nullptr, nullptr, nullptr, RBT::Color::RED}; // Create a new node with the given population and city name
        while (a != nullptr) { // Traverse the tree to find the insertion position
            b = a;
            if (c->data < a->data) {
                a = a->left;
            } else {
                a = a->right;
            }
        }
        c->parent = b; // Set parent and child relationships for the new node
        if (b == nullptr) {
            root = c;
        } else if (c->data < b->data) {
            b->left = c;
        } else {
            b->right = c;
        }

        c->color = RBT::Color::RED; // New node is initially constructed as red

        fixInserting(root, c); // Fix any violations

        while (root->parent != nullptr) {
            root = root->parent;
        }
        root->color = RBT::Color::BLACK;

        return root;
    }

    void fixDeleting(RBT::Node*& root, RBT::Node* a) { // Fix rule violations in the rbt after deletion
        if (a != nullptr) {
            while (a != root && a->color == RBT::Color::BLACK) { // Continue fixing until a is not the root and its color is black
                if (a == a->parent->left) { // Node a is a left child
                    RBT::Node* w = a->parent->right;
                    if (w->color == RBT::Color::RED) { //Sibling w is red
                        w->color = RBT::Color::BLACK;
                        a->parent->color = RBT::Color::RED;
                        root = leftRotation(root, a->parent);
                        w = a->parent->right;
                    } //Both of w's children are black
                    if (w->left->color == RBT::Color::BLACK && w->right->color == RBT::Color::BLACK) {
                        w->color = RBT::Color::RED;
                        a = a->parent;
                    } else { //w's right child is black
                        if (w->right->color == RBT::Color::BLACK) {
                            w->left->color = RBT::Color::BLACK;
                            w->color = RBT::Color::RED;
                            root = rightRotation(root, w);
                            w = a->parent->right;
                        } //Restructuring
                        w->color = a->parent->color;
                        a->parent->color = RBT::Color::BLACK;
                        w->right->color = RBT::Color::BLACK;
                        root = leftRotation(root, a->parent);
                        a = root;
                    }
                } else { // Node a is a right child
                    RBT::Node* w = a->parent->left;
                    if (w->color == RBT::Color::RED) {
                        w->color = RBT::Color::BLACK;
                        a->parent->color = RBT::Color::RED;
                        root = rightRotation(root, a->parent);
                        w = a->parent->left;
                    }
                    if (w->right->color == RBT::Color::BLACK && w->left->color == RBT::Color::BLACK) {
                        w->color = RBT::Color::RED;
                        a = a->parent;
                    } else {
                        if (w->left->color == RBT::Color::BLACK) {
                            w->right->color = RBT::Color::BLACK;
                            w->color = RBT::Color::RED;
                            root = leftRotation(root, w);
                            w = a->parent->left;
                        }
                        w->color = a->parent->color;
                        a->parent->color = RBT::Color::BLACK;
                        w->left->color = RBT::Color::BLACK;
                        root = rightRotation(root, a->parent);
                        a = root;
                    }
                }
            }
            a->color = RBT::Color::BLACK; // Ensure a is black
        }
    }

    RBT::Node* transplantOperation(RBT::Node* root, RBT::Node* u, RBT::Node* v) { // Replace node u with node v in the rbt
        if (u->parent == nullptr) { // If u is the root node, update the root with v
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;  // If u is a left child, replace u with v as the left child of its parent
        } else {
            u->parent->right = v; // If u is a right child, replace u with v as the right child of its parent
        }

        if (v != nullptr) {
            v->parent = u->parent; // Update the parent pointer of v to point to u's parent
        }

        return root;
    }
        
    RBT::Node* deleteNode(RBT::Node* root, int value) {
        if (root == nullptr) { // If the tree is empty, no deletion needed
            return root;
        }

        RBT::Node* c = searchNode(value); // Find the node to be deleted

        if (c == nullptr) { // If the node with the value is not found, return the tree as is
            return root;
        }
        
        RBT::Node* a = nullptr;
        RBT::Node* b = c; // Backup node pointers and colors for later use
        int yOriginal = b->color;

        if (c->left == nullptr) { // Node has no left child
            a = c->right;
            root = transplantOperation(root, c, c->right);
        } else if (c->right == nullptr) { // Node has no right child
            a = c->left;
            root = transplantOperation(root, c, c->left);
        } else {// Node has both left and right children
            b = findMinNode(c->right); 
            yOriginal = b->color;
            a = b->right;

            if (b->parent == c) {
                if (a != nullptr) {
                    a->parent = b;
                }
            } else {
                root = transplantOperation(root, b, b->right); 
                b->right = c->right;
                if (b->right != nullptr) {
                    b->right->parent = b;
                }
            }

            root = transplantOperation(root, c, b);
            b->left = c->left;
            b->left->parent = b;
            b->color = c->color;
        }

        if (yOriginal == RBT::Color::BLACK) {
            fixDeleting(root, a);
        }

        return root;
    }

public:
    RedBlackTree() {
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

    RBT::Node* searchTree(int value) {
        return searchNode(value);
    }

    RBT::Node* successor(RBT::Node* givenNode) {
        return findSuccessor(givenNode);
    }

    RBT::Node* predecessor(RBT::Node* givenNode) {
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

    RBT::Node* getMinimum() {
        return findMinNode(this->root);
    }

    RBT::Node* getMaximum() {
        return findMaxNode(this->root);
    }

    int getTotalNodes() {
        return howManyNode(this->root);
    }
};
