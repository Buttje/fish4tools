#ifndef FISH4TOOLS_DATA_H
#define FISH4TOOLS_DATA_H

#include <inttypes.h>
#include <string>
#include <treeNode.hpp>

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
    template<class K, class O>
    class BalancedTree {
        public:

            BalancedTree(uint16_t capacity) {
                maxCapacity=capacity;
                if (maxCapacity>0) {
                   container=(TreeNode<K, O>*)malloc(maxCapacity*sizeof(TreeNode<K, O>));
                   memset(container, 0, maxCapacity*sizeof(TreeNode<K, O>));
                }
            }

            bool insert(K key, O* object) {
                
                if (maxCapacity<1) return false;
                if (actCapacity>=maxCapacity) return false;

                if (root==nullptr) {
                    root=container;
                    root[0].key = key;
                    root[0].object = object;
                    actCapacity++;
                    return true; //success
                }
                return insertAndBalance(root, key, object);
            }

            O* get(K key) {
                TreeNode<K,O>* actualNode = root;
                O* foundObject = nullptr;

                if (actCapacity==0) return nullptr;

                while (actualNode && !foundObject) {
                    if (actualNode->key==key) {
                        foundObject = actualNode->object;
                        if (actualNode->key > key) {
                            actualNode=actualNode->left;
                        } else {
                            actualNode=actualNode->left;;
                        }
                    }
                }
            return foundObject;
            }

            uint16_t getLeftDepth() {  /// for the curious lot
                if (actCapacity==0) return 0;
                return root->leftDepth();
            }; 

            uint16_t getRightDepth() { /// for the curious lot
                if (actCapacity==0) return 0;
                return root->rightDepth();
            }; 

        private:
            TreeNode<K, O>* root = nullptr; /// Pointer to the root-node of the tree
            TreeNode<K, O>* container = nullptr; /// Pointer to the pre-allocated container
            uint16_t maxCapacity=0;
            uint16_t actCapacity=0;


            bool insertAndBalance(TreeNode<K, O>* parent, K key, O* object) {
                bool success=true;

                if (parent->key==key) {
                    return false;
                }

                if (parent->key > key) {
                    if (parent->left == nullptr) {
                        container[actCapacity].key=key;
                        container[actCapacity].object=object;
                        container[actCapacity].parent=parent;
                        parent->left=&(container[actCapacity]);
                        actCapacity++;
                    } else {
                        success = insertAndBalance(parent->left, key, object);
                    }
                } else {
                    if (parent->right == nullptr) {
                        container[actCapacity].key=key;
                        container[actCapacity].object=object;
                        container[actCapacity].parent=parent;
                        parent->right=&(container[actCapacity]);
                        actCapacity++;
                    } else {
                        success = insertAndBalance(parent->right, key, object);
                    }
                }
                if (!success) {
                    return false;
                }

                balance(parent);

                return success;
            };

            void balance(TreeNode<K,O>* topNode) {
                int32_t balance;

                if (!topNode) {
                    return;
                }

                balance=topNode->leftDepth() - topNode->rightDepth();
                if (balance > 1) {
                   topNode = reTopFromLeft(topNode);
                } else if (balance < -1) {
                   topNode = reTopFromRight(topNode);
                }

                this->balance(topNode->left);
                this->balance(topNode->right);
            };

            TreeNode<K,O>* reTopFromLeft(TreeNode<K,O>* oldTopNode) {
                TreeNode<K,O>* oldLeftNode = oldTopNode->left;
                TreeNode<K,O>* newTopNode = oldLeftNode;
                TreeNode<K,O>* newTopLeftOvers = nullptr;
                bool oldLeftIsNewTop = false;

                if (!oldLeftNode) return oldTopNode;

                while(newTopNode->right) {
                    newTopNode=newTopNode->right;
                }
                oldLeftIsNewTop=(oldLeftNode==newTopNode);
                if (!oldLeftIsNewTop) {
                    newTopLeftOvers=newTopNode->left;
                    if (newTopLeftOvers) {
                         while(newTopLeftOvers->left) {
                             newTopLeftOvers=newTopLeftOvers->left;
                         }
                    }
                }
                if(oldLeftIsNewTop) {
                    newTopNode->parent->left = nullptr;
                } else {
                    newTopNode->parent->right = nullptr;
                }
                if(oldTopNode->parent==nullptr) {
                    root=newTopNode;
                    newTopNode->parent = nullptr;
                } else {
                     newTopNode->parent=oldTopNode->parent;
                    if (oldTopNode->parent->left==oldTopNode) {
                        oldTopNode->parent->left = newTopNode;
                    } else {
                        oldTopNode->parent->right = newTopNode;
                    }
                }
                newTopNode->right = oldTopNode;
                newTopNode->right->parent = newTopNode;
                oldTopNode->left = nullptr;
                if (!oldLeftIsNewTop) {
                    if (newTopLeftOvers) {
                        newTopLeftOvers->left = oldLeftNode;
                        newTopLeftOvers->left->parent = newTopLeftOvers;
                    } else {
                        newTopNode->left = oldLeftNode;
                        newTopNode->left->parent=newTopNode;
                    }
                }
                return newTopNode;
            }

            TreeNode<K,O>* reTopFromRight(TreeNode<K,O>* oldTopNode) {
                TreeNode<K,O>* oldRightNode = oldTopNode->right;
                TreeNode<K,O>* newTopNode = oldRightNode;
                TreeNode<K,O>* newTopLeftOvers = nullptr;
                bool oldRightIsNewTop = false;

                if (!oldRightNode) return oldTopNode;

                while(newTopNode->left) {
                    newTopNode=newTopNode->left;
                }
                oldRightIsNewTop=(oldRightNode==newTopNode);
                if (!oldRightIsNewTop) {
                    newTopLeftOvers=newTopNode->right;
                    if (newTopLeftOvers) {
                         while(newTopLeftOvers->right) {
                             newTopLeftOvers=newTopLeftOvers->right;
                         }
                    }
                }
                if(oldRightIsNewTop) {
                    newTopNode->parent->right=nullptr;
                } else {
                    newTopNode->parent->left=nullptr;
                }
                if(oldTopNode->parent==nullptr) {
                    root=newTopNode;
                    newTopNode->parent = nullptr;
                } else {
                    newTopNode->parent=oldTopNode->parent;
                    if (oldTopNode->parent->left==oldTopNode) {
                        oldTopNode->parent->left=newTopNode;
                    } else {
                        oldTopNode->parent->right=newTopNode;
                    }
                }
                newTopNode->left=oldTopNode;
                newTopNode->left->parent=newTopNode;
                oldTopNode->right=nullptr;
                if (!oldRightIsNewTop) {
                    if (newTopLeftOvers) {
                        oldRightNode->parent=newTopLeftOvers;
                        newTopLeftOvers->right=oldRightNode;
                    } else {
                        oldRightNode->parent=newTopNode;
                        newTopNode->right=oldRightNode;
                    }
                }
                return newTopNode;
            }


    };
}


#endif
