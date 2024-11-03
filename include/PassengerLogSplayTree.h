// include/PassengerLogSplayTree.h
#ifndef PASSENGERLOGSPLAYTREE_H
#define PASSENGERLOGSPLAYTREE_H

#include "PassengerLog.h"
#include <iostream>

// Structure for the nodes of the splay tree
struct PassengerLogSplayTreeNode {
    PassengerLog data;
    PassengerLogSplayTreeNode* left;
    PassengerLogSplayTreeNode* right;

    PassengerLogSplayTreeNode(const PassengerLog& log)
        : data(log), left(nullptr), right(nullptr) {}
};

class PassengerLogSplayTree {
private:
    PassengerLogSplayTreeNode* root;

    // Utility functions
    PassengerLogSplayTreeNode* splay(PassengerLogSplayTreeNode* root, int logID);
    PassengerLogSplayTreeNode* insert(PassengerLogSplayTreeNode* root, PassengerLogSplayTreeNode* node);
    PassengerLogSplayTreeNode* deleteNode(PassengerLogSplayTreeNode* root, int logID);
    void inOrderTraversal(PassengerLogSplayTreeNode* node);
    void destroyTree(PassengerLogSplayTreeNode* node);

public:
    PassengerLogSplayTree();
    ~PassengerLogSplayTree();

    void insertLog(const PassengerLog& log);
    PassengerLog* searchLog(int logID);
    void deleteLog(int logID);
    void displayLogs();
};

#endif // PASSENGERLOGSPLAYTREE_H

