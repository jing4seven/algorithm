#ifndef ALG_REV_PRINTTREE_H
#define ALG_REV_PRINTTREE_H
#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include "binary.node.h"

using namespace std;

int maxHeight(BinaryNode *);
string intToString(int);
void printBranches(int, int, int, int,
        const deque<BinaryNode*> &, ostream &);
void printNodes(int, int, int, int,
        const deque<BinaryNode*>&, ostream &);
void printLeaves(int, int, int, const deque<BinaryNode *> &,
        ostream &);
void printPretty(BinaryNode *,int,int,ostream&);
#endif
