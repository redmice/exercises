
#include <iostream>
#include <queue>
#include <climits>
#include <stack>
#include "graph.h"

void initGraph (Graph & graph, const std::vector<edge>& edges){
    for (auto edge : edges){
        graph.addEdge(edge.from, edge.to, edge.weight);
    }
}

// Shortest path between two nodes in a graph
std::stack<path_cost> dijkstra (const Graph & g, int from, int to){
    int size = g.countNodes();
    std::stack<path_cost> path; // Holding result
    std::priority_queue<path_cost, std::vector<path_cost>, std::greater<path_cost>> queue; // Weight must be pair.first
    std::vector<bool> visited = std::vector<bool>(size, false);
    std::vector<int> distance(size, INT_MAX);
    std::vector<int> prev(size, -1);

    distance[from] = 0;
    queue.push({0, from}); // Origin has a 0 cost
    prev[from] = 0;
    while ( !queue.empty() ) {
        path_cost currentPath = queue.top();
        int currentNode = currentPath.second;
        int weight = currentPath.first;
        queue.pop();
        if (currentNode == to){
            break;
        }
        if (!visited[currentNode]) {
            //get adjacents
            std::list<path_cost> adj = g.getAdjacents(currentPath.second);
            for (auto edge : adj) {
                int currentDistance = distance[currentNode] + edge.first;
                if (currentDistance < distance[edge.second]) {
                    distance[edge.second] = currentDistance;
                    prev[edge.second] = currentNode;
                }
                queue.push({distance[edge.second], edge.second});  //Queue node (second) with the accumulated cost
            }
            visited[currentNode] = true;
        }
    }
    //Build the path on a stack
    int id = to;
    while (prev[id] != -1){
        path.push({distance[id], id});
        if (id == from)
            break;
        id = prev[id];
    }
    return path;
}

int main(){

    // Initialization
    Graph g = Graph(9);
    std::vector<edge> edges = { {0, 1, 4}, {0, 7, 8},
                                {1, 7, 11}, {1, 2, 8},
                                {2, 3, 7}, {2, 8, 2}, {2, 5, 4},
                                {3, 4, 9}, {3, 5, 14},
                                {4, 5, 10},
                                {5, 6, 2},
                                {6, 8, 6},
                                {7, 6, 1}, {7, 8, 7}};
    initGraph (g, edges);

    std::stack<path_cost> result = dijkstra(g, 0, 8);
    int totalDistance = 0;
    while (!result.empty()){
        std::cout << result.top().second << " -> ";
        totalDistance = result.top().first;
        result.pop();
    }
    std::cout << std::endl << "Total distance: " << totalDistance << std::endl;

    return 0;
}