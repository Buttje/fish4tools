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
            bool insert(K key, O* object) {
                
                if (root==nullptr) {
                    root=new TreeNode<K, O>(key, *object);
                    return true; //success
                }
                return insert(root, key, object);
            }

            O* get(K key) {
                TreeNode<K,O>* actualNode = root;
                O* foundObject = nullptr;

                while (actualNode && !foundObject) {
                    if (actualNode->getKey()==key) {
                        foundObject = actualNode->getObject();
                        if (actualNode->getKey()>key) {
                            actualNode=actualNode->getLeft();
                        } else {
                            actualNode=actualNode->getRight();;
                        }
                    }
                }
            return foundObject;
            }

            uint16_t getLeftDepth() {  /// for the curious lot
                if (!root) return 0;
                return root->leftDepth();
            }; 

            uint16_t getRightDepth() { /// for the curious lot
                if (!root) return 0;
                return root->rightDepth();
            }; 

        private:
            enum tBalance {LEFT, EVEN, RIGHT};
            TreeNode<K, O>* root = nullptr; /// Pointer to the root-node of the tree

            bool insert(TreeNode<K, O>* root, K key, O* object) {  /// adding a node
                bool success = false;
                
                if (key == root->getKey()) return false; // key exists

                if (key < root->getKey()) {
                    success = handleLeft(root, key, object);
                } else {
                    success = handleRight(root, key, object);
                }
                return success;
            }; 


            bool handleLeft(TreeNode<K, O>* parent, K key, O* object) {  /// adding a node to the left
                bool success = false;
               
                if (parent->getLeft()==nullptr) {
                    parent->setLeft(new TreeNode<K,O>(key, *object));
                    success = true;
                } else {
                    success=insert(parent->getLeft(), key, object);
                }

                if ((parent->leftDepth()-parent->rightDepth())>1) {
                    balanceLeft(parent);
                    parent->leftDepth();
                    parent->rightDepth();
                }

                return success;
            }; 


            void balanceLeft(TreeNode<K,O>* node) {
                TreeNode<K,O>* oldLeft=node->getLeft();
                TreeNode<K,O>* newTopNode=oldLeft;
                TreeNode<K,O>* connectPoint=nullptr;
                bool oldPosOnTop=true;
                //find the largest node in the left 'smaller' tree
                while(newTopNode->getRight()) {
                    newTopNode=newTopNode->getRight();
                    oldPosOnTop=false;
                }
                
                if (!oldPosOnTop) {
                    newTopNode->getParent()->setRight(nullptr, false);
                } else {
                    oldLeft->setRight(nullptr, false);
                }
                if (node->getParent()==nullptr) {
                    root=newTopNode;
                    newTopNode->setParent(nullptr);
                } else {
                    newTopNode->getParent()->setRight(nullptr,false);
                    node->getParent()->setLeft(newTopNode, true);
                }
                newTopNode->setRight(node, true);
                node->setLeft(nullptr, false);
                
                if (!oldPosOnTop) {
                    connectPoint=newTopNode->getLeft();
                    if (connectPoint) {
                        while(connectPoint->getLeft()) {
                            connectPoint=connectPoint->getLeft();
                        }
                        connectPoint->setLeft(oldLeft);
                    } else {
                        newTopNode->setLeft(oldLeft);
                    }
                }

                if (!oldPosOnTop) {
                    balanceLeft(oldLeft);
                }
            };

            bool handleRight(TreeNode<K, O>* parent, K key, O* object) {  /// adding a node to the left
                bool success = false;
              
                if (parent->getRight()==nullptr) {
                    parent->setRight(new TreeNode<K,O>(key, *object));
                    success = true;
                } else {
                    success=insert(parent->getRight(), key, object);
                }

                if ((parent->rightDepth()-parent->leftDepth())>1) {
                    balanceRight(parent);
                }
            
                return success;
            }; 

            void balanceRight(TreeNode<K,O>* node) {
                TreeNode<K,O>* oldRight=node->getRight();
                TreeNode<K,O>* smallestNode=oldRight;
                TreeNode<K,O>* connectPoint=nullptr;
                bool smallestOnTop=true;
                //find the largest node in the left 'smaller' tree
                while(smallestNode->getLeft()) {
                    smallestNode=smallestNode->getLeft();
                    smallestOnTop=false;
                }
                
                if (!smallestOnTop) {
                    smallestNode->getParent()->setLeft(nullptr, false);
                } else {
                    oldRight->setLeft(nullptr, false);
                }
                if (node->getParent()==nullptr) {
                    root=smallestNode;
                    smallestNode->setParent(nullptr);
                } else {
                    smallestNode->getParent()->setLeft(nullptr,false);
                    node->getParent()->setLeft(smallestNode, true);
                }
                smallestNode->setLeft(node, true);
                node->setRight(nullptr, false);
                
                if (!smallestOnTop) {
                    connectPoint=smallestNode->getRight();
                    if (connectPoint) {
                        while(connectPoint->getRight()) {
                            connectPoint=connectPoint->getRight();
                        }
                        connectPoint->setRight(oldRight);
                    } else {
                        smallestNode->setRight(oldRight);
                    }
                }
            };

            
    };
}


#endif
