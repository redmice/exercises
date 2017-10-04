//
// Created by Javier G. Visiedo on 10/4/17.
//

#include "weightedGraph.h"

#include <iostream>
#include <vector>
#include <list>

std::list<edge> const& WNode::getAdjacents() const {
    return adjList;
}

void WNode::addAdj(edge e) {
    adjList.push_back(e);
}

std::vector<WNode> const& WGraph::getNodes(){
    return nodeList;
}

WNode const& WGraph::getNode(int n){
    return nodeList[n];
}

long WGraph::addNode() {
    WNode node;
    nodeList.push_back(node);
    return nodeList.size() - 1;
}

void WDirectedGraph::addEdge (int n1, int n2, int w){
    if ((nodeList.size() > n1) && (nodeList.size() > n2)) {
        nodeList[n1].addAdj({n2, w});
    }
}
void WUndirectedGraph::addEdge (int n1, int n2, int w) {
    nodeList[n1].addAdj({n2, w});
    nodeList[n2].addAdj({n2, w});
}
