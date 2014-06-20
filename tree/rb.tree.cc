#include <iostream>
#include <cctype>
#include "rb.tree.h"
#include "printTree.h"

using namespace std;

// 构造函数
RBTree::RBTree():root(NIL) {}

RBTree::RBTree(const RBTree & tree) {
    *this = tree;
}

RBTree::~RBTree() {
    makeEmpty();
}

////////////////////////////////////////////////////////////////////////////////
// Public functions

int
RBTree::findMin() const {
    RBNode * node = findMin((RBNode *)root);
    return node->elm;
}

int
RBTree::findMax() const {
    RBNode * node = findMax((RBNode *)root);
    return node->elm;
}

bool
RBTree::contains(const int d) const {
    return contains((const RBNode *&)root, d);
}

void
RBTree::makeEmpty() {
    if (isEmpty() == false) {
        makeEmpty(root);
    }
}

bool
RBTree::isEmpty() const {
    return root == NIL ? true : false;
}

void
RBTree::traversalWithColor(ostringstream & out) const {
    traversalWithColor((const RBNode *&)root, out);
}

void
RBTree::traversal(ostringstream & out) const {
    traversal((const RBNode *&)root, out);
}

void
RBTree::insert(int d) {
    insert(root, (RBNode *)NIL, d);
}

void
RBTree::remove(int d) {
    remove(root, d);
}

int
RBTree::getBlackHeight() {
    getBlackHeight((const RBNode *&)root);
}

RBTree &
RBTree::operator=(const RBTree & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone((const RBNode *&)tree.root,
                (RBNode *)NIL);
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Private functions

RBNode *
RBTree::findMin(RBNode * node) const {
    if (node->left)
        return findMin((RBNode * )node->left);
    else
        return node;
}

RBNode *
RBTree::findMax(RBNode * node) const {
    if (node->right)
        return findMax((RBNode * )node->right);
    else
        return node;
}

bool
RBTree::contains(const RBNode * &node,  const int data) const {
    if (!node)
        return false;
    else {
        if (data < node->elm) {
            return contains((const RBNode *&)node->left, data);
        } else if (data > node->elm) {
            return contains((const RBNode *&)node->right, data);
        } else {
            return true;
        }
    }
}

void
RBTree::insert(RBNode * &node, RBNode * pNode, int d) {
    if (node == NIL) {
        node = new RBNode(d, NIL, NIL, pNode);
        insertFixup(node);
    } else if (d< node->elm){
        insert((RBNode *&)node->left, node, d);
    } else if (d> node->elm) {
        insert((RBNode *&)node->right, node, d);
    } else {
        return;
    }
}

void
RBTree::remove(RBNode * &node, int d) {
   if (node == NIL) {
       return;
   } else if (d< node->elm) {
       remove((RBNode *&)node->left, d);
   } else if (d> node->elm) {
       remove((RBNode *&)node->right, d);
   } else {
        int originalColor = node->color;
        RBNode  * dNode = node,     // 将被删除的节点
                * tmpNode,          // 临时节点，用于替换
                * xNode,            // 可能打破平衡的节点
                * pNode;            //
        if (node->left != NIL && node->right != NIL) {
            tmpNode = findMin((RBNode *)node->right);
            pNode = tmpNode;

            originalColor = tmpNode->color;
            xNode = (RBNode *)tmpNode->right;

            if (node->right == tmpNode) {
                tmpNode->left = node->left;
            } else {
                if (tmpNode->parent->left == tmpNode) {
                    tmpNode->parent->left = tmpNode->right;
                } else {
                    tmpNode->parent->right = tmpNode->right;
                }

                tmpNode->left  = node->left;
                tmpNode->right = node->right;
            }

            pNode = tmpNode;
        } else {
            pNode = node->parent;
            if (node->left == NIL) {
                tmpNode = (RBNode *)node->right;
            } else {
                tmpNode = (RBNode *)node->left;
            }
            xNode = tmpNode;
        }


        if (node->left != NIL) {
            ((RBNode *)node->left)->parent  = tmpNode;
        }

        if (node->right != NIL) {
            ((RBNode *)node->right)->parent = tmpNode;
        }

        transplant(node, tmpNode);

        delete dNode;
        dNode = NULL;

        // 只有删除的是黑色节点时，才修复
        if (originalColor == BLACK_COLOR) {
            removeFixup(tmpNode, pNode);
        }
   }
}

int
RBTree::getBlackHeight(const RBNode * &node) const {
    if (node == NIL) {
        return 0;
    }

    int lH(0), rH(0);
    lH = getBlackHeight((const RBNode *&)node->left);
    rH = getBlackHeight((const RBNode *&)node->right);
    lH = lH>rH ? lH : rH;

    return node->color == BLACK_COLOR ? lH + 1 : lH;
}

void
RBTree::makeEmpty(RBNode * &node) {
    if (node!=NULL) {
        makeEmpty((RBNode *&)node->left);
        makeEmpty((RBNode *&)node->right);

        delete node;
        node = NULL;
    }
}

void
RBTree::traversalWithColor(const RBNode *& node, ostringstream & out) const {
    if (!node)
        return;

    if (node->left) {
        traversal((const RBNode *&)node->left, out);
    }

    if (node) {
        out << node->elm << "(" << getColor(node) << ")" << ",";
    }

    if (node->right) {
        traversal((const RBNode *&)node->right, out);
    }
}

void
RBTree::traversal(const RBNode *& node, ostringstream & out) const {
    if (!node)
        return;

    if (node->left) {
        traversal((const RBNode *&)node->left, out);
    }

    if (node) {
        out << node->elm << ",";
    }

    if (node->right) {
        traversal((const RBNode *&)node->right, out);
    }
}

RBNode *
RBTree::clone(const RBNode * &node, RBNode * pNode){
    RBNode * tmpNode = new RBNode(node->elm,
            NULL, NULL, (RBNode *)pNode);

    if (node->left)
        tmpNode->left = clone((const RBNode *&)node->left,
                tmpNode);

    if (node->right)
        tmpNode->right = clone((const RBNode *&)node->right,
                tmpNode);

    return tmpNode;
}

// Replace node1 with node 2
void
RBTree::transplant(RBNode *&node1, RBNode *&node2){
    if (node1 == node2) {
        return;
    }

    RBNode * tmpNode = node1;

    if (node1->parent == NULL) {
        root = node2;
    } else {
        if (node1->parent->left == node1) {
            node1->parent->left = node2;
        } else
            node1->parent->right = node2;
    }

    if (node2)
        node2->parent = tmpNode->parent;

    // 为了方便修复，这里让node2保持和node1一样额着色
    if (node2 != NIL)
        node2->color = node1->color;
}

int
RBTree::getColor(const RBNode * &node) const {
    if (node == NULL) {
        return -1;
    }
    return node->color == BLACK_COLOR ? 'B':'R';
}

void
RBTree::insertFixup(RBNode *&node) {
    while (node->parent && node->parent->color == RED_COLOR) {
        RBNode * cNode = node;
        RBNode * pNode = node->parent;
        RBNode * uNode;

        if (pNode->parent!= NIL) {
            if (pNode->parent->left == pNode) {
                uNode = (RBNode *)pNode->parent->right;
            } else {
                uNode = (RBNode *)pNode->parent->left;
            }

            // case 1
            if (uNode != NIL && uNode->color == RED_COLOR) {
                    cout << "yes1" << endl;
                pNode->color         = BLACK_COLOR;
                pNode->parent->color = RED_COLOR;
                uNode->color         = BLACK_COLOR;
            } else if (uNode == NIL || uNode->color == BLACK_COLOR) {
                if (node->parent->left == node) {
                    // case 2
                    cout << "yes2" << endl;
                    pNode->color  = BLACK_COLOR;
                    pNode->parent = RED_COLOR;
                    rightRotate(pNode);
                } else {
                    // case 3
                    cout << "yes3" << endl;
                    cNode = pNode;
                    leftRotate(pNode);
                    insertFixup(cNode);
                }
            }
        }
    }
    root->color = BLACK_COLOR;
}

void
RBTree::removeFixup(RBNode *&node, RBNode *&pNode) {
    while (node!= root && (node==NIL || node->color == BLACK_COLOR)) {
        if (pNode->left == node) {
            RBNode * bNode = (RBNode *)pNode->right;

            // case 1: bNode->color 是红色
            if (bNode != NIL && bNode->color == RED_COLOR) {
                pNode->color = RED_COLOR;
                bNode->color = BLACK_COLOR;
                leftRotate(pNode);
                // 重置标志
                bNode = (RBNode *)pNode->right;
            }

            // case 2: bNode->color 是黑色，双子节点都是黑色
            if ((bNode->left == NIL ||
                        ((RBNode *)bNode->left)->color == BLACK_COLOR) &&
                  (bNode->right == NIL ||
                        ((RBNode *)bNode->right)->color == BLACK_COLOR)) {
                bNode->color = RED_COLOR;
                // 将node移动至其父节点
                node = pNode;
            } else if (bNode->right == NIL ||
                    ((RBNode *)bNode->right)->color == BLACK_COLOR) {
            // case 3: bNode->color 是黑色，右子节点是黑色
                ((RBNode *)bNode->left)->color = BLACK_COLOR;
                bNode->color                   = RED_COLOR;
                rightRotate(bNode);

                // 重置标志
                bNode = (RBNode *)pNode->right;

            // case 4: bNode->color 是黑色，左子结点是黑色
                ((RBNode *)pNode)->color = BLACK_COLOR;
                bNode->color                    = RED_COLOR;
                ((RBNode *)bNode->right)->color = BLACK_COLOR;

                leftRotate(pNode);
                pNode = bNode;
            }
        } else {
            RBNode * bNode = (RBNode *)pNode->left;

            // case 1: bNode->color 是红色
            if (bNode != NIL && bNode->color == RED_COLOR) {
                pNode->color = RED_COLOR;
                bNode->color        = BLACK_COLOR;
                leftRotate(pNode);
                // 重置标志
                bNode = (RBNode *)pNode->left;
            }

            // case 2: bNode->color 是黑色，双子节点都是黑色
            if ((bNode->left == NIL ||
                        ((RBNode *)bNode->left)->color == BLACK_COLOR) &&
                  (bNode->right == NIL ||
                        ((RBNode *)bNode->right)->color == BLACK_COLOR)) {
                bNode->color = RED_COLOR;
                // 将node移动至其父节点
                node = pNode;
            } else if (bNode->left== NIL ||
                    ((RBNode *)bNode->left)->color == BLACK_COLOR) {
            // case 3: bNode->color 是黑色，左子节点是黑色
                ((RBNode *)bNode->right)->color = BLACK_COLOR;
                bNode->color                   = RED_COLOR;
                leftRotate(bNode);

                // 重置标志
                bNode = (RBNode *)pNode->left;

            // case 4: bNode->color 是黑色，左子结点是黑色
                ((RBNode *)pNode)->color = BLACK_COLOR;
                bNode->color                    = RED_COLOR;
                ((RBNode *)bNode->left)->color = BLACK_COLOR;

                rightRotate(pNode);
                pNode = bNode;
            }
        }
    }

    if (node!=NIL)
        node->color = BLACK_COLOR;
}

void
RBTree::leftRotate(RBNode * &node){
    RBNode * subNode = (RBNode *)node->right;
    RBNode * tmpNode = node;

    if (subNode) {
        tmpNode->right = subNode->left;

        if (subNode->left)
            ((RBNode *)subNode->left)->parent = tmpNode;

        if (tmpNode->parent==NIL) {
            root = subNode;
        } else if (((RBNode *)tmpNode->parent)->left == tmpNode) {
            ((RBNode *)tmpNode->parent)->left= subNode;
        } else {
            ((RBNode *)tmpNode->parent)->right= subNode;
        }

        subNode->parent = tmpNode ->parent;
        subNode->left   = tmpNode;
        tmpNode->parent = subNode;
    }
}

void
RBTree::rightRotate(RBNode * &node){
    RBNode * subNode = (RBNode *)node->left;
    RBNode * tmpNode = node;

    if (subNode) {
        tmpNode->left = subNode->right;

        if (subNode->right)
            ((RBNode *)subNode->right)->parent = tmpNode;

        if (tmpNode->parent==NIL) {
            root = subNode;
        } else if (((RBNode *)tmpNode->parent)->left == tmpNode) {
            ((RBNode *)tmpNode->parent)->left= subNode;
        } else {
            ((RBNode *)tmpNode->parent)->right= subNode;
        }

        subNode->parent = tmpNode->parent;
        subNode->right  = tmpNode;
        tmpNode->parent = subNode;
    }
}

void
RBTree::rightLeftRotate(RBNode * &node){
    rightRotate((RBNode *&)node->right);
    leftRotate(node);
}

void
RBTree::leftRightRotate(RBNode * &node){
    leftRotate((RBNode *&)node->left);
    rightRotate(node);
}
/*
int main(void) {
    RBTree * tree = new RBTree();

    cout << ( tree->root == NIL ) << endl;

    // 组建一棵树：
    tree->root                      = new RBNode(3, NULL, NULL,
            NULL, BLACK_COLOR);
    tree->root->left                = new RBNode(1, NULL, NULL,
            tree->root, BLACK_COLOR);
    tree->root->left->right         = new RBNode(2, NULL, NULL,
            (RBNode *)tree->root->left, BLACK_COLOR);
    tree->root->right               = new RBNode(6, NULL, NULL,
            tree->root, RED_COLOR);
    tree->root->right->left         = new RBNode(4, NULL, NULL,
            (RBNode *)tree->root->right, BLACK_COLOR);
    tree->root->right->left->right  = new RBNode(5, NULL, NULL,
            (RBNode *)tree->root->right->left, BLACK_COLOR);
    tree->root->right->right        = new RBNode(7, NULL, NULL,
            (RBNode *)tree->root->right, BLACK_COLOR);
    tree->root->right->right->right = new RBNode(8, NULL, NULL,
            (RBNode *)tree->root->right->right, BLACK_COLOR);

    ostringstream os1, os2;
    tree->traversalWithColor(os1);

    printPretty(tree->root, 4, 0, cout);

    cout << os1.str() << endl;

    tree->remove(1);
    tree->traversalWithColor(os2);

    cout << os2.str() << endl;

    printPretty(tree->root, 4, 0, cout);

    return 0;
}*/
