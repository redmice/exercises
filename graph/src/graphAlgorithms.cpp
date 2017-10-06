//
// Created by Javier G. Visiedo on 10/4/17.
//

#include <queue>
#include "graph.h"
#include "BinaryTree.h"


// 4.1 Route Between Nodes: Given a directed graph, design an algorithm to find out whether there is a route between
// two nodes.

bool isConnected (DirectedGraph g, int n1, int n2) { // Using BSF to get the route quicker

    std::queue<int> nodeQueue;

    nodeQueue.push(n1);
    while (!nodeQueue.empty()) {
        int index = nodeQueue.front();
        if (index == n2) {
            return true;
        }
        nodeQueue.pop();
        Node node = g.getNode(index);
        node.visit();
        for (auto adjacent : node.getAdjacents()){
            if (!g.getNode(adjacent).isVisited()) {
                nodeQueue.push(adjacent);
            }
        }
    }
    return false;
}

// 4.2 Minimal Tree: Given a sorted (increasing order) array with unique integer elements, write an algorithm to create
// a binary search tree with minimal height

    // Version 1: Using BinaryTree class

BinaryTreeNode *createMinimalBST (std::vector<int> const&v){
    BinaryTreeNode *root = createMinimalBST(v, 0, v.size()-1);
    return root;
}

BinaryTreeNode *createMinimalBST (std::vector<int> const&v, int min, int max){
    if (max < min) {
        return nullptr;
    }
    int midPoint = (min + max) / 2;
    BinaryTreeNode *node = new BinaryTreeNode(v[midPoint]);
    node->left(createMinimalBST(v, min, midPoint-1));
    node->right(createMinimalBST(v, midPoint+1, max));
    return node;
}

    // Version 2: Using a simple tree structure: maybe more adequate for interviews, where the focus is on solving the
    // exercise at hand, rather than build a full fledge data structure class.


BinTree *createMinimalBST_v2 (std::vector<int> const&v){
    BinTree *root = createMinimalBST_v2(v, 0, v.size()-1);
    return root;
}

BinTree *createMinimalBST_v2 (std::vector<int> const&v, int min, int max){
    if (max < min) {
        return nullptr;
    }
    int midPoint = (min + max) / 2;
    BinTree *node = new BinTree(v[midPoint]);
    node->left = createMinimalBST_v2(v, min, midPoint-1);
    node->right = createMinimalBST_v2(v, midPoint+1, max);
    return node;
}

int getHeight_v2(BinTree *node) {
    if (node == nullptr){
        return -1;
    }
    return std::max(getHeight_v2(node->left), getHeight_v2(node->right)) + 1;
}

void insertNode_v2(BinTree *node, int n) {

    if (n <= node->value) { // left
        if (node->left == nullptr){
            node->left = new BinTree(n);
        }
        else {
            insertNode_v2(node->left, n);
        }
    }
    if (n > node->value) { // right
        if (node->right == nullptr){
            node->right = new BinTree(n);
        }
        else {
            insertNode_v2(node->right, n);
        }
    }
}

// 4.3 List of Depths: Given a binary tree, design an algorithm which creates a linked list of all the nodes at each depth
// (e.g., if you have a tree with depth D, you'll have Dlinked lists).

std::vector<std::list<int>> depths (BinTree *root){
    std::vector<std::list<int>> lists;
    fillDepths (lists, root, 0);
    return lists;
}

void fillDepths (std::vector<std::list<int>> &lists, BinTree *node, int level) {
    if (node == nullptr) {
        return;
    }
    if (lists.size() == level) { //level not included
        std::list<int> newList;
        lists.push_back(newList);
    }
    lists[level].push_back(node->value);
    fillDepths (lists, node->left, level+1);
    fillDepths (lists, node->right, level+1);
}

// 4.4 Check Balanced: Implement a function to check if a binary tree is balanced. For the purposes of this question,
// a balanced tree is defined to be a tree such that the heights of the two subtrees of any node never differ by more
// than one.

bool isBalanced(BinTree *root){
    if (root == nullptr) return true;

    int heightDiff = std::abs(getHeight_v2(root->left) - getHeight_v2(root->right));
    if (heightDiff > 1) {
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}

// 4.5 Validate 8ST: Implement a function to check ifa binary tree is a binary search tree.

bool checkBST(BinTree *node, BinTree *minNode, BinTree *maxNode){
    if (node == nullptr) {
        return true;
    }
    if ((minNode && (node->value <= minNode->value)) || (maxNode && (node->value > maxNode->value))) {
        return false;
    }
    return checkBST(node->left, minNode, node) && checkBST(node->right, node, maxNode);
}

bool isBST(BinTree *root) {
    return checkBST(root, nullptr, nullptr);
}


// 4.6 Successor: Write an algorithm to find the "next" node (i.e., in-order successor) of a given node in a binary
// search tree. You may assume that each node has a link to its parent.