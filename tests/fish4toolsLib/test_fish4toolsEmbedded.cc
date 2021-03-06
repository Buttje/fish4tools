#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include <embedded.hpp>

using namespace fish4tools::embedded;

/**
 * @test Testing the miscellaneous functions of tribble
 */
TEST(Embedded, char2Byte) {
    std::string testInputLowNibble = "000102030405060708090A0B0C0D0E0F0a0b0c0d0e0f";
    std::string testInputHighNibble = "00112233445566778899AABBCCDDEEFFaabbccddeeff";
    std::string testNegative = "0x@3HALLOWELT!...*ÜÄ\n\f%$Vsfsgacxcsdifsfjgfzto8qn pv@ł€@„gbtrhhtrh„ſ„¢łđergsbsbyböfŋħſħſ“»«v byxfvy UHWE~4ZT µ";

    uint8_t goodCompare=0;
    uint8_t result=0;

    for (uint8_t idx=0; idx<testInputLowNibble.length(); idx+=2) {
        EXPECT_TRUE(char2Byte(&(testInputLowNibble[idx]), &result));
        EXPECT_EQ(result, goodCompare);
        if (goodCompare==15) {
            goodCompare=10;
        } else {
            goodCompare++;
        }
    }

    goodCompare=0;
    for (uint8_t idx=0; idx<testInputHighNibble.length(); idx+=2) {
        EXPECT_TRUE(char2Byte(&(testInputHighNibble[idx]), &result));
        EXPECT_EQ(result, (goodCompare<<4)+goodCompare);
        if (goodCompare==15) {
            goodCompare=10;
        } else {
            goodCompare++;
        }
    }

    for (uint8_t idx=0; idx<testNegative.length(); idx+=2) {
        EXPECT_FALSE(char2Byte(&(testNegative[idx]), &result));
        EXPECT_EQ(result, 0);
    }
}