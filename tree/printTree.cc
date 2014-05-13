/*
 * PrintTree
 *
 * More information:
 * http://leetcode.com/2010/09/how-to-pretty-print-binary-tree.html
 */
#include "printTree.h"

using namespace std;

// Find the maximum height of the binary tree
int maxHeight(BinaryNode * node) {
    if (node ==NULL)
        return 0;

    int lh = maxHeight(node->left);
    int rh = maxHeight(node->right);

    return (lh > rh ) ? lh + 1: rh + 1;
}

// Convert an integer value to string
string intToString(int val) {
    ostringstream ss;
    ss << val;

    return ss.str();
}

// Print the arm branches (eg, /   \) on a line
void printBranches(int bLen, int nsLev, int sLen, int nLev,
        const deque<BinaryNode *> & nq, ostream &out) {
    deque<BinaryNode*>::const_iterator iter = nq.begin();

    for (int i=0; i< nLev/2; ++i) {
        out << ((i==0)? setw(sLen-1):setw(nsLev-2)) << ""
             << ((*iter++)? "/": " " );
        out << setw(2*bLen+2) << "" << ((*iter++) ? "\\" : " ");
    }
    out <<endl;
}

// Print the branches and node (eg, ___10___ )
void printNodes(int bLen, int nsLev, int sLen, int nLev,
        const deque<BinaryNode*>& nq, ostream &out) {
    deque<BinaryNode*>::const_iterator iter = nq.begin();

    for (int i=0; i< nLev; ++i, ++iter) {
        out << ((i==0)? setw(sLen) : setw(nsLev)) << ""
            << ((*iter&& (*iter)->left) ? setfill('_'): setfill(' '));
        out << setw(bLen+2) << ((*iter) ? intToString((*iter)->elm): "");
        out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' '))
            << setw(bLen) << "" << setfill(' ');
    }
    out << endl;
}

// Print the leaves only (just for the bottom row)
void printLeaves(int is, int lev, int nLev, const deque<BinaryNode *> & nq,
        ostream &out) {
    deque<BinaryNode *>::const_iterator iter = nq.begin();

    for (int i =0; i< nLev; ++i, ++iter) {
        out << ((i==0) ? setw(is+2): setw(2*lev+2))
            << ((*iter) ? intToString((*iter)->elm): "");
    }
    out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @lev: Control how wide you want the tree to sparse (eg, level 1 has the
// minimum space between nodes, while level 2 has a larger space between
// nodes)
// @is: (indent space) Change this to add some indent space to the left
// (eg, indent space of 0 means the lowetst level of the left node will
// stick to the left margin)
//
void printPretty(BinaryNode * root, int lev, int is, ostream& out) {
    int h = maxHeight(root);
    int nLev = 1;

    // eg of the length of branch for each node of each level
    int bLen = 2*((int)pow(2.0,h)-1) - (3-lev)*(int)pow(2.0,h-1);
    // distance between left neighbor node's right arm and right neighbor
    // node's left arm
    int nsLen = 2+ (lev+1)*(int)pow(2.0,h);
    // starting space to the first node to print of each level (for the
    // left most node of each level only)
    int sLen = bLen + (3-lev) + is;

    deque<BinaryNode *> nq;
    nq.push_back(root);

    for (int r = 1; r <h; ++r ) {
        printBranches(bLen, nsLen, sLen, nLev, nq, out);
        bLen = bLen/2 -1;
        nsLen = nsLen/2 + 1;
        sLen = bLen + (3-lev) + is;
        printNodes(bLen, nsLen, sLen, nLev, nq, out);

        for (int i=0; i< nLev; ++i) {
            BinaryNode * nd = nq.front();
            nq.pop_front();
            if (nd) {
                nq.push_back(nd->left);
                nq.push_back(nd->right);
            } else {
                nq.push_back(NULL);
                nq.push_back(NULL);
            }
        }
        nLev *= 2;
    }

    printBranches(bLen, nsLen, sLen, nLev, nq, out);
    printLeaves(is, lev, nLev, nq, out);
}
