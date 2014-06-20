#include <iostream>
#include <sstream>
#include <exception>
#include <cctype>
#include "printTree.h"
#include "search.tree2.h"

////////////////////////////////////////////////////////////////////////////////

BinarySearchTree2::BinarySearchTree2():root(NULL){}

BinarySearchTree2::BinarySearchTree2(const BinarySearchTree2  &tree) {
    *this = tree;
}

BinarySearchTree2::~BinarySearchTree2() {
    makeEmpty();
}

int
BinarySearchTree2::findMax() const {
    return findMax(root)->elm;
}

int
BinarySearchTree2::findMin() const {
    return findMin(root)->elm;
}

bool
BinarySearchTree2::contains(const int data) const {
    return contains((const SecuBinaryNode *&)root, data);
}

void
BinarySearchTree2::insert(const int data) {
    insert(root, NULL, data);
}

void
BinarySearchTree2::remove(const int data) {
    remove(root, data);
}

bool
BinarySearchTree2::isEmpty() const {
    return root == NULL;
}

void
BinarySearchTree2::makeEmpty() {
    makeEmpty(this->root);
}

void
BinarySearchTree2::traversal(ostringstream & out) const {
    traversal((const SecuBinaryNode *&)root, out);
}

BinarySearchTree2 &
BinarySearchTree2::operator=(const BinarySearchTree2 & tree) {
    if (this != &tree) {
        makeEmpty();
        root = clone((const SecuBinaryNode * &)tree.root, NULL);
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

SecuBinaryNode *
BinarySearchTree2::findMax(SecuBinaryNode * node) const{
    if (node->right != NULL)
        return findMax((SecuBinaryNode *)node->right);

    return node;
}

SecuBinaryNode *
BinarySearchTree2::findMin(SecuBinaryNode * node) const{
    if (node->left != NULL)
        return findMin((SecuBinaryNode *)node->left);

    return node;
}

bool
BinarySearchTree2::contains(const SecuBinaryNode * &node, const int d) const{
    while (node!=NULL && node->elm != d) {
        if (d > node->elm)
            node = (const SecuBinaryNode *)node->right;
        if (d < node->elm)
            node = (const SecuBinaryNode *)node->left;
    }

    return node == NULL ? false : true;
}

void
BinarySearchTree2::insert(SecuBinaryNode * &node, SecuBinaryNode * pnode,  int d) {
    if (node == NULL) {
        node = new SecuBinaryNode(d, NULL, NULL, pnode);
    } else if (d > node->elm) {
        insert((SecuBinaryNode *&)node->right, node, d);
    } else if (d < node->elm) {
        insert((SecuBinaryNode *&)node->left, node, d);
    }
}

void
BinarySearchTree2::remove(SecuBinaryNode * &node, int d) {
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
        SecuBinaryNode * tmpNode = NULL;
        SecuBinaryNode * dNode = node;
        if (node->left != NULL && node->right !=NULL ) {
            tmpNode  = findMin((SecuBinaryNode *)node->right);

            // 如果要直接右子节点就是右边最小的节点
            // 直接和node交换
            if (tmpNode == node->right) {
                //node->right = tmpNode->right;
                //((SecuBinaryNode *)tmpNode->right)->parent = node;
                tmpNode->left = node->left;
            } else {
                // 维护最小节点的父节点的left, right
                if (tmpNode->parent->left == tmpNode) {
                    tmpNode->parent->left = tmpNode->right;
                } else {
                    tmpNode->parent->right = tmpNode->right;
                }

                tmpNode->left = node->left;
                tmpNode->right= node->right;
            }

            //node->left = dNode->left;
            //node->right= dNode->right;
        // 只有一个子节点存在时
        // 直接用字节点替换即可
        } else {
            if (node->left!=NULL)
                tmpNode = (SecuBinaryNode *)node->left;

            if (node->right != NULL)
                tmpNode = (SecuBinaryNode *)node->right;
        }
/*
        if (tmpNode) {
            tmpNode->left = node->left;
            tmpNode->right= node->right;
        }a*/

        if (node->left)
            ((SecuBinaryNode *)node->left)->parent = tmpNode;

        if (node->right)
            ((SecuBinaryNode *)node->right)->parent = tmpNode;

        transplant(node, tmpNode);

        delete dNode;
        dNode = NULL;
    }
}

SecuBinaryNode *
BinarySearchTree2::findNext(const SecuBinaryNode * node) {
    if (node->right != NULL) {
        return findMin((SecuBinaryNode *)node->right);
    } else {
        SecuBinaryNode * temp;
        temp = node->parent;

        // 如果node的父节点不为空且，node是右节点
        // 说明node的父节点的值比node的值小
        // 还需要往更高层搜索
        while (temp != NULL && temp->right == node) {
            // temp往上爬一层后，它与node的相对
            // 关系发生了变化，所以node也得保持相对
            // 位置，以保持循环判定方法的正确
            node = temp;

            temp = node->parent;
        }
        return temp;
    }
}

void
BinarySearchTree2::makeEmpty(SecuBinaryNode * &node) {
    if (node != NULL) {
        makeEmpty((SecuBinaryNode *&)node->left);
        makeEmpty((SecuBinaryNode *&)node->right);

        delete node;
        node = NULL;
    }
}

void
BinarySearchTree2::traversal (const SecuBinaryNode * &node, ostringstream & out)
    const {
    if (node==NULL)
        return;

    if (node->left) {
        traversal((const SecuBinaryNode *&)node->left, out);
    }

    if (node) {
        out << node->elm << ",";
    }

    if (node->right) {
        traversal((const SecuBinaryNode *&)node->right, out);
    }
}

SecuBinaryNode *
BinarySearchTree2::clone(const SecuBinaryNode * &node, SecuBinaryNode * pNode)
    const {
    SecuBinaryNode * temp = new SecuBinaryNode(node->elm, NULL, NULL, pNode);

    if (node->left != NULL)
        temp->left  = clone((const SecuBinaryNode *&)node->left, temp);

    if (node->right != NULL)
        temp->right = clone((const SecuBinaryNode *&)node->right, temp);

    return temp;
}

// 这个方法里，仅仅维护父节点的正确性
// 对于双子节点，再替换完成后最后的地方取处理
// 如果放在此方法中处理，可能会在删除时造成死循环
void
BinarySearchTree2::transplant(SecuBinaryNode * &node1,
        SecuBinaryNode * &node2) {
    if (node1 == node2)
        return;

    SecuBinaryNode * tmpNode  = node1;

    if (node1->parent == NULL) {
        root = node2;
    } else if (node1->parent->left == node1) {
        node1->parent->left =node2;
    } else {
        node1->parent->right=node2;
    }

    if (node2!=NULL)
        node2->parent = tmpNode->parent;
}
/*
int main() {
    BinarySearchTree2 * tree = new BinarySearchTree2();
    tree->insert(1130);
    tree->insert(1120);
    tree->insert(1140);
    tree->insert(1110);
    tree->insert(1125);
    tree->insert(1135);
    tree->insert(1150);
    tree->insert(1115);
    tree->insert(1115);
    tree->insert(1128);
    tree->insert(1141);

    cout << "Print tree:"<<endl;
    //tree->printfTree(cout);
    printPretty(tree->root, 4, 0, cout);

    //tree->remove(115);

    tree->remove(1130);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1120);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1115);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1110);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1150);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1141);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1140);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1128);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1125);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1135);
    printPretty(tree->root, 4, 0, cout);
    tree->remove(1115);
    printPretty(tree->root, 4, 0, cout);


    cout << "After remove root item:" <<endl;
    //tree->printfTree(cout);
    printPretty(tree->root, 4, 0, cout);

    tree->makeEmpty();

    return 0;

}*/
