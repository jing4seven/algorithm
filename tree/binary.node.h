#ifndef ALG_TREE_BINARY_NODE_H
#define ALG_TREE_BINARY_NODE_H

class BinaryNode {
public:
    int elm;
    BinaryNode * left;
    BinaryNode * right;
    BinaryNode(const int & theElm, BinaryNode * l,
            BinaryNode * r): elm(theElm), left(l), right(r){};
};

#endif
