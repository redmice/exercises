//
// Created by Javier G. Visiedo on 10/7/17.
//

#include "SimpleDirectedGraph.h"
#include <iostream>

void SimpleDirectedGraph::addNode() {
    std::list<int> newList;
    adjList.push_back(newList);
    numNodes++;
}

void SimpleDirectedGraph::addEdge(int from, int to) {
    adjList[from].push_back(to);
}

bool SimpleDirectedGraph::isCycle() {
    std::vector<bool> v = std::vector<bool>(numNodes, false);
    std::list<int> q;
    for (auto n=0; n<numNodes; n++){
        q.push_front(n);
        if (isCycleHelper(n, q, v)) {
            return true;
        }
    }
    return false;
}

bool::SimpleDirectedGraph::isCycleHelper(int n, std::list<int> &queue, std::vector<bool> &visited) {
    visited[n] = true;
    for (auto node : adjList[n]){
        if (find(queue.begin(), queue.end(), node) != queue.end())
            return true;
        if (!visited[node]) {
            queue.push_back(node);
            if (isCycleHelper(node, queue, visited))
                return true;
        }
    }
    queue.pop_back();
    return false;
}

void SimpleDirectedGraph::tSort () {
    std::vector<bool> visited = std::vector<bool>(numNodes);
    std::stack<int> sorted;
    for (auto n=0; n<numNodes; n++){
        if (!visited[n]) {
            tSortHelper(n, visited, sorted);
        }
    }
    while (!sorted.empty()){
        std::cout << sorted.top() << ", ";
        sorted.pop();
    }
    std::cout << "\n";

}

void SimpleDirectedGraph::tSortHelper (int n,
                                       std::vector<bool> & visited,
                                       std::stack<int> & sorted) {
    visited[n] = true;
    for (auto node : adjList[n]) {
        if(!visited[node]){
            tSortHelper (node, visited, sorted);
        }
    }
    sorted.push(n);
}
