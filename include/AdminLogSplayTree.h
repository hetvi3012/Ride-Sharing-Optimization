// include/AdminLogSplayTree.h
#ifndef ADMINLOGSPLAYTREE_H
#define ADMINLOGSPLAYTREE_H

#include "AdminLog.h"
#include <iostream>

// Structure for the nodes of the splay tree
struct AdminLogSplayTreeNode {
    AdminLog data;
    AdminLogSplayTreeNode* left;
    AdminLogSplayTreeNode* right;

    AdminLogSplayTreeNode(const AdminLog& log)
        : data(log), left(nullptr), right(nullptr) {}
};

class AdminLogSplayTree {
private:
    AdminLogSplayTreeNode* root;

    // Utility functions
    AdminLogSplayTreeNode* splay(AdminLogSplayTreeNode* root, int logID);
    AdminLogSplayTreeNode* insert(AdminLogSplayTreeNode* root, AdminLogSplayTreeNode* node);
    AdminLogSplayTreeNode* deleteNode(AdminLogSplayTreeNode* root, int logID);
    void inOrderTraversal(AdminLogSplayTreeNode* node);
    void destroyTree(AdminLogSplayTreeNode* node);

public:
    AdminLogSplayTree();
    ~AdminLogSplayTree();

    void insertLog(const AdminLog& log);
    AdminLog* searchLog(int logID);
    void deleteLog(int logID);
    void displayLogs();
};

#endif // ADMINLOGSPLAYTREE_H

