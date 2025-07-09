#include <iostream>
using namespace std;

// Node colors
enum Color { RED, BLACK };

// Node structure
struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int val) {
        data = val;
        color = RED; // New node is always red
        left = right = parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*& root, Node*& x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node*& root, Node*& x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node*& root, Node*& x) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (x != root && x->color == RED && x->parent->color == RED) {
            parent = x->parent;
            grandparent = parent->parent;

            // Parent is left child of grandparent
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                // Case 1: Uncle is red
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    x = grandparent;
                } else {
                    // Case 2: x is right child
                    if (x == parent->right) {
                        rotateLeft(root, parent);
                        x = parent;
                        parent = x->parent;
                    }

                    // Case 3: x is left child
                    rotateRight(root, grandparent);
                    swap(parent->color, grandparent->color);
                    x = parent;
                }
            }
            // Parent is right child of grandparent
            else {
                Node* uncle = grandparent->left;

                if (unccle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    x = grandparent;
                } else {
                    if (x == parent->left) {
                        rotateRight(root, parent);
                        x = parent;
                        parent = x->parent;
                    }

                    rotateLeft(root, grandparent);
                    swap(parent->color, grandparent->color);
                    x = parent;
                }
            }
        }

        root->color = BLACK; // Root always black
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insert(int val) {
        Node* newNode = new Node(val);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (val < x->data)
                x = x->left;
            else if (val > x->data)
                x = x->right;
            else {
                cout << "Duplicate value not allowed: " << val << endl;
                return;
            }
        }

        newNode->parent = y;

        if (y == nullptr)
            root = newNode;
        else if (val < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        fixInsert(root, newNode);
    }

    void inorderTraversal() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }
};

// Main to test
int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);

    tree.inorderTraversal(); // Sorted output

    return 0;
}
