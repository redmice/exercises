//
// Created by Javier Garcia Visiedo on 2017-10-05.
//

#include <iostream>
#include <vector>
#include "../src/BinaryTree.h"
#include "gtest/gtest.h"

class bstTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        //Initializations
    }

    BinaryTreeNode root;
    std::vector<int> input = {1, 3, 8, 9, 10, 45, 67, 98, 123};
};

TEST_F(bstTest, emptyBinaryTreeHasZeroHeight){
    EXPECT_EQ(0, root.getHeight());
}

TEST_F(bstTest, minimalBST) {
    BinaryTreeNode *root;
    root = createMinimalBST(input);
    EXPECT_EQ(3, root->getHeight());
}

TEST_F(bstTest, buildingInOrderGivesHugeheight) {
    BinaryTreeNode *root = new BinaryTreeNode(input[0]);
    for (auto i=1; i < input.size(); i++) {
        root->insertNode(input[i]);
    }
    EXPECT_EQ(8, root->getHeight());
}

TEST_F(bstTest, buildingInOrderGivesHugeheight_v2) {
    BinTree *root = new BinTree;
    root->value = input[0];
    for (auto i=1; i < input.size(); i++) {
        insertNode_v2(root, input[i]);
    }
    EXPECT_EQ(8, getHeight_v2(root));
}