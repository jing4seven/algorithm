#include <iostream>
#include "graph_matrix.h"
#include <iomanip> // for setw

////////////////////////////////////////////////////////////////////////////////
template <typename T>
Graph<T>::Graph():vcount(0), ecount(0) {
    // 给矩阵分配基础空间
    matrixs = new int *[BASIC_CAPACITY];

    for (int i =0; i<BASIC_CAPACITY; ++i) {
        matrixs[i] = new int[BASIC_CAPACITY];
        // 将矩阵的值都填充为 INFINITE
        fill_n(matrixs[i], BASIC_CAPACITY, INFINITE);
    }

    matrixs_capacity= BASIC_CAPACITY;
}

template <typename T>
Graph<T>::~Graph() {
    // 删除矩阵的空间
    for (int i=0; i< matrixs_capacity; ++i) {
        delete [] matrixs[i];
    }
    delete [] matrixs;

    // 删除节点所指向的存储空间
    typename vector<GNode<T> *>::iterator iter = vertexs.begin();

    while (iter != vertexs.end()) {
        delete (*iter);
        ++iter;
    }
    vertexs.clear();

    // 清空匹配表
    idxmap.clear();
}

////////////////////////////////////////////////////////////////////////////////

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
Graph<T>::insert_edge(const GNode<T> * snode, const  GNode<T> * enode, int priority=1) {
    // 检查两个节点是否已经在图上
    int sidx(-1), eidx(-1);
    if (check_if_vertex_exists(snode, sidx) == false ||
            check_if_vertex_exists(enode, eidx) == false) {
        return;
    }

    // 将值存放到矩阵中
    if (sidx >=0 && eidx >=0 && matrixs[sidx][eidx] != 1) {
        matrixs[sidx][eidx] = priority;
        // 更新边计数器
        ecount++;
    }
}
template <typename T>
void
Graph<T>::remove_vertex(GNode<T> * node) {
    int idx(-1);

    // 检查此节点是否存在
    if (check_if_vertex_exists((const GNode<T> * &)node, idx) == false) {
        return;
    }

    // 删除节点涉及的所有边，并更新图的边数量；
    for (int i=0; i<vcount; ++i) {
        if (matrixs[idx][i] != INFINITE) {
            matrixs[idx][i] = INFINITE;
            --ecount;
        }
    }

    for (int i=0; i<vcount; ++i) {
        if (matrixs[i][idx] != INFINITE) {
            matrixs[i][idx] = INFINITE;
            --ecount;
        }
    }

    // 压缩矩阵
    for (int i=idx; i<vcount-1; ++i) {
        for (int j=0; j<vcount; ++j) {
            matrixs[i][j] = matrixs[i+1][j];
        }
    }

    for (int j=idx; j<vcount-1; ++j) {
        for (int i=0; i<vcount; ++i) {
            matrixs[i][j] = matrixs[i][j+1];
        }
    }

    // 删除节点
    typename vector<GNode<T> *>::iterator iter = vertexs.begin();
    iter+=idx;
    cout << (*iter)->data << endl;
    delete (*iter);
    vertexs.erase(iter);
    --vcount;

    // 删除点边映射关系
   idxmap.erase(node->data);
}

template <typename T>
void
Graph<T>::remove_edge(GNode<T> * snode, GNode<T> * enode) {
    int sidx(-1), eidx(-1);
    // 检查两个节点是否都存在，任意一个不存在即退出
    if (check_if_vertex_exists((const GNode<T> *&)snode, sidx) == false ||
            check_if_vertex_exists((const GNode<T> *&)enode, eidx) == false) {
        return;
    }

    // 在矩阵上删除边, 并更新边数量
    if (matrixs[sidx][eidx]) {
        matrixs[sidx][eidx] = INFINITE;
        --ecount;
    }
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
            fill_n(matrixs[i], tmp_capacity, INFINITE);
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
// local test function
/*
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

    graph->insert_edge(na, nb, 5);
    graph->insert_edge(na, ne, 4);
    graph->insert_edge(ne, nd, 3);
    graph->insert_edge(nf, nb, 2);

    cout << "graph->vcount:" << graph->vcount << endl;
    cout << "graph->ecount:" << graph->ecount << endl;

    cout << "vertexs:" << endl;;
    for (int i=0; i<(graph->vertexs).size(); ++i) {
        cout << setw(15) << graph->vertexs[i]->data;
    }
    cout << endl;

    cout << "matrixs:" << endl;
    for (int i=0; i<graph->vcount; ++i) {
        for (int j=0; j<graph->vcount; ++j) {
            cout << setw(15) << graph->matrixs[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "____after do remove vertex___" << endl;

    //graph->remove_vertex(na);
    graph->remove_edge(nf, nb);
    graph->remove_edge(na, nb);
    cout << "graph->vcount:" << graph->vcount << endl;
    cout << "graph->ecount:" << graph->ecount << endl;

    cout << "vertexs:" << endl;
    for (int i=0; i<graph->vertexs.size(); ++i) {
        cout << setw(15) << graph->vertexs[i]->data;
    }
    cout << endl;

    cout << "matrixs:" << endl;
    for (int i=0; i<graph->vcount; ++i) {
        for (int j=0; j<graph->vcount; ++j) {
            cout << setw(15) << graph->matrixs[i][j];
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}*/
