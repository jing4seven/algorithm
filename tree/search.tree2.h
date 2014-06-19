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
#ifndef ALG_TREE_BINARYSEARCHTREE2_H
#define ALG_TREE_BINARYSEARCHTREE2_H

#include <string.h>
#include "binary.node.h"

using namespace std;

// 重写了基类节点
class SecuBinaryNode: public BinaryNode {
public:
    // 每个操作都需要维护父节点属性
    SecuBinaryNode * parent;

    SecuBinaryNode(const int &d, SecuBinaryNode * l, SecuBinaryNode * r,
            SecuBinaryNode * p):BinaryNode(d,l,r), parent(p){}
};

// 接口部分
class BinarySearchTree2 {
public:
    BinarySearchTree2();
    BinarySearchTree2(const BinarySearchTree2 &tree);
    ~BinarySearchTree2();

    int findMax() const;
    int findMin() const;

    bool contains(const int data) const ;
    bool isEmpty() const;
    void makeEmpty();
    void traversal(ostringstream & out) const;

    void insert(const int data);
    void remove(const int data);

    BinarySearchTree2 &operator=(const BinarySearchTree2 &node);

    SecuBinaryNode * root;

private:
    SecuBinaryNode * findMax(SecuBinaryNode * node) const;
    SecuBinaryNode * findMin(SecuBinaryNode * node) const;

    bool contains(const SecuBinaryNode * & node, const int data) const;

    void insert(SecuBinaryNode * &node, SecuBinaryNode * pnode, const int d);
    void remove(SecuBinaryNode * &node, const int d);

    void makeEmpty(SecuBinaryNode * &node);
    SecuBinaryNode * findNext(const SecuBinaryNode * node);
    void traversal (const SecuBinaryNode * &node, ostringstream & out) const;
    SecuBinaryNode * clone(const SecuBinaryNode * node) const;

    void transplant(SecuBinaryNode * &a, SecuBinaryNode * &b);
};
#endif
