//
// Created by Javier G. Visiedo on 10/10/17.
//

#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H


#include <list>
#include <vector>

typedef std::pair<int, int> path_cost;  // <weight, toNode>

struct edge {
    int from;
    int to;
    int weight;

    edge(int f, int t, int w): from(f), to(t), weight(w){};
};

/*
 * Class Graph: Implements a simple directed weighted graph
 *
 * Assumes the graph nodes can be indexed on consequtive ints, starting on 0.
 * Nodes do not have any lables, and are referenced just by the auto-increase index
 */
class Graph {
private:
    std::vector<std::list<path_cost>> adjList;
    int numNodes;
public:
    Graph(int n) : adjList(n), numNodes(n) {}
    void addNode();
    void addEdge(int from, int to, int weight);
    std::list<path_cost> getAdjacents (int n) const { return adjList[n]; }
    int countNodes() const { return numNodes; } ;
    int getCost (int from, int to) {
        std::list<path_cost>::iterator it = find_if(adjList[from].begin(), adjList[from].end(),
                                                    [to](const path_cost &element){
                                                        return (element.second==to);
                                                    });

        if (it != adjList[from].end()) {
            return it->first;
        }
        else
            return -1;
    }
};


#endif //DIJKSTRA_GRAPH_H
