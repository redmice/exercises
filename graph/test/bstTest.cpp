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
        sample = createMinimalBST_v2(input);
        notSearch = new BinTree(10);
        BinTree *runner = notSearch;
        for (auto i=0; i<20; i++){
            runner->left = new BinTree(i);
            runner = runner->left;
        }
        terriblyWrongBST = new BinTree(10);
        terriblyWrongBST->left = new BinTree(5);
        terriblyWrongBST->left->left = new BinTree(3);
        terriblyWrongBST->left->right = new BinTree(20);
    }

    BinTree *sample;
    BinTree *notSearch;
    BinTree *terriblyWrongBST;
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

TEST_F(bstTest, minimalBST_v2) {
    BinTree *root;
    root = createMinimalBST_v2(input);
    EXPECT_EQ(3, getHeight_v2(root));
}

TEST_F(bstTest, buildingInOrderGivesHugeheight_v2) {
    BinTree *root = new BinTree(input[0]);
    for (auto i=1; i < input.size(); i++) {
        insertNode_v2(root, input[i]);
    }
    EXPECT_EQ(8, getHeight_v2(root));
}

TEST_F(bstTest, depthListHasThreeLists) {
    std::vector<std::list<int>> lists;
    lists = depths (sample);

    EXPECT_EQ(4, lists.size());
}

TEST_F(bstTest, heightOfEmptyTreeMinus1) {
    BinTree *root = nullptr;
    EXPECT_EQ(-1, getHeight_v2(root));
}

TEST_F(bstTest, minimalBSTShouldBeBallanced) {
    BinTree *root;
    root = createMinimalBST_v2(input);
    EXPECT_TRUE(isBalanced(root));
}

TEST_F(bstTest, aTerriblyBallancedTreeReturnsFalse) {
    BinTree *root = new BinTree(input[0]);
    for (auto i=1; i < input.size(); i++) {
        insertNode_v2(root, input[i]);
    }
    EXPECT_FALSE(isBalanced(root));
}

TEST_F (bstTest, anEmptyTreeIsNotBallanced) {
    BinTree *root = nullptr;
    EXPECT_TRUE(isBalanced(root));
}

TEST_F (bstTest, OneNodeOnlyShouldBeBalanced) {
    BinTree *root = new BinTree(0);
    EXPECT_TRUE(isBalanced(root));
}

TEST_F (bstTest, binaryTreeReturnsTrue) {
    EXPECT_TRUE(isBST(sample));
}

TEST_F (bstTest, bstTest_NonBinaryTreeReturnsFalse_Test) {
    EXPECT_FALSE(isBST(notSearch));
}

TEST_F (bstTest, bstTest_terriblyWrongBST_Test) {
    EXPECT_FALSE(isBST(terriblyWrongBST));
}

TEST_F (bstTest, bstTest_rootNodeNeverHasParent_Test){
    EXPECT_EQ(nullptr, sample->parent);
}

TEST_F(bstTest, nextToNineIsTen) {
    EXPECT_EQ(10, successor(search(sample, 9))->value);
}

TEST_F(bstTest, nextToRightMostLeaveIsNull) {
    EXPECT_EQ(nullptr, successor(search(sample, 123)));
}

TEST_F(bstTest, nextToRootIs67) {
    EXPECT_EQ(45, successor(search(sample, 10))->value);
}

TEST_F(bstTest, nextToRootEmptyTreeIsEmpty) {
    BinTree *empty = nullptr;
    EXPECT_EQ(nullptr, successor(empty));
}

TEST_F(bstTest, bstTest_singleNodeTreeDoesNotHaveNext_Test) {
    BinTree *single = new BinTree(1);
    EXPECT_EQ(nullptr, successor(single));
}

TEST_F(bstTest, bstTest_weCanFindOurAncestors_Test) {
    BinTree *v1 = find (sample, 123);
    BinTree *v2 = find (sample, 9);

    EXPECT_EQ(10, lca(sample, v1, v2)->value);
}

TEST_F(bstTest, bstTest_weANodeIsItsOwnAncestor_Test) {
    BinTree *v1 = find (sample, 3);
    BinTree *v2 = find (sample, 9);

    EXPECT_EQ(3, lca(sample, v1, v2)->value);
}

TEST_F(bstTest, bstTest_weCanFindOurAncestors_v2_Test) {
    BinTree *v1 = find (sample, 123);
    BinTree *v2 = find (sample, 9);

    EXPECT_EQ(10, lca_v2(sample, v1, v2)->value);
}

TEST_F(bstTest, bstTest_weANodeIsItsOwnAncestor_v2_Test) {
    BinTree *v1 = find (sample, 3);
    BinTree *v2 = find (sample, 9);

    EXPECT_EQ(3, lca_v2(sample, v1, v2)->value);
}

TEST_F(bstTest, bstTest_weCanFindOurAncestors_noParent_Test) {
    BinTree *v1 = find (sample, 123);
    BinTree *v2 = find (sample, 9);

    EXPECT_EQ(10, lca_noParent(sample, v1, v2)->value);
}

TEST_F(bstTest, bstTest_weANodeIsItsOwnAncestor_noParent_Test) {
    BinTree *v1 = find (sample, 3);
    BinTree *v2 = find (sample, 9);

    EXPECT_EQ(3, lca_noParent(sample, v1, v2)->value);
}


