/*******************************************************************************
 红黑树


 特征：
 1. 每个节点，不是红色就使黑色；
 2. 根节点是黑色的；
 3. 每个叶节点（NIL）都是黑色的；
 4. 如果一个节点是红的，那么它的两个子节点都使黑色的；
 5. 对于每个节点，从该节点到其后代节点的简单路径，均含有相同数目黑色节点；

 注：
 1. 数据元素直接用int实现，也是为了方便验证；

*******************************************************************************/
#ifndef ALG_TREE_RB_BINARYSEARCHTREE_H
#define ALG_TREE_RB_BINARYSEARCHTREE_H
#include <sstream>
#include "binary.node.h"

#define RED_COLOR   0
#define BLACK_COLOR 1
#define NIL         NULL

using namespace std;

class RBNode: public BinaryNode{
public:
    RBNode * parent;
    int color;

    RBNode(int d, RBNode * l, RBNode * r,
            RBNode * p): BinaryNode(d, l, r),
            parent(p), color(RED_COLOR) {}
};

class RBTree {
public:
    RBTree();
    RBTree(const RBTree & tree);
    ~RBTree();

    int findMin() const;
    int findMax() const;

    bool contains(const int data) const;
    bool isEmpty() const;
    void makeEmpty();
    void traversal(ostringstream & out) const;

    void insert(const int data);
    void remove(const int data);

    RBTree & operator=(const RBTree & tree);

    RBNode * root;

private:
    RBNode * findMin(RBNode * node) const;
    RBNode * findMax(RBNode * node) const;

    bool contains(const RBNode * &node,  const int data) const;

    void insert(RBNode * &node, RBNode * pnode, const int d);
    void remove(RBNode * &node, const int d);

    void makeEmpty(RBNode * &node);
    void traversal(const RBNode * &node, ostringstream & out) const;
    RBNode * clone(const RBNode * &node, RBNode * pNode);

    void transplant(RBNode *&node1, RBNode *&node2);
    int getColor(const RBNode *&node) const;

    void insertFixup(RBNode *&node);
    void removeFixup(RBNode *&node, RBNode *&pNode);
    void leftRotate(RBNode * &node);
    void rightRotate(RBNode * &node);
    void rightLeftRotate(RBNode * &node);
    void leftRightRotate(RBNode * &node);
};
#endif
