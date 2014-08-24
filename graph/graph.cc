#include "graph.h"
#include <iostream>
#include <stdio.h>
#include <list>
#include <string>
#include <set>

using namespace std;

/*
 * 所有的顶点是按照从小到大得顺序进行排列, 找到合适的位置，将带插入节点插入即可.
 */

////////////////////////////////////////////////////////////////////////////////
// public function
template <typename T>
void
Graph<T>::insert_vertex(const T data) {
    typename list<GNode<T> *>::iterator iter = adjacents.begin();
    GNode<T> * gnode = NULL;
    // ToDo: 修改为二分搜索
    while (iter != adjacents.end() ) {
        gnode = (GNode<T> *)*iter;
        if (gnode->data == data) {
            return;
        } else if (gnode->data < data) {
            break;
        } else {
            ++iter;
        }
    }

    gnode = new GNode<T>(data);
    this->adjacents.insert(--iter, gnode);
    this->vcount++;
}

template <typename T>
void
Graph<T>::insert_edge(const T s, const T e) {
    typename list<GNode<T> *>::iterator siter, eiter;
    GNode<T> * sgnode,  * egnode;

    siter = this->adjacents.begin();
    // 如果两个顶点都不存在，即退出
    while (siter != adjacents.end()) {
        sgnode = (GNode<T> *)*siter;

        if (sgnode->data == s) {
            break;
        }
        ++siter;
    }

    if (*siter == NULL) {
        return;
    }

    eiter = adjacents.begin();
    while (eiter != adjacents.end()) {
        egnode = (GNode<T> *)*eiter;

        if (egnode->data == e) {
            break;
        }
        ++eiter;
    }

    if (*eiter == NULL) {
        return;
    }

    sgnode = (GNode<T> *)*siter;
    egnode = (GNode<T> *)*eiter;

    sgnode->adjacent.insert(egnode);

    this->vcount++;
}

template <typename T>
void
Graph<T>::remove_vertex(const T data) {
    GNode<T> * gnode, adjnode;
    gnode = adjnode = NULL;

    // 抹去当前节点的数据
    if ((gnode = get_vertex(data)) == NULL) {
        return;
    }

    set<GNode<T> > * gadjacent = gnode->adjacent;

    // 抹去其他节点到被删除节点的边
    typename list<GNode<T> >::iterator iter = adjacents.begin();

    // 遍历邻接表，将所有包含data节点的边都删除
    while (iter != adjacents.end()) {
        adjnode = (GNode<T> *)iter;

        if (iter != NULL) {
            remove_adjacent(adjnode, data);
            this->vcount--;
        }
        ++iter;
    }

    delete gadjacent;
    delete gnode;

    this->ecount--;
}

template <typename T>
void
Graph<T>::remove_edge(const T s, const T e) {

    this->vcount--;
}

template <typename T>
set<GNode<T>*>
Graph<T>::get_adjacent(const T data) const {
    GNode<T> * gnode = NULL;

    if ((gnode = get_vertex(data)) != NULL) {
        return gnode->adjacent;
    }

    return NULL;
}
////////////////////////////////////////////////////////////////////////////////
// private function
template <typename T>
GNode<T> *
Graph<T>::get_vertex(const T data) const {
    typename list<GNode<T> >::iterator iter = adjacents.begin();
    GNode<T> * gnode = NULL;
    while (iter != adjacents.end() ) {
        gnode = (GNode<T> *)iter;
        if (gnode && gnode->data == data) {
            return gnode;
        }
        ++iter;
    }
    return NULL;
}

template <typename T>
void
Graph<T>::remove_adjacent(const GNode<T> * cnode, const T adjdata) {
    if (cnode == NULL) {
        return;
    }

    set<GNode<T> > * adj = cnode->adjacent;

    if (adj == NULL) {
        return;
    }

    typename set<GNode<T> >::iterator iter = NULL;

    iter = adj->find(adjdata);

    if (iter != NULL ) {
        adj->erase(iter);
    }
}

////////////////////////////////////////////////////////////////////////////////
// local test function
int main(void) {
    Graph<string> * graph = new Graph<string>();

    graph->insert_vertex("A");
    graph->insert_vertex("B");
    graph->insert_vertex("C");
    graph->insert_vertex("D");
    graph->insert_vertex("E");
    graph->insert_vertex("F");
    graph->insert_vertex("G");

    graph->insert_edge("A", "B");
    graph->insert_edge("A", "D");
    graph->insert_edge("A", "C");

    graph->insert_edge("B", "D");
    graph->insert_edge("B", "E");

    graph->insert_edge("C", "F");

    graph->insert_edge("D", "F");
    graph->insert_edge("D", "G");
    graph->insert_edge("D", "C");

    graph->insert_edge("E", "D");
    graph->insert_edge("E", "G");

    graph->insert_edge("G", "F");

    list<GNode<string>*> adjs = graph->adjacents;

    list<GNode<string>*>::const_iterator iter = adjs.begin();
    set<GNode<string>*>::const_iterator adjiter;
    set<GNode<string>*> * adjtemp;

    while (iter != adjs.end()) {
        cout <<  (string)(*iter)->data << endl;

        adjtemp = &(*iter)->adjacent;
        adjiter = adjtemp->begin();
        while (adjiter != adjtemp->end()) {
            cout << "\t" << (*adjiter)->data << endl;
            ++adjiter;
        }
        ++iter;
    }

    return 0;
}

