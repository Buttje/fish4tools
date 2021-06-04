#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include <treeNode.hpp>
#include <misc.hpp>

using namespace fish4tools::data;

/**
 * @test Testing the miscellaneous functions of tribble
 */
TEST(Data, Node_left_right_depth) {
    TreeNode<std::string, std::string> *testNode=new TreeNode<std::string, std::string>("", "");

    EXPECT_EQ(testNode->leftDepth(),1);
    EXPECT_EQ(testNode->rightDepth(),1);

    testNode->setLeft(new TreeNode<std::string, std::string>("", ""));
    EXPECT_EQ(testNode->leftDepth(),2);
    EXPECT_EQ(testNode->rightDepth(),1);

    testNode->getLeft()->setLeft(new TreeNode<std::string, std::string>("", ""));
    EXPECT_EQ(testNode->leftDepth(),3);
    EXPECT_EQ(testNode->rightDepth(),1);

    testNode->getLeft()->setRight(new TreeNode<std::string, std::string>("", ""));
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),1);
    EXPECT_EQ(testNode->getLeft()->leftDepth(), 2);
    EXPECT_EQ(testNode->getLeft()->rightDepth(), 2);
    EXPECT_EQ(testNode->getLeft()->getLeft()->leftDepth(), 1);
    EXPECT_EQ(testNode->getLeft()->getRight()->rightDepth(), 1);

    testNode->setRight(new TreeNode<std::string, std::string>("", ""));
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),2);

    testNode->getRight()->setLeft(new TreeNode<std::string, std::string>("", ""));
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),3);

    testNode->getRight()->setRight(new TreeNode<std::string, std::string>("", ""));
    EXPECT_EQ(testNode->leftDepth(),4);
    EXPECT_EQ(testNode->rightDepth(),4);
    EXPECT_EQ(testNode->getRight()->leftDepth(), 2);
    EXPECT_EQ(testNode->getRight()->rightDepth(), 2);
    EXPECT_EQ(testNode->getRight()->getLeft()->leftDepth(), 1);
    EXPECT_EQ(testNode->getRight()->getRight()->rightDepth(), 1);
}