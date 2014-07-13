## 图的定义

### 图的表示

通常来说，图G(V, E)有两种表示方式，`邻接表(Adjacent table)`和`邻接矩阵(Adjacent matrix)`。两种都可以表示有向图和无向图，但是对于稀疏图来说，临界表所占用的存储空间比邻接矩阵占用的要小，所以大部分情况下，图都采用邻接表来表示，但是，对于稠密图来说，两种方式占用空间差不多，此时可能更倾向于使用邻接矩阵。

### 基类


```c++
template <typename T>
class GNode {
public:
    T data;
    set<GNode<T>*> adjacent; // 邻接链表
    GNode(T d): data(d), adjacent(){
    };
};

template <typename T>
class Graph {
public:
    int vcount; // Vertex顶点数
    int ecount; // Edge 边数
    list<GNode<T>*> adjacents; // 存储节点指针的集合

    Graph(): vcount(0), ecount(0), adjacents() {
    }
};

```
### 方法
`Graph`的公共方法
```c++
    void insert_vertex(GNode<T> * node);
    void insert_edge(GNode<T> * snode, GNode<T> * enode);
    void remove_vertex(GNode<T> * node);
    void remove_edge(GNode<T> * snode, GNode<T> * enode);
```

`Graph`私有方法
```c++
    void remove_adjacent(set<GNode<T>*> &adjacent, GNode<T> * n);
```
