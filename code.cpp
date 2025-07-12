#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val): data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root = nullptr;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left) return root->right;
            else if (!root->right) return root->left;

            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void update(Node* &root, int oldVal, int newVal) {
        root = deleteNode(root, oldVal);
        root = insert(root, newVal);
    }
};

int main() {
    BST tree;
    tree.root = tree.insert(tree.root, 50);
    tree.insert(tree.root, 30);
    tree.insert(tree.root, 70);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 40);

    cout << "Inorder: ";
    tree.inorder(tree.root);
    cout << endl;

    tree.root = tree.deleteNode(tree.root, 30);
    cout << "After deletion: ";
    tree.inorder(tree.root);
    cout << endl;

    tree.update(tree.root, 20, 25);
    cout << "After update: ";
    tree.inorder(tree.root);
    cout << endl;

    return 0;
}