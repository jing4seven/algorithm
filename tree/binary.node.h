#ifndef ALG_TREE_BINARY_NODE_H
#define ALG_TREE_BINARY_NODE_H

#include <sstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class BinaryNode {
public:
    int elm;
    BinaryNode * left;
    BinaryNode * right;
    BinaryNode(const int & theElm, BinaryNode * l,
            BinaryNode * r): elm(theElm), left(l), right(r){};

    // 纯粹是为了验证方便添加的方法
    virtual string getNodeStr() {
        os.str("");
        os << elm;
        return os.str();
    }

    virtual preOrder(vecotr<BinaryNode *> & vc) const {
        BinaryNode * node = root;
        stack<BinaryNode *> stack;

        while (node != NULL && !stack.empty()) {
            BinaryNode * tmpNode = node;

            while (node != NULL) {
                stack.push(node);
                node=node->left;
            }

            if (!stack.empty()) {
                node= stack.top();

                vc.push_back(node);
                stack.pop();
                node = node->right;
            }
        }
    }

protected:
    ostringstream os;
};

#endif
