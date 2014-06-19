/*******************************************************************************
 二叉查找树

 插入删除操作用替换数据实现

 特征：
 对于二叉树中的每个节点X，其左子树中所有项的值都小于X中的项，而它的右子树中的
 所有项都大于X中的项.


 注：
 1. 数据元素直接用int实现，也是为了方便验证；
 2. 这个版本的二叉搜索树在插入和删除节点的实现上用的时数据替换，不是真实的节点
    替换；在某些情况下，这样做会导致一些问题，被删除的节点也许并不是传递到删除
    过程中的那个节点。
    如果一个程序的其他部分要维持一些指向节点的指针，那么他们可能会被这些已删除
    节点的“过时”指针带来错误的影响。

*******************************************************************************/
#ifndef ALG_TREE_BINARYSEARCHTREE_H
#define ALG_TREE_BINARYSEARCHTREE_H

#include "binary.node.h"

class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree & tree);
    ~BinarySearchTree();

    int findMin() const;
    int findMax() const;

    bool contains(const int data) const;
    bool isEmpty() const;
    void makeEmpty();

    void insert(const int data);
    void remove(const int data);

    BinarySearchTree &  operator=(const BinarySearchTree & tree);

    BinaryNode * root;

private:
    BinaryNode * findMin(BinaryNode * node) const;
    BinaryNode * findMax(BinaryNode * node) const;

    bool contains(const BinaryNode * &node, const int data) const;

    void insert(BinaryNode * &node, const int data);
    void remove(BinaryNode * &node, const int data);

    void makeEmpty(BinaryNode * &node);
    BinaryNode * clone(const BinaryNode * t) const;
};
#endif
