//
// Created by Javier G. Visiedo on 10/4/17.
//

#include <queue>
#include <unordered_set>
#include "graph.h"
#include "BinaryTree.h"
#include "SimpleDirectedGraph.h"


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
    BinTree *root = createMinimalBST_v2(v, 0, v.size()-1, nullptr);
    return root;
}

BinTree *createMinimalBST_v2 (std::vector<int> const&v, int min, int max, BinTree *parent){
    if (max < min) {
        return nullptr;
    }
    int midPoint = (min + max) / 2;
    BinTree *node = new BinTree(v[midPoint]);
    node->parent = parent;
    node->left = createMinimalBST_v2(v, min, midPoint-1, node);
    node->right = createMinimalBST_v2(v, midPoint+1, max, node);
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

BinTree * successor(BinTree *node) {
    if (node == nullptr)
        return nullptr
                ;
    if (node->right) {           //I have something to the right => left-most leave on the right branch
        BinTree *runner = node->right;
        while (runner->left) {
            runner = runner->left;
        }
        return runner;
    }

    BinTree *runner = node;      // I am the right child => way up until I am on a left branch, or nothing
    while ((runner->parent) && (runner->parent->right == runner)) {
        runner = runner->parent;
    }
    return runner->parent;
}


BinTree * search(BinTree *root, int n) {
    if (!root || (root->value == n)){
        return root;
    }
    if (root->value >= n) {
        return search(root->left, n);
    }
    return search(root->right, n);
}

/*
 * 4.7 Build Order: You are given a list of projects and a list of dependencies (which is a list of pairs of
 * projects, where the second project is dependent on the first project). All of a project's dependencies
 * must be built before the project is. Find a build order that will allow the projects to be built. If there
 * is no valid build order, return an error.
 *
 * EXAMPLE
 * Input:
 * projects: a, b, c, d, e, f
 * dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
 * Output: f, e, a, b, d, c
 */

void buildOrder (std::list<int> projects, std::list<std::pair<int, int>> dependencies) {
    SimpleDirectedGraph graph = buildGraph(projects, dependencies);
    if (graph.isCycle()){
        std::cout << "Error: cyclic dependencies \n";
    }
    else {
        graph.tSort();
    }
}

SimpleDirectedGraph buildGraph (std::list<int> projects, std::list<std::pair<int, int>> dependencies) {
    SimpleDirectedGraph graph = SimpleDirectedGraph(projects.size());
    for (auto dep : dependencies){
        graph.addEdge(dep.first, dep.second);
    }
    return graph;
}

/*
 * 4.8 First Common Ancestor: Design an algorithm and write code to find the first common ancestor
 * of two nodes in a binary tree. Avoid storing additional nodes in a data structure. NOTE: This is not
 * necessarily a binary search tree.
 *
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as
 * the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
 *
 *       _______3______
 *      /              \
 *   ___5__          ___1__
 *  /      \        /      \
 *  6      _2       0       8
 *        /  \
 *        7   4
 *
 * For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5,
 * since a node can be a descendant of itself according to the LCA definition.
 *
 */

bool check(BinTree* node, std::unordered_set<BinTree *> &visited) {
    if (!node)
        return false;
    if (visited.find(node) != visited.end())
        return true;
    visited.insert(node);
    return false;
}

// With links to parents. Time complexity O(D) where D is depth of tree. Space complexity O(D) due to hash table
BinTree* lca(BinTree *root, BinTree *v1, BinTree *v2) {
    std::unordered_set<BinTree *> visited;

    if ((v1 == nullptr) || (v2 == nullptr))
        return nullptr;
    if ((v1 == root) || (v2 == root))
        return root;
    if (v1 == v2) {
        return v1;
    }
    while ((v1 != nullptr) || (v2 != nullptr)) {
        if (check(v1, visited))
            return (v1);
        if (check(v2, visited))
            return (v2);
        v1 = v1->parent;
        v2 = v2->parent;
    }
    return nullptr;
}

int getDepth(BinTree* node) {
    int depth = 0;
    while (node != nullptr) {
        node = node->parent;
        depth++;
    }
    return depth;
}

BinTree* moveUpBy(BinTree *node, int n) {
    while ((n > 0) && (node != nullptr)) {
        node = node->parent;
        n--;
    }
    return node;
}

// With links to parents. Time complexity O(D) where D is depth of tree. Space complexity O(1): no additional data struct
BinTree* lca_v2(BinTree *root, BinTree *v1, BinTree *v2) {
    int delta = getDepth(v1) - getDepth(v2);
    BinTree *first = (delta >= 0) ? v2 : v1;
    BinTree *second = (delta >= 0) ? v1 : v2;
    second = moveUpBy(second, abs(delta));

    while ((first) && (second) && (first != second)) {
        first = first->parent;
        second = second->parent;
    }

    return (!first || !second) ? nullptr : first;
}

// With no link to parents.
BinTree* lca_noParent(BinTree* root, BinTree* v1, BinTree* v2) {
    // 1. check if v1 and v2 fall under the same branch. Otherwise I found the common ancestor

    BinTree *lca = root;
    while ( (((v1->value <= lca->value) && (v2->value <= lca->value)) ||
             ((v1->value > lca->value) && (v2->value > lca->value))) &&   //While on the same branch
           (lca)){
        lca = v1->value <= lca->value ? lca->left : lca->right;
    }
    return lca;
}

/*
 * BST Sequences: A binary search tree was created by traversing through an array from left to right and inserting each
 * element. Given a binary search tree with distinct elements, print all possible arrays that could have led to this
 * tree.
 * EXAMPLE Input:
 *       __2__
 *      /     \
 *     1       3
 *
 * Output: {2, 1, 3}, {2, 3, 1}
 */

std::vector<std::list<int>> sequences(BinTree *root) {
    std::vector<std::list<int>> seqsLeft;
    std::vector<std::list<int>> seqsRight;
    std::vector<std::list<int>> result;
    std::list<int> prefix;

    if (root == nullptr){
        std::list<int> empty = {};
        result.push_back(empty);
        return result;
    }

    seqsLeft = sequences(root->left);
    seqsRight = sequences(root->right);
    prefix.push_back(root->value);
    for (auto left : seqsLeft){
        for (auto right : seqsRight){
            weave(left, right, result, prefix);
        }
    }
    return result;
}

void weave(std::list<int> list1,
           std::list<int> list2,
           std::vector<std::list<int>> &results,
           std::list<int> prefix){

    if ((list1.size() == 0) || (list2.size() == 0)) {
        std::list<int> result = prefix;
        result.insert(result.end(), list1.begin(), list1.end());
        result.insert(result.end(), list2.begin(), list2.end());
        results.push_back(result);
        return;
    }

    int head1 = list1.front();
    list1.pop_front();
    prefix.push_back(head1);
    weave (list1, list2, results, prefix);
    list1.push_front(head1);
    prefix.pop_back();

    int head2 = list2.front();
    list1.pop_front();
    prefix.push_back(head2);
    weave (list1, list2, results, prefix);
    list1.push_front(head2);
    prefix.pop_back();
}
