#include <iostream>
#include <exception>
#include <cctype>
#include <stdexcept>
#include <string.h>
#include "printTree.h"
#include "search.tree.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

// 构造函数
BinarySearchTree::BinarySearchTree():root(NULL) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree & tree) {
    *this = tree;
}

BinarySearchTree::~BinarySearchTree() {
    makeEmpty();
}

// 公共函数
int
BinarySearchTree::findMin() const {
    if (isEmpty() ) {
        throw new overflow_error("Tree is empty.");
    }

    return findMin(root)->elm;
}

int
BinarySearchTree::findMax() const {
    if (isEmpty()) {
        throw new overflow_error("Tree is empty.");
    }

    return findMax(root)->elm;
}

bool
BinarySearchTree::contains(const int data) const {
    if (isdigit(data)) {
        return false;
    }
    return contains((const BinaryNode *&)root, data);
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
BinarySearchTree::traversal(ostringstream & out) const {
    return traversal((const BinaryNode *&)root, out);
}

void
BinarySearchTree::insert(const int data) {
    // 传递root节点的引用
    insert(root, data);
}

void
BinarySearchTree::remove(const int data) {
    remove(root, data);
}

BinarySearchTree &
BinarySearchTree::operator=(const BinarySearchTree & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone(tree.root);
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

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
BinarySearchTree::contains(const BinaryNode * &node, const int data) const {
    if (node == NULL) {
        return false;
    } else if (data < node->elm) {
        return contains((const BinaryNode *&)node->left, data);
    } else if (data > node->elm) {
        return contains((const BinaryNode *&)node->right, data);
    } else {
        return true;
    }
}

void
BinarySearchTree::insert(BinaryNode * & node, const int data) {
    if (node == NULL) {
        // 如果node为空，表示其为根节点
        // 那么直接对其引用赋值，实例化一个node给它.
        node = new BinaryNode(data, NULL, NULL);
    } else if (data < node->elm){
        insert(node->left, data);
    } else if (data > node->elm) {
        insert(node->right, data);
    }
}

// 这里
void
BinarySearchTree::remove(BinaryNode * &node, const int data) {
    if (node == NULL) {
        return;
    } else if (data < node->elm) {
        remove(node->left, data);
    } else if (data > node->elm) {
        remove(node->right, data);
    } else {
        if (node->left != NULL && node->right != NULL) {
            // 如果有两个子节点, 删除右子节点中最小节点；
            node->elm = findMin(node->right)->elm;
            remove(node->right, node->elm);
        } else  {
            // 如果只有一个子节点或者根本没有子节点，直接删除
            BinaryNode * dNode = node;
            node = node->left != NULL ? node->left : node->right;
            delete dNode;
            dNode = NULL;
        }
    }
}

void
BinarySearchTree::makeEmpty(BinaryNode * &node) {
    if (node !=NULL) {
        makeEmpty(node->left);
        makeEmpty(node->right);

        delete node;
        node = NULL;
    }
}

void
BinarySearchTree::traversal(const BinaryNode *&node, ostringstream & out)
    const {
    if (!node)
        return;
    if (node->left) {
        traversal((const BinaryNode *&)node->left, out);
    }
    if (node) {
        out << node->elm << ",";
    }
    if (node->right) {
        traversal((const BinaryNode *&)node->right, out);
    }
}

BinaryNode *
BinarySearchTree::clone(const BinaryNode * node) const {
    if (node == NULL)
        return NULL;
    else
        return new BinaryNode(node->elm, clone(node->left), clone(node->right));
}
