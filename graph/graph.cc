#include "graph.h"
#include <iostream>
#include <stdio.h>
#include <list>
#include <string>
#include <set>

/*
 * 所有的顶点是按照从小到大得顺序进行排列, 找到合适的位置，将带插入节点插入即可.
 */

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

////////////////////////////////////////////////////////////////////////////////
// public function
template <typename T>
void
Graph<T>::insert_vertex(const T data) {
    int adjcount = this->adjacents.size();

    GNode<T> * gnode = new GNode<T>(data);
    adjacents.push_back(gnode);
    adjacents.sort(comp_with_gnode<T>);
    adjacents.unique(dist_with_gnode<T>);

    if (adjcount < adjacents.size()) {
        this->vcount++;
    }
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

    this->ecount++;
}

template <typename T>
void
Graph<T>::remove_vertex(const T data) {
    GNode<T> * gnode, * adjnode;
    gnode = adjnode = NULL;

    typename list<GNode<T>*>::iterator niter = adjacents.begin();
    while (niter != adjacents.end() ) {
        gnode = (GNode<T> *)*niter;
        if (gnode && gnode->data == data) {
            break;
        }
        ++niter;
    }
    // 抹去当前节点的数据
    if (gnode == NULL || *niter == NULL) {
        return;
    }

    // 抹去其他节点到被删除节点的边
    typename list<GNode<T>*>::iterator iter = adjacents.begin();

    // 遍历邻接表，将所有包含data节点的边都删除
    while (iter != adjacents.end()) {
        //adjnode = (GNode<T> *)*iter;

        if (*iter != NULL) {
            remove_adjacent((*iter)->adjacent, data);
        }
        ++iter;
    }

    set<GNode<T>*> gadjacent = gnode->adjacent;
    // 清空邻接表之前记得要同步边的数量
    this->ecount = this->ecount - gadjacent.size();
    gadjacent.clear();

    adjacents.erase(niter);

    this->vcount--;
}

template <typename T>
void
Graph<T>::remove_edge(const T s, const T e) {
    GNode<T> * gnode = get_vertex(s);

    if (gnode == NULL) {
        return;
    }

    remove_adjacent(gnode->adjacent, e);
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
    typename list<GNode<T>*>::const_iterator iter = adjacents.begin();
    GNode<T> * gnode = NULL;
    while (iter != adjacents.end() ) {
        gnode = (GNode<T> *)*iter;
        if (gnode && gnode->data == data) {
            return gnode;
        }
        ++iter;
    }
    return NULL;
}

template <typename T>
void
Graph<T>::remove_adjacent(set<GNode<T>*> &adjacent, const T adjdata) {
    if (adjacent.size() <=0) {
        return;
    }

    typename set<GNode<T>*>::iterator iter = adjacent.begin();
    while (iter!=adjacent.end()) {
        if ((*iter)->data == adjdata) {
            break;
        }
        ++iter;
    }

    if (iter!=adjacent.end()) {
        adjacent.erase(iter);
        this->ecount--;
    }
}

////////////////////////////////////////////////////////////////////////////////
// local test function
int main(void) {
    Graph<string> * graph = new Graph<string>();

    graph->insert_vertex("D");
    graph->insert_vertex("C");
    graph->insert_vertex("A");
    graph->insert_vertex("E");
    graph->insert_vertex("B");
    graph->insert_vertex("F");
    graph->insert_vertex("G");
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

    //list<GNode<string>*> adjs = graph->adjacents;

    list<GNode<string>*>::iterator iter = graph->adjacents.begin();
    set<GNode<string>*>::iterator adjiter;

    while (iter != graph->adjacents.end()) {
        cout <<  (string)(*iter)->data << endl;

        adjiter =(&(*iter)->adjacent)->begin();
        while (adjiter != (&(*iter)->adjacent)->end()) {
            cout << "\t" << (*adjiter)->data << endl;
            ++adjiter;
        }
        ++iter;
    }

    cout << "vcount:" << graph->vcount << endl;
    cout << "ecount:" << graph->ecount << endl;

    cout << "--------------------" << endl;

    graph->remove_vertex("A");
    graph->remove_vertex("C");

    graph->remove_edge("E", "D");

    iter = graph->adjacents.begin();

    while (iter != graph->adjacents.end()) {
        cout <<  (string)(*iter)->data << endl;

        adjiter =(&(*iter)->adjacent)->begin();
        while (adjiter != (&(*iter)->adjacent)->end()) {
            cout << "\t" << (*adjiter)->data << endl;
            ++adjiter;
        }
        ++iter;
    }

    cout << "vcount:" << graph->vcount << endl;
    cout << "ecount:" << graph->ecount << endl;
    cout << "--------------------" << endl;
    return 0;
}

