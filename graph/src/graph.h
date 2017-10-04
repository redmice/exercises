//
// Created by Javier G. Visiedo on 10/4/17.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <iostream>
#include <vector>
#include <list>

class Node {
protected:
    std::list<int> adjList;
    bool visited;
public:
    Node() : visited(false) {}
    std::list<int> const& getAdjacents() const;
    void addAdj(int n);
    void visit();
    void clearVisit();
    bool isVisited() const;
};


class Graph {
protected:
    std::vector<Node> nodeList;
public:
    Graph () {}
    Graph(long n) {
        nodeList.reserve(n);
    }

    std::vector<Node> const& getNodes();
    Node const& getNode(int n);
    long addNode();
    bool isEmpty();
};

class DirectedGraph : public Graph {
public:
    DirectedGraph(){}
    DirectedGraph(long n) : Graph(n){}
    void addEdge (int n1, int n2);
};

class UndirectedGraph : public Graph {
public:
    UndirectedGraph(){}
    UndirectedGraph(long n) : Graph(n){}
    void addEdge (int n1, int n2);
};


#endif //GRAPH_GRAPH_H
