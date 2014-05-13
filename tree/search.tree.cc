/*
 * 二叉查找树
 *
 * 特征：
 * 1. 对于二叉树中的每个节点X，其左子树中所有项的值
 *    都小于X中的项，而它的右子树中的所有项都大于X
 *    中的项.
 *
 * 注：
 * 1. 这里为了方便起见，没有将接口和实现分离，
 *    如果在正式的项目中，最好还是分离；
 * 2. 数据元素直接用int实现，也是为了方便验证；
 */

// 接口部分

#include <iostream>
#include <exception>
#include <cctype>
#include "printTree.h"

using namespace std;

class UnderflowException {};

// 二叉树定义
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree & tree);
    ~BinarySearchTree();

    const int & findMin() const;
    const int & findMax() const;
    bool contains(const int data) const;
    bool isEmpty() const;
    void printfTree(ostream & out) const;

    void makeEmpty();
    void insert(const int data);
    void remove(const int data);
    const BinarySearchTree &  operator=(const BinarySearchTree & tree);
    BinaryNode * root;

private:
    BinaryNode * findMin(BinaryNode * node) const;
    BinaryNode * findMax(BinaryNode * node) const;
    bool contains(const int data, BinaryNode * node) const;
    void insert(const int data, BinaryNode * &node);
    void remove(const int data, BinaryNode * &node);

    void makeEmpty(BinaryNode * &node);
    void printfTree(const BinaryNode * node, ostream & out) const;
    BinaryNode * clone(const BinaryNode * t) const;
};

// 实现部分
BinarySearchTree::BinarySearchTree():root(NULL) {}

BinarySearchTree::BinarySearchTree(BinarySearchTree & tree) {
    *this = tree;
}

BinarySearchTree::~BinarySearchTree() {
    makeEmpty();
}

const int &
BinarySearchTree::findMin() const {
    if (isEmpty() ) {
        throw new UnderflowException();
    }

    return findMin(root)->elm;
}

const int &
BinarySearchTree::findMax() const {
    if (isEmpty()) {
        throw new UnderflowException();
    }

    return findMax(root)->elm;
}

bool
BinarySearchTree::contains(const int data) const {
    if (isdigit(data)) {
        return false;
    }
    return contains(data, root);
}

bool
BinarySearchTree::isEmpty() const {
    return root == NULL;
}

void
BinarySearchTree::makeEmpty() {
    makeEmpty(root);
}

void
BinarySearchTree::insert(const int data) {
    // 传递root节点的引用
    insert(data, root);
}

void
BinarySearchTree::remove(const int data) {
    remove(data, root);
}

const BinarySearchTree &
BinarySearchTree::operator=(const BinarySearchTree & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone(tree.root);
    }
    return *this;
}

void
BinarySearchTree::printfTree(ostream & out) const {
    if (isEmpty())
        out << "Empty tree" << endl;
    else
        printfTree(root, out);
}

BinaryNode *
BinarySearchTree::findMin(BinaryNode * node) const {

    if (node == NULL)
        return NULL;

    if (node->left) {
        return findMin(node->left);
    } else {
        return node;
    }
}

BinaryNode *
BinarySearchTree::findMax(BinaryNode * node) const {

    if (node == NULL)
        return NULL;

    if (node->right) {
        return findMax(node->right);
    } else {
        return node;
    }
}

bool
BinarySearchTree::contains(const int data, BinaryNode * node) const {
    if (node == NULL) {
        return false;
    } else if (data < node->elm) {
        contains(data, node->left);
    } else if (data > node->elm) {
        return contains(data, node->right);
    } else if (data == node->elm) {
        return true;
    }
}
void
BinarySearchTree::insert(const int data, BinaryNode * & node) {
    if (node == NULL) {
        // 如果node为空，表示其为根节点
        // 那么直接对其引用赋值，实例化一个node给它.
        node = new BinaryNode(data, NULL, NULL);
    } else if (data < node->elm){
        insert(data, node->left);
    } else if (data > node->elm) {
        insert(data, node->right);
    }
}

// 这里
void
BinarySearchTree::remove(const int data, BinaryNode * &node) {
    if (node == NULL) {
        return;
    } else if (data < node->elm) {
        remove(data, node->left);
    } else if (data > node->elm) {
        remove(data, node->right);
    } else {
        if (node->left != NULL && node->right != NULL) {
            // 如果有两个子节点, 删除右子节点中最小节点；
            node->elm = findMin(node->right)->elm;
            remove(node->elm, node->right);
        } else  {
            // 如果只有一个子节点或者根本没有子节点，直接删除
            BinaryNode * oldElm = node;
            node = node->left != NULL ? node->left : node->right;
            delete oldElm;
        }
    }
}

void
BinarySearchTree::makeEmpty(BinaryNode * &node) {
    if (node !=NULL) {
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    node = NULL;
}

BinaryNode *
BinarySearchTree::clone(const BinaryNode * node) const {
    if (node == NULL)
        return NULL;
    else
        return new BinaryNode(node->elm, clone(node->left), clone(node->right));
}

void
BinarySearchTree::printfTree(const BinaryNode * node, ostream & out) const {
    if (node != NULL) {
        printfTree(node->left, out);
        out << node->elm << endl;
        printfTree(node->right, out);
    }
}

int main() {
    BinarySearchTree * tree = new BinarySearchTree();
    tree->insert(30);
    tree->insert(20);
    tree->insert(40);
    tree->insert(10);
    tree->insert(25);
    tree->insert(35);
    tree->insert(50);
    tree->insert(5);
    tree->insert(15);
    tree->insert(28);
    tree->insert(41);

    cout << "Print tree:"<<endl;
    //tree->printfTree(cout);
    printPretty(tree->root, 1, 0, cout);

    tree->remove(30);
    cout << "After remove root item:" <<endl;
    //tree->printfTree(cout);
    printPretty(tree->root, 1, 0, cout);

    tree->makeEmpty();
    return 0;

}
