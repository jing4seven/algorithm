/*******************************************************************************
 图(邻接矩阵实现)

 特征：
 1. 有向图，可以有环可以无环；
 2. 可以带权
 3. 暂时没有实现环路检测，可以在矩阵中检测matrixs[i][j] == matrixs[j][i] &&
    matrixs[i][j] != INFINITE, 来判断实现

*******************************************************************************/
#ifndef ALG_GRAPH_MATRIX_H
#define ALG_GRAPH_MATRIX_H

#include <list>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <exception>
#include <new>

using namespace std;

#define BASIC_CAPACITY  5
#define INFINITE        ~(1<<(sizeof(int)*8-1))

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class GNode {
public:
    T data;
    GNode(T d): data(d){};
};

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class comp_gnode{
    const GNode<T> * local;
public:
    comp_gnode(const GNode<T> * l) : local(l) {}
    bool operator()(const GNode<T> * n) const {
        return local->data == n->data;
    }
};

template <>
class comp_gnode<string>{
    const GNode<string> * local;
public:
    comp_gnode(const GNode<string> * l) : local(l) {}
    bool operator()(const GNode<string> * n) const {
        return local->data.compare(n->data) == 0;
    }
};

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Graph {
public:
    int vcount; // Vertex顶点数
    int ecount; // Edge 边数
    int **matrixs;
    vector<GNode<T>* > vertexs;

    Graph();
    ~Graph();

    void insert_vertex(const GNode<T> * node);
    void insert_edge(const GNode<T> * snode, const GNode<T> * enode, int priority);
    void remove_vertex(GNode<T> * node);
    void remove_edge(GNode<T> * snode, GNode<T> * enode);
private:
    int matrixs_capacity; // 记录矩阵真实容量
    map<T, int> idxmap;     // 记录data与矩阵索引的匹配关系
    int allocate_matrixs();
    bool check_if_vertex_exists(const GNode<T>* & node, int & idx) const;
};

#endif // ALG_GRAPH_MATRIX_H
