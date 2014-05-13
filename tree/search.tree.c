#include <stdio.h>
#include <stdlib.h>


typedef struct BinaryNode_s BinaryNode;
struct BinaryNode_s {
    void * elm;
    BinaryNode * left;
    BinaryNode * right;
};


