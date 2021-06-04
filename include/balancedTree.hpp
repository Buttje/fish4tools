#ifndef FISH4TOOLS_DATA_H
#define FISH4TOOLS_DATA_H

#include <inttypes.h>
#include <string>

using namespace std;

namespace fish4tools::data {

    /**
     * @brief The BalancedTree Class implements a balanced tree of objects
     *        where the 'key' parameter is the attribute to balance on.
     * 
     * The time consuming balancing process is done when objects are added.
     * Retrieving an object from that tree is fast.
     * 
     */
    template<class O>
    class BalancedTree {
        public:
            bool addNode(std::string key, O object) {
                bool success; 
                success=addSymbol(&root, key, O, &success);

                return success;
            }
            O getNode(std::string key) {

            }
            uint16_t getLeftDepth(); /// for the curious lot
            uint16_t getRightDepth(); /// for the curious lot

        private:
            Node<O> root = nullptr; /// Pointer to the root-node of the tree
            bool addNodel(Node<O>** parentPtr, std::string key, O object, bool* ptaller); /// adding a node
            void right_balance(Node<O>** node); ///
            void left_balance(Node<O>** node);  ///
            void rotate_left(Node<O>** node);   ///
            void rotate_right(Node<O>** node);  ///
    };

}

#endif
