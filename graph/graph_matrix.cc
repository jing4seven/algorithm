#include <stdio.h>
#include <iostream>
#include <exception>
#include <new>
#include "graph_matrix.h"

template <typename T>
Graph<T>::Graph():vcount(0), ecount(0) {
    // 给矩阵分配基础空间
    matrixs = new int *[BASIC_CAPACITY];

    for (int i =0; i<BASIC_CAPACITY; ++i) {
        matrixs[i] = new int[BASIC_CAPACITY];
    }

    matrixs_capacity= BASIC_CAPACITY;
}

template <typename T>
void
Graph<T>::insert_vertex(const GNode<T> * node) {
    int idx = -1;
    // 查看是否已经存在，如果存在就直接返回，不存在就插入
    if (check_if_vertex_exists(node, idx) == true){
        return;
    }

    // 检查空间, 不够就扩容
    if (matrixs_capacity-vcount ==1) {
        allocate_matrixs();
    }

    vertexs.push_back((GNode<T>*)node);

    // 记录映射关系
    idxmap.insert(make_pair(node->data, vcount));
    vcount++;
}

template <typename T>
void
Graph<T>::insert_edge(const GNode<T> * snode, const  GNode<T> * enode) {
    // 检查两个节点是否已经在图上
    int sidx(-1), eidx(-1);
    if (check_if_vertex_exists(snode, sidx) == false ||
            check_if_vertex_exists(enode, eidx) == false) {
        cout << "return" << endl;
        return;
    }

    // 将值存放到矩阵中
    if (sidx >=0 && eidx >=0 && matrixs[sidx][eidx] != 1) {
        matrixs[sidx][eidx] = 1;
        // 更新边计数器
        ecount++;
    }
}
template <typename T>
void
remove_vertex(GNode<T> * node) {
    // ToDo
}

template <typename T>
void
remove_edge(GNode<T> * snode, GNode<T> * enode) {
    // ToDo
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
int
Graph<T>::allocate_matrixs() {
    int tmp_capacity = 2*matrixs_capacity;
    int tmp_matrixs[matrixs_capacity][matrixs_capacity];

    // 备份原始数据
    for (int i=0; i< matrixs_capacity; ++i) {
        for (int j=0; j<matrixs_capacity; ++j) {
            tmp_matrixs[i][j] = matrixs[i][j];
        }
    }

    // 删除旧的
    for (int i=0; i<matrixs_capacity; ++i) {
        delete [] matrixs[i];
    }
    delete [] matrixs;

    // 创建新的
    try {
        for (int i=0; i< tmp_capacity; ++i) {
            matrixs[i] = new int[tmp_capacity];
        }
    } catch (bad_alloc) {
        cout << "bad_alloc exception was raised." << endl;
        return 1;
    }

    // 还原就数据
    for (int i=0; i<matrixs_capacity; ++i) {
        for (int j=0; j<matrixs_capacity; ++j) {
            matrixs[i][j] = tmp_matrixs[i][j];
        }
    }

    // 更新容量
    matrixs_capacity = tmp_capacity;

    return 0;
}

template <typename T>
bool
Graph<T>::check_if_vertex_exists(const GNode<T>* & node, int & idx) const {

    bool result = false;
    if ( vertexs.end() !=
            find_if(vertexs.begin(), vertexs.end(),comp_gnode<T>(node) ) ) {
        result = true;
    }

    // 把索引值赋给idx
    typename map<T,int>::const_iterator iter;
    iter = idxmap.find(node->data);

    if (iter != idxmap.end()) {
        idx = iter->second;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
int main(void) {
    Graph<string> * graph = new Graph<string>();
    GNode<string> * na = new GNode<string>("A");
    GNode<string> * nb = new GNode<string>("B");
    GNode<string> * nc = new GNode<string>("C");
    GNode<string> * nd = new GNode<string>("D");
    GNode<string> * ne = new GNode<string>("E");
    GNode<string> * nf = new GNode<string>("F");

    graph->insert_vertex(na);
    graph->insert_vertex(nb);
    graph->insert_vertex(nc);
    graph->insert_vertex(nd);
    graph->insert_vertex(ne);
    graph->insert_vertex(nf);

    graph->insert_edge(na, nb);
    graph->insert_edge(na, nb);


    //cout << graph->vertexs.size() << endl;
    //cout << graph->vcount << endl;

    cout << graph->ecount << endl;

    cout << graph->matrixs[0][1] << endl;
    cout << graph->matrixs[1][0] << endl;

    return 0;
}
