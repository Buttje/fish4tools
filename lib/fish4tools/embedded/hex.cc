#include <embedded.hpp>
#include <inttypes.h>
#include <string>
#include <cctype>

namespace fish4tools::embedded {

/**
 * @brief isHex checks, if the given string contains a valid hexadecimal value
 * 
 * @param hexStr the hexadecimal string 
 * @return true the string contains a valid hexadecimal value
 * @return false the string does not contain a valid hexadecimal value
 */
inline bool isHex(const std::string& hexStr) {
    const std::size_t len = hexStr.size();

    // Length must be even
    if ((len & 1u) != 0u) {
        return false;
    }

    // Keep original bounds: (len > 2) && (len < 130), otherwise return false
    if (len <= 2u || len >= 130u) {
        return false;
    }

    // Original code starts checking from index 2 and ignores the first two chars
    // It also used isalnum(), not isxdigit(), so we preserve that.
    for (std::size_t idx = 2u; idx < len; ++idx) {
        unsigned char ch = static_cast<unsigned char>(hexStr[idx]);
        if (!std::isalnum(ch)) {
            return false;     // early exit instead of computing through whole string
        }
    }
    return true;
}

/**
 * @brief Converts a hexadecimal character into the decimal value.
 * 
 * @param pin pointer to a character of [(0-9)|(a-f)|(A-F)]
 * @param pout the decimal value is written into this variable
 * @return true the conversion was successful
 * @return false the provided in-character was invalid
 */
inline bool char2Nibble(char* pin, uint8_t* pout) {
    if (!pin || !pout) {
        return false;
    }

    unsigned char c = static_cast<unsigned char>(*pin);

    // Most common case first: numbers
    if (c >= '0' && c <= '9') {
        *pout = static_cast<uint8_t>(c - '0');
        return true;
    }
    // lowercase a-f
    if (c >= 'a' && c <= 'f') {
        *pout = static_cast<uint8_t>(c - 'a' + 10);
        return true;
    }
    // uppercase A-F
    if (c >= 'A' && c <= 'F') {
        *pout = static_cast<uint8_t>(c - 'A' + 10);
        return true;
    }

    return false;
}

/**
 * @brief Converts the next two hexadecimal 
 *          characters into the corresponding byte value
 * 
 * @param pin pointer to the first character
 * @param pout points to the output value
 * @return true the conversion was successful
 * @return false the conversion was not successful
 */
inline bool char2Byte(char* pin, uint8_t* pout) {
    if (!pin || !pout) {
        return false;
    }

    uint8_t highNibble = 0;
    uint8_t lowNibble  = 0;

    if (!char2Nibble(pin, &highNibble) ||
        !char2Nibble(pin + 1, &lowNibble)) {
        *pout = 0;
        return false;
    }

    *pout = static_cast<uint8_t>((highNibble << 4) | lowNibble);
    return true;
}

}
