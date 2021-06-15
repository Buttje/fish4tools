#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include <treeNode.hpp>
#include <misc.hpp>

using namespace fish4tools::data;

/**
 * @test Testing the miscellaneous functions of tribble
 */
TEST(Data, TreeNode_left_right_depth) {
    TreeNode<std::string, std::string> *testNode=new TreeNode<std::string, std::string>("", "");

    EXPECT_EQ(testNode->leftDepth(),1);
    EXPECT_EQ(testNode->rightDepth(),1);

    testNode->left=new TreeNode<std::string, std::string>("", "");
    testNode->left->parent=testNode;
    EXPECT_EQ(testNode->leftDepth(),2);
    EXPECT_EQ(testNode->rightDepth(),1);

    testNode->left->left=new TreeNode<std::string, std::string>("", "");
    EXPECT_EQ(testNode->leftDepth(),3);
    EXPECT_EQ(testNode->rightDepth(),1);

    testNode->left->right = new TreeNode<std::string, std::string>("", "");
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),1);
    EXPECT_EQ(testNode->left->leftDepth(), 2);
    EXPECT_EQ(testNode->left->rightDepth(), 2);
    EXPECT_EQ(testNode->left->left->leftDepth(), 1);
    EXPECT_EQ(testNode->left->right->rightDepth(), 1);

    testNode->right = new TreeNode<std::string, std::string>("", "");
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),2);

    testNode->right->left = new TreeNode<std::string, std::string>("", "");
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),3);

    testNode->right->right = new TreeNode<std::string, std::string>("", "");
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),4);
    EXPECT_EQ(testNode->right->leftDepth(), 2);
    EXPECT_EQ(testNode->right->rightDepth(), 2);
    EXPECT_EQ(testNode->right->left->leftDepth(), 1);
    EXPECT_EQ(testNode->right->right->rightDepth(), 1);
}