/*
 * 二叉查找树
 *
 * 特征：
 * 对于二叉树中的每个节点X，其左子树中所有项的值
 * 都小于X中的项，而它的右子树中的所有项都大于X
 * 中的项.
 *
 * 这里为了方便起见，没有将接口和实现分离，
 * 如果在正式的项目中，最好还是分离；
 */

// 接口部分

#include <iostream>
#include <exception>

class UnderflowException {};

// 二叉树的节点
template <typename T>
class BinaryNode {
public:
    T elm;
    BinaryNode * left;
    BinaryNode * right;
    BinaryNode(const T & theElm, const BinaryNode & l,
            const BinaryNode & r): elm(theElm), left(l), right(r){};
};

// 二叉树定义
template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree & tree);
    ~BinarySearchTree();

    T & findMin() const;
    T & findMax() const;
    bool contains(const T & data) const;
    bool isEmpty() const;
    void printfTree() const;

    void makeEmpty();
    void insert(const T & data);
    void remove(const T & data);
    const BinarySearchTree &  operator=(const BinarySearchTree & tree);

private:
    BinaryNode<T> * root;

    BinaryNode<T> * findMin(BinaryNode<T> * node) const;
    BinaryNode<T> * findMax(BinaryNode<T> * node) const;
    bool contains(const T & data, const BinaryNode<T> * node) const;
    void insert(const T &data, BinaryNode<T> * node);
    void remove(const T &data, BinaryNode<T> * node);

    void makeEmpty(BinaryNode<T> * &node);
    void printfTree() const;
    BinaryNode<T> * clone(const BinaryNode<T> * t) const;
};

// 实现部分
template <typename T>
BinarySearchTree<T>::BinarySearchTree():root(NULL) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree & tree) {
    *this = tree;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    this.makeEmpty();
}

template <typename T>
T &
BinarySearchTree<T>::findMin() const {
    if (isEmpty() ) {
        throw new UnderflowException();
    }

    return findMin(root)->elm;
}

template <typename T>
T &
BinarySearchTree<T>::findMax() const {
    if (isEmpty()) {
        throw new UnderflowException();
    }

    return this.findMax(root)->elm;
}

template <typename T>
bool
BinarySearchTree<T>::contains(const T & data) const {
    if (data == NULL) {
        return false;
    }
    return contains(data, root);
}

template <typename T>
bool
BinarySearchTree<T>::isEmpty() const {
    return root == NULL;
}

template <typename T>
void
BinarySearchTree<T>::makeEmpty() {
    makeEmpty(root);
}

template <typename T>
void
BinarySearchTree<T>::insert(const T & data) {
    insert(data, root);
}

template <typename T>
void
BinarySearchTree<T>::remove(const T & data) {
    remove(data, root);
}

template <typename T>
const BinarySearchTree<T> &
BinarySearchTree<T>::operator=(const BinarySearchTree & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone(tree.root);
    }
    return *this;
}

template <typename T>
BinaryNode<T> *
BinarySearchTree<T>::findMin(BinaryNode<T> * node) const {

    if (node == NULL)
        return NULL;

    if (node->left) {
        return findMin(node->left);
    } else {
        return node;
    }
}

template <typename T>
BinaryNode<T> *
BinarySearchTree<T>::findMax(BinaryNode<T> * node) const {

    if (node == NULL)
        return NULL;

    if (node->right) {
        return findMax(node->right);
    } else {
        return node;
    }
}

template <typename T>
bool
BinarySearchTree<T>::contains(const T & data, const BinaryNode<T> * node) const {
    if (node == NULL) {
        return false;
    } else if (data < node.elm) {
        contains(data, node->left);
    } else if (data > node.elm) {
        return contains(data, node->right);
    } else if (data == node.elm) {
        return true;
    }
}

template <typename T>
void insert(const T &data, BinaryNode<T> * node) {
    if (node == NULL) {
        node = new BinaryNode<T>(data, NULL, NULL);
    } else if (data < node->elm){
        insert(data, node->left);
    } else if (data > node->elm) {
        insert(data, node->right);
    }
}

template <typename T>
void remove(const T &data, BinaryNode<T> * node) {
    if (node == NULL) {
        return;
    } else if (data < node->elm) {
        remove(data, node->left);
    } else if (data > node->elm) {
        remove(data, node->right);
    } else {
        if (node->left != NULL && node->right != NULL) {
            node->elm = findMin(node->right)->elm;
            remove(node->elm, node->right);
        } else if (node->left != NULL || node->right != NULL) {
            BinaryNode<T> * oldElm = node;
            node = node->left != NULL ? node->left : node->right;
            delete oldElm;
        } else {
            delete node;
        }
    }
}

template <typename T>
void
BinarySearchTree<T>::makeEmpty(BinaryNode<T> * &node) {
    if (node !=NULL) {
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    node = NULL;
}

template <typename T>
BinaryNode<T> *
BinarySearchTree<T>::clone(const BinaryNode<T> * node) const {
    if (node == NULL)
        return NULL;
    else
        return clone(node->elm, clone(node->left), clone(node->right));
}
