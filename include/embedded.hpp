
#ifndef FISH4TOOLS_EMBEDDED_H
#define FISH4TOOLS_EMBEDDED_H

#include <string>
#include <inttypes.h>

namespace fish4tools::embedded {

	bool isHex(std::string hexStr);
	bool char2Nibble(char* pin, uint8_t* pout);
	bool char2Byte(char* pin, uint8_t* pout);
}

#endif
