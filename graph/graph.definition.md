## 图的定义

### 图的表示

通常来说，图G(V, E)有两种表示方式，`邻接表(Adjacent table)`和`邻接矩阵(Adjacent matrix)`。两种都可以表示有向图和无向图，但是对于稀疏图来说，临界表所占用的存储空间比邻接矩阵占用的要小，所以大部分情况下，图都采用邻接表来表示，但是，对于稠密图来说，两种方式占用空间差不多，此时可能更倾向于使用邻接矩阵。

### 基类

#### 邻接表的实现
```c++
template <typename T>
class GNode {
public:
    T data;
    set<GNode<T>*> adjacent;
    GNode(T d): data(d), adjacent(){
    };
    GNode operator==(GNode & gn) {
        if (gn.data == gn.data) {
            return true;
        } else {
            return false;
        }
    }
};

template <typename T>
class Graph {
public:
    int vcount; // Vertex顶点数
    int ecount; // Edge 边数
    list<GNode<T>*> adjacents;

    Graph(): vcount(0), ecount(0), adjacents() {
    }
    ~Graph();
};

```

#### 邻接矩阵的实现
```c++
template <typename T>
class GNode {
public:
    T data;
    GNode(T d): data(d){};
    GNode(GNode<T> * gn):data(gn->data) {};
};

template <typename T>
class Graph {
public:
    int vcount; // Vertex顶点数
    int ecount; // Edge 边数
    int **matrixs;
    vector<GNode<T>* > vertexs;

    Graph();
    ~Graph();
};
```

### API 

#### 邻接表的实现
```c++
    void insert_vertex(const GNode<T> * node);
    void insert_edge(const GNode<T> * snode, const GNode<T> * enode);
    void remove_vertex(GNode<T> * node);
    void remove_edge(GNode<T> * snode, GNode<T> * enode);
```
    
#### 邻接矩阵的实现
因为邻接矩阵自身就很容易实现带权值的图，所以仅仅只有`insert_edge`和邻接表的实现不同；
```c++
    // 邻接矩阵
    void insert_vertex(const GNode<T> * node);
    void insert_edge(const GNode<T> * snode, const GNode<T> * enode, int priority);
    void remove_vertex(GNode<T> * node);
    void remove_edge(GNode<T> * snode, GNode<T> * enode);
```
