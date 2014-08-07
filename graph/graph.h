/*******************************************************************************
 图(邻接表实现)

 有两种构造方式，一种是利用map， 将定点作为Key, 将邻接表（GNode的链表）作为
 Value；另外一种方式是直接将邻接表作为图类的成员；
*******************************************************************************/
#ifndef ALG_GRAPH_H
#define ALG_GRAPH_H

#include <list>
#include <set>
#include <string>

using namespace std;

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

    void insert_vertex(const GNode<T> * node);
    void insert_edge(const GNode<T> * snode, const GNode<T> * enode);
    void remove_vertex(GNode<T> * node);
    void remove_edge(GNode<T> * snode, GNode<T> * enode);
private:
    void remove_adjacent(set<GNode<T>*> &adjacent, GNode<T> * n);

};

template <typename T>
bool
dist_with_gnode(GNode<T> * ln, GNode<T> * rn) {
    return ln->data == rn->data;
}

template <typename T>
bool
comp_with_gnode(GNode<T> * ln, GNode<T> * rn) {
    return ln->data < rn->data;
}

#endif //ALG_GRAPH_H
