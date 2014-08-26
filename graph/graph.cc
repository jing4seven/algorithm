#include "graph.h"
#include <iostream>
#include <stdio.h>
/*
 * 所有的顶点是按照从小到大得顺序进行排列, 找到合适的位置，将带插入节点插入即可.
 */

////////////////////////////////////////////////////////////////////////////////
// public function
template <typename T>
void
Graph<T>::insert_vertex(GNode<T> * gnode) {
    if (gnode == NULL) {
        return;
    }

    int adjcount = this->adjacents.size();

    adjacents.push_back(gnode);
    //adjacents.sort(comp_with_gnode<T>);
    adjacents.unique(dist_with_gnode<T>);

    if (adjcount < adjacents.size()) {
        this->vcount++;
    }
}

template <typename T>
void
Graph<T>::insert_edge(GNode<T> * snode, GNode<T> * enode) {
    if (snode == NULL || enode == NULL) {
        return;
    }

    typename list<GNode<T> *>::iterator siter, eiter;
    GNode<T> * sgnode,  * egnode;

    siter = this->adjacents.begin();
    // 如果两个顶点都不存在，即退出
    while (siter != adjacents.end()) {
        sgnode = (GNode<T> *)*siter;

        if (sgnode->data == snode->data) {
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

        if (egnode->data == enode->data) {
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
Graph<T>::remove_vertex(GNode<T> * gnode) {
    GNode<T> * tempNode, * adjnode;
    adjnode = NULL;

    if (gnode == NULL) {
        return;
    }

    // 查找gnode是否在图中
    typename list<GNode<T>*>::iterator niter = adjacents.begin();
    while (niter != adjacents.end() ) {
        tempNode= (GNode<T> *)*niter;
        if (tempNode &&  tempNode->data == gnode->data) {
            break;
        }
        ++niter;
    }

    // 抹去当前节点的数据
    if (tempNode== NULL) {
        return;
    }

    // 抹去其他节点到被删除节点的边
    typename list<GNode<T>*>::iterator iter = adjacents.begin();

    // 遍历邻接表，将所有包含data节点的边都删除
    while (iter != adjacents.end()) {

        if (*iter != NULL) {
            remove_adjacent((*iter)->adjacent, gnode);
        }
        ++iter;
    }

    set<GNode<T>*> gadjacent = tempNode->adjacent;
    // 清空邻接表之前记得要同步边的数量
    this->ecount = this->ecount - gadjacent.size();
    gadjacent.clear();

    adjacents.erase(niter);

    this->vcount--;
}

template <typename T>
void
Graph<T>::remove_edge(GNode<T> * snode, GNode<T> * enode) {
    if (snode == NULL) {
        return;
    }

    remove_adjacent(snode->adjacent, enode);
}

////////////////////////////////////////////////////////////////////////////////
// private function

/*
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
}*/

template <typename T>
void
Graph<T>::remove_adjacent(set<GNode<T>*> &adjacent, GNode<T> * gnode) {
    if (adjacent.size() <=0 || gnode == NULL) {
        return;
    }

    typename set<GNode<T>*>::iterator iter = adjacent.begin();
    while (iter!=adjacent.end()) {
        if ((*iter)->data == gnode->data) {
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
/*
int main(void) {
    Graph<string> * graph = new Graph<string>();

    GNode<string> * n1 = new GNode<string>("A");
    GNode<string> * n2 = new GNode<string>("B");
    GNode<string> * n3 = new GNode<string>("C");
    GNode<string> * n4 = new GNode<string>("D");
    GNode<string> * n5 = new GNode<string>("E");
    GNode<string> * n6 = new GNode<string>("F");
    GNode<string> * n7 = new GNode<string>("G");

    graph->insert_vertex(n1);
    graph->insert_vertex(n2);
    graph->insert_vertex(n3);
    graph->insert_vertex(n4);
    graph->insert_vertex(n5);
    graph->insert_vertex(n6);
    graph->insert_vertex(n7);

    graph->insert_edge(n1, n2);
    graph->insert_edge(n1, n4);
    graph->insert_edge(n1, n3);

    graph->insert_edge(n2, n4);
    graph->insert_edge(n2, n5);

    graph->insert_edge(n3, n6);

    graph->insert_edge(n4, n6);
    graph->insert_edge(n4, n7);
    graph->insert_edge(n4, n3);

    graph->insert_edge(n5, n4);
    graph->insert_edge(n5, n7);

    graph->insert_edge(n7, n6);

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

    graph->remove_vertex(n1);
    graph->remove_vertex(n3);

    graph->remove_edge(n5, n4);

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
}*/

