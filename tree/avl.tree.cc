#include "printTree.h"
#include "math.h"

class AvlNode: public BinaryNode{
public:
    int height;
    AvlNode * parent;

    AvlNode(int d, AvlNode * l, AvlNode * r,
            AvlNode * p): BinaryNode(d, l, r),
            parent(p), height(0) {}
};

class AvlTree {
public:
    AvlTree();
    AvlTree(AvlTree & tree);
    ~AvlTree();

    int findMin() const;
    int findMax() const;

    bool contains(const int d) const;
    bool isEmpty() const;
    void makeEmpty();

    void insert(const int d);
    void remove(const int d);

    AvlTree & operator=(const AvlTree & tree);

    AvlNode * root;

private:
    AvlNode * findMin(AvlNode * node) const;
    AvlNode * findMax(AvlNode * node) const;
    bool contains(const AvlNode * &node,  const int d) const;

    void insert(AvlNode * &node, AvlNode * pnode, const int d);
    void remove(AvlNode * &node, const int d);

    void makeEmpty(AvlNode * &node);
    AvlNode * clone(const AvlNode * &node);

    void updateHeight(AvlNode * &node);
    void transplant(AvlNode *&node1, AvlNode *&node2);

    int getHeight(const AvlNode *&node) const;
    void blanceTree(AvlNode * &node);
    void leftRotate(AvlNode * &node);
    void rightRotate(AvlNode * &node);
    void rightLeftRotate(AvlNode * &node);
    void leftRightRotate(AvlNode * &node);
};

//////////////////////////////////////////////////////////////////////

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
AvlTree::insert(int d) {
    insert(root, NULL, d);
}

void
AvlTree::remove(int d) {
    remove(root, d);
}

void
AvlTree::makeEmpty() {
    makeEmpty(root);
}


AvlTree &
AvlTree::operator=(const AvlTree & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone((const AvlNode *&)tree.root);
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////

AvlNode * AvlTree::findMin(AvlNode * node) const {
    if (node->left)
        return findMin((AvlNode * )node->left);
    else
        return node;
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

        AvlNode * tmpNode = (AvlNode *)node->left;
        // 重新平衡
        if (getHeight((const AvlNode *&)tmpNode->right) -
                getHeight((const AvlNode *&)tmpNode->left) == 2) {
            leftRightRotate(node);
        } else {
            rightRotate(node);
        }

    } else if (d>node->elm) {
        insert((AvlNode*&)node->right,node, d);

        AvlNode * tmpNode = (AvlNode *)node->right;
        // 重新平衡
        if (getHeight((const AvlNode *&)tmpNode->left) -
                getHeight((const AvlNode *&)tmpNode->right) == 2) {
            rightLeftRotate(node);
        } else {
            leftRotate(node);
        }
    } else
        ; // If d exists, do nothing.

    // 为了可以得到更新后的节点高度，这里需要对node更新高度
    node->height = max(getHeight((const AvlNode *&)node->left),
            getHeight((const AvlNode *&)node->right)) + 1;
}

void
AvlTree::remove(AvlNode * &node, int d) {
    if (node->elm < d) {
        remove((AvlNode *&)node->left, d);
    } else if (node->elm > d){
        remove((AvlNode *&)node->right, d);
    } else {
        if (node->right != NULL && node->left != NULL) {
            // 首先找到右节点中最小值节点
            AvlNode * tmpNode = findMin((AvlNode *)(node->right));

            // 如果最小节点就是node的右节点
            // 直接用node的右节点代替node
            if (tmpNode == node->right) {
                transplant(node, (AvlNode *&)node->right);
                tmpNode->left = node->left;
            } else {
            // 否则，先用tmpNode代替node, 再将tmpNode的子节点
            // （右节点）并入到tmpNode原先的父节的左子节点上
                AvlNode * tmpPNode = tmpNode->parent;
                transplant(node, (AvlNode *&)tmpNode);
                tmpNode->left = node->left;
                tmpNode->right= node->right;

                if (tmpPNode) {
                    tmpPNode->left = tmpNode->right;
                }
            }

        } else {
            // 此时直接删除即可
            // 首先需要计算子节点
            AvlNode * tmpNode = node->left == NULL ?
                (AvlNode *)node->left :
                (AvlNode *)node->right;

            transplant(node, tmpNode);
        }

        delete node;
        updateHeight(root);
    }
}

void
AvlTree::makeEmpty(AvlNode * &node) {
    if (node != NULL) {
        makeEmpty((AvlNode *&)node->left);
        makeEmpty((AvlNode *&)node->right);
        delete node;
    }
    node = NULL;
}

AvlNode *
AvlTree::clone(const AvlNode * &node){
    AvlNode * tmpNode = new AvlNode(node->elm,
            (AvlNode *)node->left,
            (AvlNode *)node->right,
            NULL);

    if (node->left)
        tmpNode->left = clone((const AvlNode *&)node->left);

    if (node->right)
        tmpNode->right = clone((const AvlNode *&)node->right);

    return tmpNode;
}

void
AvlTree::updateHeight(AvlNode * &node) {
    // Only update for insert item action.
    //if (node->parent) {
    //    if (node->parent->height == node->height) {
    //        node->parent->height++;
    //        updateHeight(node->parent);
    //    }
    //}

    // Update height for all items of node
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
void AvlTree::transplant(AvlNode *&node1, AvlNode *&node2){
    if (node1 == node2) {
        return;
    }

    if (node1->parent == NULL) {
        root = node2;
    } else {
        if (node1->parent->left == node1) {
            node1->parent->left = node2;
        } else
            node1->parent->right = node2;
    }

    node2->parent = node1->parent;
}

int
AvlTree::getHeight(const AvlNode *&node) const {
    return node ? node->height : 0;
}


void
AvlTree::blanceTree(AvlNode * &node) {
    int l(0), r(0);
    if (node) {
        if (node->left) {
            l=((AvlNode *)node->left)->height + 1;
            blanceTree((AvlNode *&)node->left);
        }

        if (node->right) {
            r=((AvlNode *)node->right)->height + 1;
            blanceTree((AvlNode *&)node->right);
        }

        AvlNode * heavyNode;

        if (l == 0 && abs(r - l) > 1) {
            heavyNode = (AvlNode *)node->right;

            if (heavyNode->left) {
                l=((AvlNode *)heavyNode->left)->height + 1;
            }

            if (node->right) {
                r=((AvlNode *)heavyNode->right)->height + 1;
            }

            if (l>r) {
                rightLeftRotate(node);
            } else if (r > l) {
                leftRotate(node);
            }
        } else if (r == 0 && abs(l-r) > 1) {
            heavyNode = (AvlNode *)node->left;

            if (heavyNode->left) {
                l=((AvlNode *)heavyNode->left)->height + 1;
            }

            if (node->right) {
                r=((AvlNode *)heavyNode->right)->height + 1;
            }

            if (r>l) {
                leftRightRotate(node);
            } else if (l>r) {
                rightRotate(node);
            }
        }
    }
}

void
AvlTree::leftRotate(AvlNode * &node){
    AvlNode * tmp = (AvlNode *)node->right;
    if (tmp) {
        node->right = tmp->left;
        ((AvlNode *)tmp->left)->parent = node;

        if (node->parent) {
            root = tmp;
        } else if (((AvlNode *)node->parent)->left == node) {
            ((AvlNode *)node->parent)->left= tmp;
        } else {
            ((AvlNode *)node->parent)->right= tmp;
        }

        tmp->parent  = node->parent;
        tmp->left    = node;
        node->parent = tmp;
        // 更新节点高度
        node->height = max(getHeight((const AvlNode *&)node->left),
                getHeight((const AvlNode *&)node->right))+1;
        tmp->height  = max(getHeight((const AvlNode *&)tmp->right),
                getHeight((const AvlNode *&)node)) + 1;

        node         = tmp;
    }
}

void
AvlTree::rightRotate(AvlNode * &node){
    AvlNode * tmp = (AvlNode *)node->left;

    if (tmp) {
        node->left = tmp->right;
        ((AvlNode *)tmp->right)->parent = node;

        if (node->parent) {
            root = tmp;
        } else if (((AvlNode *)node->parent)->left == node) {
            ((AvlNode *)node->parent)->left= tmp;
        } else {
            ((AvlNode *)node->parent)->right= tmp;
        }

        tmp->parent  = node->parent;
        tmp->right   = node;
        node->parent = tmp;
        // 更新节点高度
        node->height = max(getHeight((const AvlNode *&)node->left),
                getHeight((const AvlNode *&)node->right))+1;
        tmp->height  = max(getHeight((const AvlNode *&)tmp->left),
                getHeight((const AvlNode *&)node)) + 1;
        node         = tmp;
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
