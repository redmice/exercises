//
// Created by Javier G. Visiedo on 10/4/17.
//

#include <queue>
#include "graph.h"


// True if there is a path between 2 nodes in the graph

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


