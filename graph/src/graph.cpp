//
// Created by Javier G. Visiedo on 10/4/17.
//

#include "graph.h"

#include <iostream>
#include <vector>
#include <list>

std::list<int> const& Node::getAdjacents() const {
    return adjList;
}

void Node::addAdj(int n) {
    adjList.push_back(n);
}

void Node::visit() {
    visited = true;
}
void Node::clearVisit() {
    visited = false;
}
bool Node::isVisited() const {
    return visited;
}

std::vector<Node> const& Graph::getNodes(){
    return nodeList;
}

Node const& Graph::getNode(int n){
    return nodeList[n];
}

long Graph::addNode() {
    Node node;
    nodeList.push_back(node);
    return nodeList.size() - 1;
}

bool Graph::isEmpty(){
    return !nodeList.size();
}

void DirectedGraph::addEdge (int n1, int n2){
    if ((nodeList.size() > n1) && (nodeList.size() > n2)) {
        nodeList[n1].addAdj(n2);
    }
}
void UndirectedGraph::addEdge (int n1, int n2) {
    nodeList[n1].addAdj(n2);
    nodeList[n2].addAdj(n1);
}

