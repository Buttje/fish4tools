#ifndef FISH4TOOLS_TREENODE_H
#define FISH4TOOLS_TREENODE_H

#include <inttypes.h>
#include <string>
#include <vector>

using namespace std;

namespace fish4tools::data {

/**
     * @brief This class is a node for the balanced tree
     *        specifically designed for the @ref Symbol
     */
    template<class K, class O>
    class TreeNode {
        public:
            TreeNode(K key, O object) {
                this->key=key;
                this->object=&object;
            }

            K key; /// The sorting key 
            O* object = nullptr; /// The object
            TreeNode* left = nullptr; /// Left branch
            TreeNode* right = nullptr; /// Right branch
            TreeNode* parent = nullptr; /// Right branch

            uint16_t leftDepth() {  /// Returns the dpeth of the left branch
                uint16_t rightDepth;
                uint16_t leftDepth;

                if (left) {
                    rightDepth=left->rightDepth();
                    leftDepth=left->leftDepth();
                    return rightDepth + leftDepth;
                } else {
                    return 1;
                }
            } 

            uint16_t rightDepth() {  /// Returns the dpeth of the right branch
                uint16_t rightDepth;
                uint16_t leftDepth;

                if (right) {
                    rightDepth=right->rightDepth();
                    leftDepth=right->leftDepth();
                    return rightDepth + leftDepth;
                } else {
                    return 1;
                }
            } 

        private:
    };
}

#endif
