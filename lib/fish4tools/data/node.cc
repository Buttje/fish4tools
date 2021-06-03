#include <inttypes.h>
#include <tribbleTools/symbolTreeNode.hpp>

using namespace tribble;

uint16_t SymbolTreeNode::leftDepth() {
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

uint16_t SymbolTreeNode::rightDepth() {
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

int8_t SymbolTreeNode::getBalance() {

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

void SymbolTreeNode::setBalance(int8_t balance) {
    _balance=balance;
}