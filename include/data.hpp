#ifndef FISH4TOOLS_DATA_H
#define FISH4TOOLS_DATA_H

#include <inttypes.h>
#include <string>

using namespace std;

namespace fish4tools::data {

/**
     * @brief This class is a node for the balanced tree
     *        specifically designed for the @ref Symbol
     */
    class Node {
        public:
            std::string key; /// The sorting key as String, since all members of the @ref Symbol class are Strings
            void* object = nullptr; /// The @ref Symbol object
            Node* left = nullptr; /// Left branch
            Node* right = nullptr; /// Right branch

            uint16_t leftDepth(); /// Returns the dpeth of the left branch
            uint16_t rightDepth(); /// Returns the dpeth of the right branch
            int8_t getBalance(); /// Used by the symbolTree to manage the balancing
            void setBalance(int8_t balance); /// Used by the symbolTree to manage the balancing

        private:
            int8_t _balance=0;
    };
    
    /**
     * @brief The BalancedTree Class implements a balanced tree for objects of the @ref Node class
     * 
     */
    class BalancedTree {
        public:
            bool addNode(std::string key, Node *node);
            Node* getNode(std::string key);
            uint16_t getLeftDepth(); /// for the curious lot
            uint16_t getRightDepth(); /// for the curious lot

        private:
            Node *root = nullptr; /// Pointer to the root-node of the tree
            bool addNodel(Node** parentPtr, std::string key, void* object, bool* ptaller); /// adding a node
            void right_balance(Node** node); ///
            void left_balance(Node** node);  ///
            void rotate_left(Node** node);   ///
            void rotate_right(Node** node);  ///
    };

}

#endif
