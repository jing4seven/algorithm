#include <iostream>
#include <cctype>
#include "avl.tree.h"
#include "printTree.h"

using namespace std;

// 构造函数
AvlTree::AvlTree():root(NULL) {}

AvlTree::AvlTree(const AvlTree & tree) {
    *this = tree;
}

AvlTree::~AvlTree() {
    makeEmpty();
}

////////////////////////////////////////////////////////////////////////////////
// Public functions

int
AvlTree::findMin() const {
    AvlNode * node = findMin((AvlNode *)root);
    return node->elm;
}

int
AvlTree::findMax() const {
    AvlNode * node = findMax((AvlNode *)root);
    return node->elm;
}

bool
AvlTree::contains(const int d) const {
    return contains((const AvlNode *&)root, d);
}

void
AvlTree::makeEmpty() {
    if (isEmpty() == false) {
        makeEmpty(root);
    }
}

bool
AvlTree::isEmpty() const {
    return getHeight((const AvlNode*&)root) == 0 ? true : false;
}

void
AvlTree::traversal(ostringstream & out) const {
    traversal((const AvlNode *&)root, out);
}

void
AvlTree::insert(int d) {
    insert(root, NULL, d);
}

void
AvlTree::remove(int d) {
    remove(root, d);
}

AvlTree &
AvlTree::operator=(const AvlTree & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone((const AvlNode *&)tree.root,
                (AvlNode *)NULL);
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Private functions

AvlNode *
AvlTree::findMin(AvlNode * node) const {
    if (node->left)
        return findMin((AvlNode * )node->left);
    else
        return node;
}

AvlNode *
AvlTree::findMax(AvlNode * node) const {
    if (node->right)
        return findMax((AvlNode * )node->right);
    else
        return node;
}

bool
AvlTree::contains(const AvlNode * &node,  const int data) const {
    if (!node)
        return false;
    else {
        if (data < node->elm) {
            return contains((const AvlNode *&)node->left, data);
        } else if (data > node->elm) {
            return contains((const AvlNode *&)node->right, data);
        } else {
            return true;
        }
    }
}

/*
 * Solution comes from here:
 * http://pages.cs.wisc.edu/~paton/readings/liblitVersion/AVL-Tree-Rotations.pdf
 *
 * Psuedo code:
 *
 * If tree is right heavy
 *      If tree's right subtree is left heavy
 *          Perform rightLeftRotate
 *      else
 *          Perform leftRotate
 * Else if tree is left heavy
 *      If tree's left subtree is right heavy
 *          Perform leftRightRotate
 *      else
 *          Perform rightRotate
 *
 * 首先找到不平衡的位置
 * 然后再做平衡
 */
void
AvlTree::insert(AvlNode * &node, AvlNode * pnode, int d) {
    if (node == NULL) {
        node = new AvlNode(d, NULL, NULL, pnode);
    } else if (d<node->elm) {
        insert((AvlNode*&)node->left,node, d);

        // 检查并修复平衡性
        if (getHeight((const AvlNode *&)node->left) -
                getHeight((const AvlNode *&)node->right) == 2) {
                AvlNode * tmpNode = (AvlNode *)node->left;
            if (getHeight((const AvlNode *&)tmpNode->right) >
                getHeight((const AvlNode *&)tmpNode->left)) {
                leftRightRotate(node);
            } else {
                rightRotate(node);
            }
        }

    } else if (d>node->elm) {
        insert((AvlNode*&)node->right,node, d);

        // 检查并修复平衡性
        if (getHeight((const AvlNode *&)node->right) -
                getHeight((const AvlNode *&)node->left) == 2) {
                AvlNode * tmpNode = (AvlNode *)node->right;
            if (getHeight((const AvlNode *&)tmpNode->left) >
                getHeight((const AvlNode *&)tmpNode->right)) {
                rightLeftRotate(node);
            } else {
                leftRotate(node);
            }
        }

    } else
        ; // 如果d（要插入）的数已经存在，不作处理

    // 为了可以得到更新后的节点高度，这里需要对node更新高度
    node->height = max(getHeight((const AvlNode *&)node->left),
            getHeight((const AvlNode *&)node->right)) + 1;
}

void
AvlTree::remove(AvlNode * &node, int d) {
    if (node == NULL)
        return;

    if (node->elm < d) {
        remove((AvlNode *&)node->right, d);
    } else if (node->elm > d){
        remove((AvlNode *&)node->left, d);
    } else {
        AvlNode * tagNode,          // 记录平衡可能被打破的节点
                * dNode = node;     // 记录即将被删除的节点

        if (node->right != NULL && node->left != NULL) {
            // 首先找到右节点中最小值节点
            AvlNode * tmpNode = findMin((AvlNode *)(node->right));

            // 如果最小节点就是node的右节点
            // 直接用node的右节点代替node
            if (tmpNode == node->right) {
                tmpNode->left = node->left;

                //  记录平衡可能被打破的节点
                tagNode = tmpNode;
            } else {
            // 否则，先用tmpNode代替node, 再将tmpNode的子节点
            // （右节点）并入到tmpNode原先的父节的左子节点上

                // tmpNode将代替node，那么它的右子节点（如果有
                // 子节点的话，只能是右子节点）作为tmpNode父节
                // 点得左子节点.
                tmpNode->parent->left = tmpNode->right;

                // 将tmpNode替代node之前，将node的子节点赋予给
                // tmpNode，因为transplant不处理子节点的转移。
                tmpNode->left = node->left;
                tmpNode->right= node->right;

                //  记录平衡可能被打破的节点
                tagNode = tmpNode->parent;
            }

            if (node->left)
                ((AvlNode *)node->left)->parent = tmpNode;

            if (node->right)
                ((AvlNode *)node->right)->parent = tmpNode;

            transplant(node, tmpNode);
        } else {
        // 此时直接删除即可

            // 首先需要计算子节点
            AvlNode * tmpNode = node->left != NULL ?
                (AvlNode *)node->left :
                (AvlNode *)node->right;

            // 记录平衡可能被打破的节点
            tagNode = node->parent;
            // transplant包含tmpNode为NULL的情况
            transplant(node, tmpNode);
        }

        delete dNode;
        dNode = NULL;

        updateHeight(root);

        if (tagNode == NULL)
            return;

        // 检查并修复平衡性
        int lH(0), rH(0);
        if (tagNode->left)
            lH = getHeight((const AvlNode *&)tagNode->left);

        if (tagNode->right)
            rH = getHeight((const AvlNode *&)tagNode->right);

        if ( lH - rH == 2) {
            AvlNode * subNode = (AvlNode *)tagNode->left;

            if ( getHeight((const AvlNode *&)subNode->right) >
                        getHeight((const AvlNode *&)subNode->left)) {
                leftRightRotate(tagNode);
            } else {
                rightRotate(tagNode);
            }
        } else if ( rH - lH == 2) {
            AvlNode * subNode = (AvlNode *)tagNode->right;

            if ( getHeight((const AvlNode *&)subNode->left) >
                        getHeight((const AvlNode *&)subNode->right)) {
                rightLeftRotate(tagNode);
            } else {
                leftRotate(tagNode);
            }
        }
    }
}

void
AvlTree::makeEmpty(AvlNode * &node) {
    if (node!=NULL) {
        makeEmpty((AvlNode *&)node->left);
        makeEmpty((AvlNode *&)node->right);

        delete node;
        node = NULL;
    }
}

void
AvlTree::traversal(const AvlNode *& node, ostringstream & out) const {
    if (!node)
        return;

    if (node->left) {
        traversal((const AvlNode *&)node->left, out);
    }

    if (node) {
        out << node->elm << ",";
    }

    if (node->right) {
        traversal((const AvlNode *&)node->right, out);
    }
}

AvlNode *
AvlTree::clone(const AvlNode * &node, AvlNode * pNode){
    AvlNode * tmpNode = new AvlNode(node->elm,
            NULL, NULL, (AvlNode *)pNode);

    if (node->left)
        tmpNode->left = clone((const AvlNode *&)node->left,
                tmpNode);

    if (node->right)
        tmpNode->right = clone((const AvlNode *&)node->right,
                tmpNode);

    return tmpNode;
}

// 更新node（含）下所有节点的高度
void
AvlTree::updateHeight(AvlNode * &node) {
    if (node == NULL) {
        return;
    }

    int lH(0), rH(0);

    if (node->left) {
        updateHeight((AvlNode *&)node->left);
        lH = ((AvlNode *&)node->left)->height;
    }

    if (node->right) {
        updateHeight((AvlNode *&)node->right);
        rH = ((AvlNode *&)node->right)->height;
    }

    node->height = (lH > rH ? lH : rH) + 1;
}

// Replace node1 with node 2
void
AvlTree::transplant(AvlNode *&node1, AvlNode *&node2){
    if (node1 == node2) {
        return;
    }

    AvlNode * tmpNode = node1;

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
}

int
AvlTree::getHeight(const AvlNode *&node) const {
    return node!=NULL ? node->height : 0;
}

void
AvlTree::leftRotate(AvlNode * &node){
    AvlNode * subNode = (AvlNode *)node->right;
    AvlNode * tmpNode = node;

    if (subNode) {
        tmpNode->right = subNode->left;

        if (subNode->left)
            ((AvlNode *)subNode->left)->parent = tmpNode;

        if (tmpNode->parent==NULL) {
            root = subNode;
        } else if (((AvlNode *)tmpNode->parent)->left == tmpNode) {
            ((AvlNode *)tmpNode->parent)->left= subNode;
        } else {
            ((AvlNode *)tmpNode->parent)->right= subNode;
        }

        subNode->parent = tmpNode ->parent;
        subNode->left   = tmpNode;
        tmpNode->parent    = subNode;

        // 更新节点高度
        tmpNode->height    = max(getHeight((const AvlNode *&)tmpNode->left),
                getHeight((const AvlNode *&)tmpNode->right))+1;
        subNode->height = max(getHeight((const AvlNode *&)subNode->right),
                getHeight((const AvlNode *&)tmpNode)) + 1;
        tmpNode            = subNode;
    }
}

void
AvlTree::rightRotate(AvlNode * &node){
    AvlNode * subNode = (AvlNode *)node->left;
    AvlNode * tmpNode = node;

    if (subNode) {
        tmpNode->left = subNode->right;

        if (subNode->right)
            ((AvlNode *)subNode->right)->parent = tmpNode;

        if (tmpNode->parent==NULL) {
            root = subNode;
        } else if (((AvlNode *)tmpNode->parent)->left == tmpNode) {
            ((AvlNode *)tmpNode->parent)->left= subNode;
        } else {
            ((AvlNode *)tmpNode->parent)->right= subNode;
        }

        subNode->parent = tmpNode->parent;
        subNode->right  = tmpNode;
        tmpNode->parent = subNode;

        // 更新节点高度
        tmpNode->height = max(getHeight((const AvlNode *&)tmpNode->left),
                getHeight((const AvlNode *&)tmpNode->right))+1;
        subNode->height = max(getHeight((const AvlNode *&)subNode->left),
                getHeight((const AvlNode *&)tmpNode)) + 1;
        tmpNode            = subNode;
    }
}

void
AvlTree::rightLeftRotate(AvlNode * &node){
    rightRotate((AvlNode *&)node->right);
    leftRotate(node);
}

void
AvlTree::leftRightRotate(AvlNode * &node){
    leftRotate((AvlNode *&)node->left);
    rightRotate(node);
}
