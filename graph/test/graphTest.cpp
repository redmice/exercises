//
// Created by Javier G. Visiedo on 10/4/17.
//

#include <iostream>
#include "gtest/gtest.h"
#include "../src/graph.h"

bool isConnected (DirectedGraph g, int n1, int n2);

class GraphTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        //Init g1 with 6 unnconected vertex:
        // num. vertex = 6
        // num edges = 0
        for (auto i=0; i<6; i++){
            ug.addNode();
            dg.addNode();
        }
        ug.addEdge(0, 1);
        ug.addEdge(0, 2);
        ug.addEdge(1, 2);
        ug.addEdge(1, 3);
        ug.addEdge(1, 4);
        ug.addEdge(4, 5);

        dg.addEdge(0, 1);
        dg.addEdge(0, 2);
        dg.addEdge(1, 2);
        dg.addEdge(1, 3);
        dg.addEdge(1, 4);
        dg.addEdge(4, 5);

    }

    // virtual void TearDown() {}

    UndirectedGraph ug = UndirectedGraph(6);
    DirectedGraph dg = DirectedGraph(6);
    DirectedGraph emptyGraph;
};

TEST_F(GraphTest, NodesInDirectedGraphAreConnected) {
    EXPECT_TRUE(isConnected(dg, 0, 3));
    EXPECT_FALSE(isConnected(dg, 5, 1));
}

TEST_F(GraphTest, UninitializedGraphIsNotEmpty) {
    DirectedGraph reservedGraph = DirectedGraph(6);
    EXPECT_TRUE(reservedGraph.isEmpty());
}

TEST_F(GraphTest, SpaceReservationStillEmpty) {
    DirectedGraph emptyGraph;
    EXPECT_TRUE(emptyGraph.isEmpty());
}

TEST_F(GraphTest, InitializedGraphIsNotEmpty) {
    EXPECT_FALSE(ug.isEmpty());
}

TEST_F(GraphTest, NumEdgesUndirectedGraphIsCorrect){
    size_t ugSize = ug.getNode(1).getAdjacents().size();
    EXPECT_EQ(ugSize, 4);
}

TEST_F(GraphTest, NumEdgesDirectedGraphIsCorrect){
    size_t ugSize = dg.getNode(1).getAdjacents().size();
    EXPECT_EQ(ugSize, 3);
}