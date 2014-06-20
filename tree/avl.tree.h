/*******************************************************************************
 二叉查找树

 通过删除真实节点实现remove操作，

 特征：
 对于二叉树中的每个节点X，其左子树中所有项的值都小于X中的项，而它的右子树中的
 所有项都大于X中的项.


 注：
 1. 数据元素直接用int实现，也是为了方便验证；
 2. 这个版本的二叉搜索树在插入和删除节点的实现上用是真实的节点的删除。

*******************************************************************************/
#ifndef ALG_TREE_AVL_BINARYSEARCHTREE_H
#define ALG_TREE_AVL_BINARYSEARCHTREE_H
#include <sstream>
#include "binary.node.h"

using namespace std;

class AvlNode: public BinaryNode{
public:
    AvlNode * parent;
    int height;

    AvlNode(int d, AvlNode * l, AvlNode * r,
            AvlNode * p): BinaryNode(d, l, r),
            parent(p), height(0) {}
};

class AvlTree {
public:
    AvlTree();
    AvlTree(const AvlTree & tree);
    ~AvlTree();

    int findMin() const;
    int findMax() const;

    bool contains(const int data) const;
    bool isEmpty() const;
    void makeEmpty();
    void traversal(ostringstream & out) const;

    void insert(const int data);
    void remove(const int data);

    AvlTree & operator=(const AvlTree & tree);

    AvlNode * root;

private:
    AvlNode * findMin(AvlNode * node) const;
    AvlNode * findMax(AvlNode * node) const;

    bool contains(const AvlNode * &node,  const int data) const;

    void insert(AvlNode * &node, AvlNode * pnode, const int d);
    void remove(AvlNode * &node, const int d);

    void makeEmpty(AvlNode * &node);
    void traversal(const AvlNode * &node, ostringstream & out) const;
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
#endif
