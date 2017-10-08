//
// Created by Javier Garcia Visiedo on 2017-10-05.
//

#include "BinaryTree.h"


void BinaryTreeNode::insertNode(int n) {

    if (n <= value) { // left
        if (childrenNodes[0] == nullptr){
            childrenNodes[0] = new BinaryTreeNode(n);
        }
        else {
            childrenNodes[0]->insertNode(n);
        }
    }
    if (n > value) { // right
        if (childrenNodes[1] == nullptr){
            childrenNodes[1] = new BinaryTreeNode(n);
        }
        else {
            childrenNodes[1]->insertNode(n);
        }
    }
}

BinaryTreeNode * BinaryTreeNode::getNode (int n){
    if (n == value) {
        return this;
    }
    if (n < value) {
        if (childrenNodes[0] != nullptr) {
            return childrenNodes[0]->getNode (n);
        }
        else {
            return nullptr;
        }
    }
    else {
        if (childrenNodes[1] != nullptr) {
            return childrenNodes[1]->getNode (n);
        }
        else {
            return nullptr;
        }
    }
}

int BinaryTreeNode::getHeight() {
    int heightLeft = 0;
    int heightRight = 0;

    if ((childrenNodes[0] == nullptr) && (childrenNodes[1] == nullptr))
        return 0;


    if (childrenNodes[0] != nullptr)
        heightLeft = 1 + childrenNodes[0]->getHeight();
    if (childrenNodes[1] != nullptr)
        heightLeft = 1 + childrenNodes[1]->getHeight();

    return std::max(heightLeft, heightRight);
}

BinTree* find(BinTree* root, int n){
    if (root == nullptr){
        return nullptr;
    }
    if (n == root->value)
        return root;
    if (n < root->value)
        return find(root->left, n);
    else
        return find(root->right, n);
}