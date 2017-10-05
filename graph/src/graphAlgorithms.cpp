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
    BinTree *node = new BinTree;
    node->value = v[midPoint];
    node->left = createMinimalBST_v2(v, min, midPoint-1);
    node->right = createMinimalBST_v2(v, midPoint+1, max);
    return node;
}

int getHeight_v2(BinTree *node) {
    int heightLeft = 0;
    int heightRight = 0;

    if ((node->left == nullptr) && (node->right == nullptr))
        return 0;


    if (node->left != nullptr)
        heightLeft = 1 + getHeight_v2(node->left);
    if (node->right != nullptr)
        heightLeft = 1 + getHeight_v2(node->right);

    return std::max(heightLeft, heightRight);
}

void insertNode_v2(BinTree *node, int n) {

    if (n <= node->value) { // left
        if (node->left == nullptr){
            node->left = new BinTree;
            node->left->value = n;
        }
        else {
            insertNode_v2(node->left, n);
        }
    }
    if (n > node->value) { // right
        if (node->right == nullptr){
            node->right = new BinTree;
            node->right->value = n;
        }
        else {
            insertNode_v2(node->right, n);
        }
    }
}


