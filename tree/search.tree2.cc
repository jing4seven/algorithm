/*
 * 二叉查找树
 * 插入删除操作用真实元素操作实现
 *
 */
#include <iostream>
#include <exception>
#include <cctype>
#include "printTree.h"

// 多一个属性parent
class SecuBinaryNode: public BinaryNode {
public:
    // 每个操作都需要维护父节点属性
    SecuBinaryNode * parent;

    SecuBinaryNode(const int &d, SecuBinaryNode * l, SecuBinaryNode * r,
            SecuBinaryNode * p):BinaryNode(d,l,r), parent(p){}
};

// 接口部分
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree * &tree);
    ~BinarySearchTree();

    void insert(const int data);
    void remove(const int data);
    int findMax() const;
    int findMin() const;
    bool contains(const int data) const ;
    bool isEmpty() const;
    void makeEmpty();
    BinarySearchTree &operator=(const BinarySearchTree &node);

    SecuBinaryNode * root;

private:
    SecuBinaryNode * findNext(const SecuBinaryNode * node);
    void insert(SecuBinaryNode * &node, SecuBinaryNode * pnode, int d);
    void remove(SecuBinaryNode * &node, int d);
    SecuBinaryNode * findMax(SecuBinaryNode * node) const;
    SecuBinaryNode * findMin(SecuBinaryNode * node) const;
    bool contains(const SecuBinaryNode * node, const int data) const;
    void makeEmpty(SecuBinaryNode * &node);
    SecuBinaryNode * clone(const SecuBinaryNode * node) const;
    void transplant(SecuBinaryNode * &a, SecuBinaryNode * &b);
};


BinarySearchTree::BinarySearchTree():root(NULL){}

BinarySearchTree::BinarySearchTree(BinarySearchTree * &tree) {
    *this = tree;
}

BinarySearchTree::~BinarySearchTree() {
    makeEmpty();
}

void
BinarySearchTree::insert(const int data) {
    insert(root, NULL, data);
}

void
BinarySearchTree::remove(const int data) {
    remove(root, data);
}

int
BinarySearchTree::findMax() const {
    return findMax(root)->elm;
}

int
BinarySearchTree::findMin() const {
    return findMin(root)->elm;
}

bool
BinarySearchTree::contains(const int data) const {
    return contains(root, data);
}

bool
BinarySearchTree::isEmpty() const {
    return root == NULL;
}

void
BinarySearchTree::makeEmpty() {
    makeEmpty(this->root);
}

BinarySearchTree &
BinarySearchTree::operator=(const BinarySearchTree & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone(tree.root);
    }
    return *this;
}

// 私有方法实现
SecuBinaryNode *
BinarySearchTree::findNext(const SecuBinaryNode * node) {
    if (node->right != NULL) {
        return findMin((SecuBinaryNode *)node->right);
    } else {
        SecuBinaryNode * temp;
        temp = node->parent;

        // 如果node的父节点不为空且，node是右节点
        // 说明node的父节点的值比node的值小
        // 还需要往更高层搜索
        while (temp != NULL && temp->right == node) {
            // temp网上爬一层后，它与node的相对
            // 关系发生了变化，所以node也得保持相对
            // 位置，以保持循环判定方法的正确
            node = temp;

            temp = node->parent;
        }
        return temp;
    }
}

void
BinarySearchTree::insert(SecuBinaryNode * &node, SecuBinaryNode * pnode,  int d) {
    if (node == NULL) {
        node = new SecuBinaryNode(d, NULL, NULL, pnode);
    } else if (d > node->elm) {
        insert((SecuBinaryNode *&)node->right, node, d);
    } else if (d < node->elm) {
        insert((SecuBinaryNode *&)node->left, node, d);
    }
}

void
BinarySearchTree::remove(SecuBinaryNode * &node, int d) {
    if (node == NULL) {
        return;
    }
    // 先查找要找的节点
    if (d > node->elm) {
        remove((SecuBinaryNode *&)node->right, d);
    } else if (d < node->elm) {
        remove((SecuBinaryNode *&)node->left, d);
    } else {
        // 找到节点后，查看其左右子节点是否存在
        // 如果两个子节点都存在
        // 情况稍微复杂一点
        SecuBinaryNode * temp = NULL;
        SecuBinaryNode * dNode = NULL;
        if (node->left != NULL && node->right !=NULL ) {
            temp  = findMin((SecuBinaryNode *)node->right);

            // 如果要直接右子节点就是右边最小的节点
            // 直接和node交换
            if (temp == node->right) {
                dNode = node;
                transplant(node, temp);
                node->right = temp->right;
                ((SecuBinaryNode *)temp->right)->parent = node;
            } else {
                // 如果不是，将右边最小的节点替换node
                dNode = node;
                transplant(node, temp);
                // 维护最小节点的父节点的left, right
                if (temp->parent->left == temp) {
                    temp->parent->left = temp->right;
                } else {
                    temp->parent->right = temp->right;
                }
            }

            node->left = dNode->left;
            node->right= dNode->right;
            delete dNode;

        // 只有一个子节点存在时
        // 直接用字节点替换即可
        } else {
            if (node->left==NULL)
                temp = (SecuBinaryNode *)node->right;
            else if (node->right == NULL)
                temp = (SecuBinaryNode *)node->left;

            dNode = node;
            transplant(node, temp);
            delete dNode;
        }
    }
}

SecuBinaryNode *
BinarySearchTree::findMax(SecuBinaryNode * node) const{
    if (node->right != NULL)
        return findMax((SecuBinaryNode *)node->right);

    return node;
}

SecuBinaryNode *
BinarySearchTree::findMin(SecuBinaryNode * node) const{
    if (node->left != NULL)
        return findMin((SecuBinaryNode *)node->left);

    return node;
}

bool
BinarySearchTree::contains(const SecuBinaryNode * node, const int d) const{
    while (node!=NULL && node->elm != d) {
        if (d > node->elm)
            node = (SecuBinaryNode *)node->right;
        if (d < node->elm)
            node = (SecuBinaryNode *)node->left;
    }

    return node == NULL ? false : true;
}

void
BinarySearchTree::makeEmpty(SecuBinaryNode * &node) {
    if (node != NULL) {
        makeEmpty((SecuBinaryNode *&)node->left);
        makeEmpty((SecuBinaryNode *&)node->right);

        delete node;
    }
    node = NULL;
}

SecuBinaryNode *
BinarySearchTree::clone(const SecuBinaryNode * node) const {
    SecuBinaryNode * temp = new SecuBinaryNode(node->elm, NULL, NULL, NULL);
    if (node->left != NULL)
        temp->left = clone((SecuBinaryNode *)node->left);
    else if (node->right != NULL)
        temp->right = clone((SecuBinaryNode *)node->right);

    return temp;
}

// 这个方法里，仅仅维护父节点的正确性
// 对于双子节点，再替换完成后最后的地方取处理
// 如果放在此方法中处理，可能会在删除时造成死循环
void
BinarySearchTree::transplant(SecuBinaryNode * &a, SecuBinaryNode * &b) {
    if (a->parent == NULL) {
        root = b;
    } else if (a->parent->left == a) {
        a->parent->left =b;
    } else {
        a->parent->right=b;
    }

    b->parent = a->parent;
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
