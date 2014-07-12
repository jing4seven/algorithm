/*******************************************************************************
 图(邻接表实现)

 有两种构造方式，一种是利用map， 将定点作为Key, 将邻接表（GNode的链表）作为
 Value；另外一种方式是直接将邻接表作为图类的成员；
*******************************************************************************/
#ifndef ALG_GRAPH_H
#define ALG_GRAPH_H

#include <list>
#include <set>

using namespace std;

template <typename T>
class GNode {
public:
    T data;
    set<GNode<T>*> adjacent;
    GNode(T d): data(d), adjacent(){
    };
};

template <typename T>
class Graph {
public:
    int vcount; // Vertex顶点数
    int ecount; // Edge 边数
    list<GNode<T>*> adjacents;

    Graph(): vcount(0), ecount(0), adjacents() {
    }
    Graph(const list<GNode<T> > adj);
    void insert_vertex(const T data);
    void insert_edge(const T s, const T e);
    void remove_vertex(const T data);
    void remove_edge(const T s, const T e);
    set<GNode<T>*> get_adjacent(const T s) const;
private:
    GNode<T> * get_vertex(const T data) const;
    void remove_adjacent(set<GNode<T>*> & adjacent, const T adjdata);
};

#endif
