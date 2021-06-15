#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <misc.hpp>
#include <balancedTree.hpp>

using namespace fish4tools::data;

/**
 * @test Testing the miscellaneous functions of tribble
 */
TEST(Data, BalancedTree_insert_String_leftroll) {
    BalancedTree<std::string, std::string>* bTree=new BalancedTree<std::string, std::string>(10) ;

    EXPECT_EQ(bTree->getLeftDepth(), 0);
    EXPECT_EQ(bTree->getRightDepth(), 0);

    EXPECT_EQ(bTree->get("Hallo Welt!"), nullptr);

    EXPECT_TRUE(bTree->insert("8", new std::string("OBJ9")));
    EXPECT_EQ(bTree->getLeftDepth(), 1);
    EXPECT_EQ(bTree->getRightDepth(), 1);

    EXPECT_TRUE(bTree->insert("6", new std::string("OBJ5")));
    EXPECT_EQ(bTree->getLeftDepth(), 2);
    EXPECT_EQ(bTree->getRightDepth(), 1);

    EXPECT_TRUE(bTree->insert("3", new std::string("OBJ3")));
    EXPECT_EQ(bTree->getLeftDepth(), 2);
    EXPECT_EQ(bTree->getRightDepth(), 2);

    EXPECT_TRUE(bTree->insert("4", new std::string("OBJ4")));
    EXPECT_EQ(bTree->getLeftDepth(), 3);
    EXPECT_EQ(bTree->getRightDepth(), 2);

    EXPECT_TRUE(bTree->insert("2", new std::string("OBJ4")));
    EXPECT_EQ(bTree->getLeftDepth(), 3);
    EXPECT_EQ(bTree->getRightDepth(), 3);

    EXPECT_TRUE(bTree->insert("9", new std::string("OBJ4")));
    EXPECT_EQ(bTree->getLeftDepth(), 3);
    EXPECT_EQ(bTree->getRightDepth(), 4);

}

TEST(Data, BalancedTree_insert_String_rightroll) {
    BalancedTree<std::string, std::string>* bTree=new BalancedTree<std::string, std::string>(50) ;

    EXPECT_EQ(bTree->getLeftDepth(), 0);
    EXPECT_EQ(bTree->getRightDepth(), 0);

    EXPECT_EQ(bTree->get("Hallo Welt!"), nullptr);

    EXPECT_TRUE(bTree->insert("09", new std::string("OBJ9")));
    EXPECT_EQ(bTree->getLeftDepth(), 1);
    EXPECT_EQ(bTree->getRightDepth(), 1);

    EXPECT_TRUE(bTree->insert("16", new std::string("OBJ16")));
    EXPECT_EQ(bTree->getLeftDepth(), 1);
    EXPECT_EQ(bTree->getRightDepth(), 2);

    EXPECT_TRUE(bTree->insert("19", new std::string("OBJ19")));
    EXPECT_EQ(bTree->getLeftDepth(), 2);
    EXPECT_EQ(bTree->getRightDepth(), 2);

    EXPECT_TRUE(bTree->insert("18", new std::string("OBJ18")));
    EXPECT_EQ(bTree->getLeftDepth(), 2);
    EXPECT_EQ(bTree->getRightDepth(), 3);

    EXPECT_TRUE(bTree->insert("20", new std::string("OBJ20")));
    EXPECT_EQ(bTree->getLeftDepth(), 3);
    EXPECT_EQ(bTree->getRightDepth(), 3);

    EXPECT_TRUE(bTree->insert("08", new std::string("OBJ09")));
    EXPECT_EQ(bTree->getLeftDepth(), 4);
    EXPECT_EQ(bTree->getRightDepth(), 3);

    EXPECT_TRUE(bTree->insert("01", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 4);
    EXPECT_EQ(bTree->getRightDepth(), 4);

    EXPECT_TRUE(bTree->insert("03", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 5);
    EXPECT_EQ(bTree->getRightDepth(), 4);

    EXPECT_TRUE(bTree->insert("02", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 5);
    EXPECT_EQ(bTree->getRightDepth(), 5);

    EXPECT_TRUE(bTree->insert("30", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 5);
    EXPECT_EQ(bTree->getRightDepth(), 6);

    EXPECT_TRUE(bTree->insert("40", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 6);
    EXPECT_EQ(bTree->getRightDepth(), 6);

    EXPECT_TRUE(bTree->insert("35", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 6);
    EXPECT_EQ(bTree->getRightDepth(), 7);

    EXPECT_TRUE(bTree->insert("38", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 7);
    EXPECT_EQ(bTree->getRightDepth(), 7);

    EXPECT_TRUE(bTree->insert("32", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 7);
    EXPECT_EQ(bTree->getRightDepth(), 8);

    EXPECT_TRUE(bTree->insert("31", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 8);
    EXPECT_EQ(bTree->getRightDepth(), 8);

    EXPECT_TRUE(bTree->insert("37", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 8);
    EXPECT_EQ(bTree->getRightDepth(), 9);

    EXPECT_TRUE(bTree->insert("36", new std::string("OBJ01")));
    EXPECT_EQ(bTree->getLeftDepth(), 9);
    EXPECT_EQ(bTree->getRightDepth(), 9);
}

TEST(Data, BalancedTree_insert_int_random) {

    uint32_t num_tests=1000;
    BalancedTree<uint16_t, std::string>* bTree=new BalancedTree<uint16_t, std::string>(num_tests);
    uint16_t lDepth=0;
    uint16_t rDepth=0;
    int32_t diff=0;
    std:string sample="Lorem Ipsum dolor sit amet";
    uint16_t randKey=0;

    srand (time(NULL));

    for (uint32_t i=0; i<num_tests; i++) {
        randKey=(uint16_t)rand();
        bTree->insert(randKey, &sample);
    }

    lDepth=bTree->getLeftDepth();
    rDepth=bTree->getRightDepth();
    diff=lDepth-rDepth;
    diff=abs(diff);
    EXPECT_LT(diff, 2);
}