#ifndef FISH4TOOLS_TREENODE_H
#define FISH4TOOLS_TREENODE_H

#include <inttypes.h>
#include <string>

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

            void setLeft(TreeNode<K, O>* treeNode) {
                left=treeNode;
                treeNode->setParent(this);
            }

            void setRight(TreeNode<K, O>* treeNode) {
                right=treeNode;
                treeNode->setParent(this);
            }

            TreeNode<K,O>* getParent() {
                return parent;
            }

            TreeNode<K,O>* getLeft() {
                return left;
            }

            TreeNode<K,O>* getRight() {
                return right;
            }

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
            int8_t getBalance() {  /// Used by the symbolTree to manage the balancing
                uint16_t ld = leftDepth();
                    uint16_t rd = rightDepth();
                    _balance=0;

                    if (abs(ld-rd)>2) {
                        if (ld>rd) {
                            _balance=-1;
                        } else {
                            _balance=1;
                        }
                    }
                    return(_balance);
            } 

            void setBalance(int8_t balance) {
                 _balance=balance;
            } /// Used by the symbolTree to manage the balancing

        private:
            int8_t _balance=0;
            K key; /// The sorting key as String, since all members of the @ref Symbol class are Strings
            O* object = nullptr; /// The object
            TreeNode* left = nullptr; /// Left branch
            TreeNode* right = nullptr; /// Right branch
            TreeNode* parent = nullptr; /// Right branch
            void setParent(TreeNode<K, O>* treeNode) {
                parent=treeNode;
            }
    };
}

#endif
