//
// Created by Javier Garcia Visiedo on 2017-10-05.
//

#ifndef GRAPH_BINARYTREE_H
#define GRAPH_BINARYTREE_H


#include <vector>
#include <list>

class BinaryTreeNode {
private:
    std::vector<BinaryTreeNode *> childrenNodes;
    int value;

public:
    BinaryTreeNode() : childrenNodes(2, nullptr), value(0) {}
    BinaryTreeNode(int n) : childrenNodes(2, nullptr), value(n) {}

    ~BinaryTreeNode() {
        if (childrenNodes[0] != nullptr){
            delete childrenNodes[0];
        }
        if (childrenNodes[1] != nullptr){
            delete childrenNodes[1];
        }
    }

    void insertNode (int n);
    void deleteNode (int n);
    BinaryTreeNode * getNode (int n);
    int getValue () { return value; }
    int getHeight();
    BinaryTreeNode * getLeft () { return childrenNodes[0]; }
    BinaryTreeNode * getright () { return childrenNodes[1]; }
    void left (BinaryTreeNode *n) { childrenNodes[0] = n; }
    void right (BinaryTreeNode *n) { childrenNodes[1] = n; }

};

// Simpler version, maybe better for interview???

struct BinTree {
    BinTree *left = nullptr;
    BinTree *right = nullptr;
    BinTree *parent = nullptr;
    int value;
    BinTree(int x) : value(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

BinTree* find(BinTree* root, int n);

// Function declaration for the exercises in the algorithms file
BinaryTreeNode *createMinimalBST (std::vector<int> const&v);
BinaryTreeNode *createMinimalBST (std::vector<int> const&v, int min, int max);
BinTree *createMinimalBST_v2 (std::vector<int> const&v);
BinTree *createMinimalBST_v2 (std::vector<int> const&v, int min, int max, BinTree *);
int getHeight_v2(BinTree *node);
void insertNode_v2(BinTree *node, int n);

std::vector<std::list<int>> depths (BinTree *root);
void fillDepths (std::vector<std::list<int>> &lists, BinTree *node, int level);

BinTree* lca(BinTree *root, BinTree *v1, BinTree *v2);
BinTree* lca_v2(BinTree *root, BinTree *v1, BinTree *v2);
BinTree* lca_noParent(BinTree* root, BinTree* v1, BinTree* v2);

std::vector<std::list<int>> sequences(BinTree *root);
void weave(std::list<int> list1,
                                  std::list<int> list2,
                                  std::vector<std::list<int>> &results,
                                  std::list<int> prefix);

bool isBalanced(BinTree *root);

bool isBST(BinTree *root);

BinTree * search(BinTree *root, int n);
BinTree * successor(BinTree *node);

#endif //GRAPH_BINARYTREE_H
