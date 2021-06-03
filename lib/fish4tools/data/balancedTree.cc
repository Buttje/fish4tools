#include <inttypes.h>
#include <data.hpp>

using namespace fish4tools::data;

/**
 * @brief Adding a symbol object to the tree
 * 
 * @param key The key used to store the object
 * @param symbol The pointer to the symbol object to store
 * @return true The symbol has been added
 * @return false The given key already exists, the symbol has not been added.
 */
bool BalancedTree::addNode(std::string key, Symbol *symbol) {
    bool success; 
    success=addSymbol(&root, key, symbol, &success);

    return success;
}

/**
 * @brief Retrieving a symbol from the tree by its key-value
 * 
 * @param key the key used to store 
 * @return Symbol* 
 */
Symbol* SymbolTree::getSymbol(std::string key) {
    SymbolTreeNode* actualNode = root;
    Symbol* foundSymbol = nullptr;

    while (actualNode && !foundSymbol) {
        if (actualNode->key==key) {
            foundSymbol=actualNode->symbol;
        } else {
            if (actualNode->key>key) {
                actualNode=actualNode->left;
            } else {
                actualNode=actualNode->right;
            }
        }
    }
    return foundSymbol;
}

uint16_t SymbolTree::getLeftDepth() {
    return root->leftDepth();
}

uint16_t SymbolTree::getRightDepth() {
    return root->rightDepth();
}

bool SymbolTree::addSymbol(SymbolTreeNode** parentPtr, std::string key, Symbol *symbol, bool* ptaller)
    {
        bool result = true;
        SymbolTreeNode* newNode = nullptr;
        SymbolTreeNode* parentNode = nullptr;

        if(!(*parentPtr)){
            (*parentPtr)=new SymbolTreeNode();
            (*parentPtr)->key=key;
            (*parentPtr)->symbol=symbol;
            *ptaller = true;
        } else if(key == (*parentPtr)->key){
                result = false;
                *ptaller = false;
        } else if(key < (*parentPtr)->key) {
            result = addSymbol(&(*parentPtr)->left, key, symbol, ptaller);
            if(*ptaller)
                switch((*parentPtr)->getBalance()){
                    case -1:
                        left_balance(parentPtr);
                        *ptaller = false;
                        break;
                    case 0:
                        (*parentPtr)->setBalance(-1);
                        break;
                    case 1:
                        (*parentPtr)->setBalance(0);
                        *ptaller = false;
                        break;
                }
        }
        else{
            result = addSymbol(&(*parentPtr)->right, key, symbol, ptaller);
            if(*ptaller)
               switch((*parentPtr)->getBalance()){
                    case -1:
                        (*parentPtr)->setBalance(0);
                        *ptaller = false;
                        break;
                    case 0:
                        (*parentPtr)->setBalance(1);
                        break;
                    case 1:
                        right_balance(parentPtr);
                        *ptaller = false;
                        break;
                }
    }
        return result;
    }

void SymbolTree::right_balance(SymbolTreeNode** node)
{
    SymbolTreeNode** right_tree = &(*node)->right;
    right_tree=node;
    switch((*right_tree)->getBalance()){
        case 1:
            (*node)->setBalance(0);
            (*right_tree)->setBalance(0);
            rotate_left(node); 
            break;
        case 0:
            printf("WARNING: program error in right_balance"); break;
        case -1:
            SymbolTreeNode* subTree = (*right_tree)->left;
            switch(subTree->getBalance()){
                case 0:
                    (*node)->setBalance(0);
                    (*right_tree)->setBalance(0);break;
                case -1:
                    (*node)->setBalance(0);
                    (*right_tree)->setBalance(1); break;
                case 1:
                    (*node)->setBalance(-1);
                    (*right_tree)->setBalance(0);break;
            }
            subTree->setBalance(0);
            rotate_right(right_tree);
            rotate_left(node); break;
        }
}

void SymbolTree::left_balance(SymbolTreeNode** node)
{
    SymbolTreeNode** left_tree = &(*node)->left;
    left_tree=node;
    switch((*left_tree)->getBalance()){
        case -1:
            (*node)->setBalance(0);
            (*left_tree)->setBalance(0);
            rotate_right(node); break;
        case 0:
            printf("WARNING: program error in left_balance"); break;
        case 1:
            SymbolTreeNode *subTree = (*left_tree)->right;
            switch(subTree->getBalance()){
                case 0:
                    (*node)->setBalance(0);
                    (*left_tree)->setBalance(0);break;
                case -1:
                    (*node)->setBalance(0);
                    (*left_tree)->setBalance(1); break;
                case 1:
                    (*node)->setBalance(-1);
                    (*left_tree)->setBalance(0);break;
            }
            subTree->setBalance(0);
            rotate_left(left_tree);
            rotate_right(node); break;
    }
}

void SymbolTree::rotate_left(SymbolTreeNode** node)
{
    if(*node == NULL || (*node)->right == NULL)
        printf("WARNING: program error detected in rotate_left\n");
    else{
        SymbolTreeNode* right_tree = (*node)->right;
        (*node)->right=right_tree->left;
        right_tree->left=(*node);
        *node = right_tree;
    }
}

void SymbolTree::rotate_right(SymbolTreeNode** node)
{
    if(*node == NULL || (*node)->left == NULL)
        printf("WARNING: program error detected in rotate_left\n");
    else{
        SymbolTreeNode* left_tree = (*node)->left;
        (*node)->left=left_tree->right;
        left_tree->right=(*node);
        *node = left_tree;
    }
}
