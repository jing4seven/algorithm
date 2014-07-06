## 树的定义

### 基类
对于本章节中所有二叉树中节点的定义，都以如下`BinaryNode`类作为基类进行扩展，如Search Binary Tree的node会添加`parent`属性，而AVL Tree的node还会添加height字段等。

<pre><code>

class BinaryNode {
public:
    // 基于简单起见，暂且用int代表数据，如果有需要
    // 也可以用compareable的泛型对象来实现
    int elm;

    BinaryNode * left;  // 左子节点
    BinaryNode * right; // 右子节点

    // 构造函数
    BinaryNode(const int & theElm, BinaryNode * l,
            BinaryNode * r): elm(theElm), left(l), right(r){};
};

</code></pre>

### 方法

几乎所有的二叉树的的实现都包含如下公共方法。

<pre><code>

BinaryTree();
BinaryTree(BinaryTree & tree);
~BinaryTree();

int findMin() const;
int findMax() const;

bool contains(const int data) const;
bool isEmpty() const;
void makeEmpty();

void insert(const int data);
void remove(const int data);

BinaryTree &  operator=(const BinaryTree & tree);

BinaryNode * root;
</code></pre>

有的私有方法和公共方法有同样的方法名，但是其方法签名不一样，主要是对具体节点的操作。

<pre><code>

// 找到node节点中最小的节点
BinaryNode * findMin(BinaryNode * node) const;
// 找到node节点中最大的节点
BinaryNode * findMax(BinaryNode * node) const;
bool contains(const BinaryNode * node, const int data) const;

void insert(BinaryNode * &node, const int data);
void remove(BinaryNode * &node, const int data);

void makeEmpty(BinaryNode * &node);
BinaryNode * clone(const BinaryNode * t) const;

</code></pre>

关于树的打印, 单独放在[printTree.h](https://github.com/jing4seven/algorithm/blob/master/tree/printTree.h)中定义，为了打印的方便，BinaryNode也放在这个文件中了。
