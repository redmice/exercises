//
// Created by Javier G. Visiedo on 10/10/17.
//

#include "graph.h"

void Graph::addNode() {
    std::list<path_cost> newList;
    adjList.push_back(newList);
}
void Graph::addEdge(int from, int to, int weight) {
    path_cost neighbor = {weight, to};
    adjList[from].push_back(neighbor);
}