#ifndef FISH4TOOLS_MISC_H
#define FISH4TOOLS_MISC_H

#include <type_traits>

using namespace std;

/**
 * @brief Just introducing Java's 'instanceOf' syntax in C++.
 *        Because I like it and because I can. :-)
 * 
 * @tparam Base 
 * @tparam T 
 * @return true 
 * @return false 
 */
template<typename Base, typename T>
    inline bool instanceof(const T*) {
        
        return std::is_base_of<Base, T>::value;
    }


#endif
