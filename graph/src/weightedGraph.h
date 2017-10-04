//
// Created by Javier G. Visiedo on 10/4/17.
//

#ifndef GRAPH_WEIGHTEDGRAPH_H
#define GRAPH_WEIGHTEDGRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include "graph.h"

struct edge {
    int dst;
    int weight;
};

class WNode : public Node {
private:
    std::list<edge> adjList;
    bool visited;
public:
    WNode() : visited(false) {}
    std::list<edge> const& getAdjacents() const;
    void addAdj(edge e);
};


class WGraph : public Graph {
protected:
    std::vector<WNode> nodeList;
public:
    WGraph () {}
    WGraph(long n) {
        nodeList.reserve(n);
    }

    std::vector<WNode> const& getNodes();
    WNode const& getNode(int n);
    long addNode();
};

class WDirectedGraph : public WGraph {
public:
    WDirectedGraph(){}
    WDirectedGraph(long n) : WGraph(n){}
    void addEdge (int n1, int n2, int w);
};

class WUndirectedGraph : public WGraph {
public:
    WUndirectedGraph(){}
    WUndirectedGraph(long n) : WGraph(n){}
    void addEdge (int n1, int n2, int w);
};

#endif //GRAPH_WEIGHTEDGRAPH_H
