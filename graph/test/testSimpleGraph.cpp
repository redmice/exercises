//
// Created by Javier G. Visiedo on 10/7/17.
//

#include "gtest/gtest.h"
#include "../src/SimpleDirectedGraph.h"

class SimpleGraphTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        cycleGraph.addEdge(0,1);
        cycleGraph.addEdge(0,2);
        cycleGraph.addEdge(1,2);
        cycleGraph.addEdge(2,0);
        cycleGraph.addEdge(3, 3);

        noCycleGraph.addEdge(0,1);
        noCycleGraph.addEdge(0,2);
        noCycleGraph.addEdge(2,3);
        noCycleGraph.addEdge(3,1);

    }
    SimpleDirectedGraph cycleGraph = SimpleDirectedGraph(4);
    SimpleDirectedGraph noCycleGraph = SimpleDirectedGraph(4);
};

TEST_F (SimpleGraphTest, cycleGraphIsCyclic){
    EXPECT_TRUE(cycleGraph.isCycle());
}

TEST_F (SimpleGraphTest, nonCycleGraphIsNotCyclic){
    EXPECT_FALSE(noCycleGraph.isCycle());
}

TEST_F (SimpleGraphTest, dependenciesAreSolved) {
    /*
     * projects: 0, 1, 2, 3, 4, 5
     * dependencies: (0, 3), (5, 1), (1, 3), (5, 0), (3, 2)
     * Output: 5, 4, 0, 1, 3, 2
     */
    std::list<int> projects = {0, 1, 2, 3, 4, 5};
    std::list<std::pair<int,int>> dependencies = { {0, 3}, {5, 1}, {1, 3}, {5, 0}, {3, 2} };
    testing::internal::CaptureStdout();
    buildOrder(projects, dependencies);
    std::string output = testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(output.c_str(), "5, 4, 1, 0, 3, 2, \n");
}

TEST_F (SimpleGraphTest, dependenciesAreSolved2) {
    /*
     * projects: 0, 1, 2, 3, 4, 5, 6
     * dependencies: (5, 1), (5, 0), (5, 2), (1, 0), (2, 0), (2, 4), (3, 6), (0, 4)
     * Output: 5, 4, 0, 1, 3, 2
     */
    std::list<int> projects = {0, 1, 2, 3, 4, 5, 6};
    std::list<std::pair<int,int>> dependencies = { {5, 1}, {5, 0}, {5, 2}, {1, 0}, {2, 0}, {2, 4}, {3, 6}, {0, 4} };
    testing::internal::CaptureStdout();
    buildOrder(projects, dependencies);
    std::string output = testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(output.c_str(), "5, 3, 6, 2, 1, 0, 4, \n");
}

TEST_F (SimpleGraphTest, cyclicDependenciesCannotBeSolved) {
    /*
     * projects: 0, 1, 2, 3, 4, 5, 6
     * dependencies: (5, 1), (5, 0), (5, 2), (1, 0), (2, 0), (2, 4), (3, 6), (0, 4), (4, 5)
     * Output: 5, 4, 0, 1, 3, 2
     */
    std::list<int> projects = {0, 1, 2, 3, 4, 5, 6};
    std::list<std::pair<int,int>> dependencies = { {5, 1}, {5, 0}, {5, 2}, {1, 0}, {2, 0}, {2, 4}, {3, 6}, {0, 4}, {4, 5}};
    testing::internal::CaptureStdout();
    buildOrder(projects, dependencies);
    std::string output = testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(output.c_str(), "Error: cyclic dependencies \n");
}

