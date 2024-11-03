// src/PassengerLogSplayTree.cpp
#include "PassengerLogSplayTree.h"

// Constructor
PassengerLogSplayTree::PassengerLogSplayTree() : root(nullptr) {}

// Destructor
PassengerLogSplayTree::~PassengerLogSplayTree() {
    destroyTree(root);
}

// Destroy the tree to free memory
void PassengerLogSplayTree::destroyTree(PassengerLogSplayTreeNode* node) {
    if (node == nullptr)
        return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// Right rotation
PassengerLogSplayTreeNode* rightRotate(PassengerLogSplayTreeNode* x) {
    PassengerLogSplayTreeNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotation
PassengerLogSplayTreeNode* leftRotate(PassengerLogSplayTreeNode* x) {
    PassengerLogSplayTreeNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation: Move the node with logID to the root
PassengerLogSplayTreeNode* PassengerLogSplayTree::splay(PassengerLogSplayTreeNode* root, int logID) {
    if (root == nullptr || root->data.logID == logID)
        return root;

    // Key lies in left subtree
    if (logID < root->data.logID) {
        if (root->left == nullptr)
            return root;

        // Zig-Zig (Left Left)
        if (logID < root->left->data.logID) {
            root->left->left = splay(root->left->left, logID);
            root = rightRotate(root);
        }
        // Zig-Zag (Left Right)
        else if (logID > root->left->data.logID) {
            root->left->right = splay(root->left->right, logID);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr) ? root : rightRotate(root);
    }
    else { // Key lies in right subtree
        if (root->right == nullptr)
            return root;

        // Zag-Zag (Right Right)
        if (logID > root->right->data.logID) {
            root->right->right = splay(root->right->right, logID);
            root = leftRotate(root);
        }
        // Zag-Zig (Right Left)
        else if (logID < root->right->data.logID) {
            root->right->left = splay(root->right->left, logID);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }

        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

// Insert a new log into the splay tree
PassengerLogSplayTreeNode* PassengerLogSplayTree::insert(PassengerLogSplayTreeNode* root, PassengerLogSplayTreeNode* node) {
    if (root == nullptr)
        return node;

    // Splay the tree with the logID
    root = splay(root, node->data.logID);

    if (node->data.logID < root->data.logID) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
        return node;
    }
    else if (node->data.logID > root->data.logID) {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
        return node;
    }
    else { // Duplicate logID
        // Handle duplicates as per requirements (here we do nothing)
        return root;
    }
}

// Insert log wrapper
void PassengerLogSplayTree::insertLog(const PassengerLog& log) {
    PassengerLogSplayTreeNode* node = new PassengerLogSplayTreeNode(log);
    root = insert(root, node);
}

// Search for a log by logID
PassengerLog* PassengerLogSplayTree::searchLog(int logID) {
    root = splay(root, logID);
    if (root != nullptr && root->data.logID == logID)
        return &(root->data);
    return nullptr;
}

// Delete a log by logID
PassengerLogSplayTreeNode* PassengerLogSplayTree::deleteNode(PassengerLogSplayTreeNode* root, int logID) {
    if (root == nullptr)
        return nullptr;

    root = splay(root, logID);

    if (root->data.logID != logID)
        return root; // Log ID not found

    // If left subtree is null, return right subtree
    if (root->left == nullptr) {
        PassengerLogSplayTreeNode* temp = root->right;
        delete root;
        return temp;
    }
    else {
        // Splay the maximum in left subtree
        PassengerLogSplayTreeNode* temp = splay(root->left, logID);
        // Make right subtree the right child of the new root
        temp->right = root->right;
        delete root;
        return temp;
    }
}

// Delete log wrapper
void PassengerLogSplayTree::deleteLog(int logID) {
    if (searchLog(logID) == nullptr) {
        std::cout << "Passenger log with Log ID " << logID << " not found.\n";
        return;
    }
    root = deleteNode(root, logID);
    std::cout << "Passenger log with Log ID " << logID << " deleted.\n";
}

// In-order traversal to display logs
void PassengerLogSplayTree::inOrderTraversal(PassengerLogSplayTreeNode* node) {
    if (node == nullptr)
        return;
    inOrderTraversal(node->left);
    std::cout << "Log ID: " << node->data.logID
              << " | Passenger ID: " << node->data.passengerID
              << " | Timestamp: " << node->data.timestamp
              << " | Action: " << node->data.actionType
              << " | Driver ID: " << node->data.driverID
              << " | Details: " << node->data.details << "\n";
    inOrderTraversal(node->right);
}

// Display all passenger logs
void PassengerLogSplayTree::displayLogs() {
    if (root == nullptr) {
        std::cout << "No Passenger Logs to display.\n";
        return;
    }
    std::cout << "\n=== All Passenger Logs ===\n";
    inOrderTraversal(root);
}

