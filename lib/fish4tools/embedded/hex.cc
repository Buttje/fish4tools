#include <embedded.hpp>
#include <inttypes.h>
#include <string>
#include <cctype>

namespace fish4tools::embedded {

/**
 * @brief isHex checks, if the given string containd a valid hexadecimal value
 * 
 * @param hexStr the hexadecimal string 
 * @return true the string contains a valid hexadecimal value
 * @return false the string does not contain a valid hexadecimal value
 */
bool isHex(std::string hexStr) {
    bool test = false;
    uint8_t testOffset=0;

    if ((hexStr.length() % 2) == 1) {
        return test;
    }

    if((hexStr.length()>2) && (hexStr.length()<130)) {
        if (((hexStr[0]=='0') && (hexStr[1]=='x')) ||(hexStr[1]=='X')) {
            testOffset=2;
        }
        test=true;
        for (uint16_t idx=2; idx<hexStr.length(); idx++) {
            test = (test & isalnum(hexStr[idx]));
        }
    }
    return test;
}

/**
 * @brief Converts a hexadecimal character into the decimal value.
 * 
 * @param in a character of [(0-9)|(a-f)|(A-F)]
 * @param out the decimal value is written into this variable
 * @return true the conversion was successful
 * @return false the provided in-character was invalid
 */
bool char2Nibble(char* pin, uint8_t* pout) {
    if (pin && pout) {
        if ((*pin>='a') && (*pin<='f')) {
            // lowercase a-f
            *pout=(uint8_t)((*pin)-'a'+10);
            return true;
        }
        if ((*pin>='A') && (*pin<='F')) {
            // uppercase A-F
            *pout=(uint8_t)((*pin)-'A'+10);
            return true;
        }
        if ((*pin>='0') && (*pin<='9')) {
            // numbers
            *pout=(uint8_t)((*pin)-'0');
            return true;
        }
    }
    return false;
}

/**
 * @brief Converts the next two hexadecimal 
 *          characters into the corresponding byte value
 * 
 * @param pin pointer to the first charater
 * @param pout points to the output value
 * @return true the conversion was successful
 * @return false the conversion was not successful
 */
bool char2Byte(char* pin, uint8_t* pout) {
    bool success = true;
    uint8_t highNibble=0;
    uint8_t lowNibble=0;
    *pout=0;

    success = char2Nibble(pin, &highNibble);
    if (success) {
        success&=char2Nibble(&(pin[1]), &lowNibble);
        if (success) {
            *pout=(highNibble<<4)|lowNibble;
        }
    }

    return success;
}

}
