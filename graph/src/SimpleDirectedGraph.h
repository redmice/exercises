//
// Created by Javier G. Visiedo on 10/7/17.
//

#ifndef GRAPH_SIMPLEDIRECTEDGRAPH_H
#define GRAPH_SIMPLEDIRECTEDGRAPH_H


#include <list>
#include <vector>
#include <queue>
#include <stack>

class SimpleDirectedGraph {
private:
    std::vector<std::list<int>> adjList;
    int numNodes;

    bool isCycleHelper(int n, std::list<int> &queue, std::vector<bool> &visited);
    void tSortHelper (int n, std::vector<bool> & visited, std::stack<int> & sorted);

public:
    SimpleDirectedGraph(int n) : adjList(n), numNodes(n) {}

    void addNode();
    void addEdge(int from, int to);

    bool isCycle();
    void tSort();

};

SimpleDirectedGraph buildGraph(std::list<int>, std::list<std::pair<int, int>>);
void buildOrder (std::list<int> projects, std::list<std::pair<int, int>> dependencies);

#endif //GRAPH_SIMPLEDIRECTEDGRAPH_H
