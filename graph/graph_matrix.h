/*******************************************************************************
 图(邻接矩阵实现)

*******************************************************************************/
#ifndef ALG_GRAPH_MATRIX_H
#define ALG_GRAPH_MATRIX_H

#include <list>
#include <vector>
#include <string>
#include <map>

using namespace std;

#define BASIC_CAPACITY  5

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

    void insert_vertex(const GNode<T> * node);
    void insert_edge(const GNode<T> * snode, const GNode<T> * enode);
    void remove_vertex(GNode<T> * node);
    void remove_edge(GNode<T> * snode, GNode<T> * enode);
private:
    int matrixs_capacity; // 记录矩阵真实容量
    map<T, int> idxmap;     // 记录data与矩阵索引的匹配关系
    int allocate_matrixs();
    bool check_if_vertex_exists(const GNode<T>* & node, int & idx) const;
    /*void remove_adjacent(set<GNode<T>*> &adjacent, GNode<T> * n);*/
};

//template <typename T>
//bool
//dist_with_gnode(GNode<T> * ln, GNode<T> * rn) {
    //return ln->data == rn->data;
//}

//template <typename T>
//bool
//comp_with_gnode(GNode<T> * ln, GNode<T> * rn) {
    //return ln->data < rn->data;
/*}*/


#endif // ALG_GRAPH_MATRIX_H
