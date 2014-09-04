/*******************************************************************************
  最小生成树

  问题：
  一个连通无向图, 带权值， 找到一个无环子集，能将所有的节点都连接起来，但是同时
  具有最小的权值，这样得到一个树就是最小生成树；

*******************************************************************************/

#include "graph_matrix.cc"
#include <iostream>
#include <stdio.h>
#include <map>
#include <algorithm>

// 存放矩阵坐标的对象
class NodePosition{
public:
    int x;
    int y;

    NodePosition(int a, int b) : x(a), y(b) {};
};

// 获取二进制位的长度
int check_bit_count(int n) {
    return n ? check_bit_count(n>>1) + 1 : 0;
}

// 获取二进制位中1的个数
int check_pos_bit_count(int n) {
    int c(check_bit_count(n)-1), val(0);
    while (c>=0) {
        val = val + (0x1 << c & n ? 1 : 0);
        --c;
    }
    return val;
}

template <typename T>
void
kruskal_mst(Graph<T> * graph) {
    if (graph == NULL) {
        return;
    }

    // 定义一个计数器，记录累加权值
    int priorities = 0;

    // 定义一个节点索引集合，记录已经加入的节点
    int bit_count = 0x0;

    // 定义一个存放排序结构的关联表
    multimap<int, NodePosition*> sortedEdgs;

    // 初始化关联表
    for (int i=0; i< graph->vcount; ++i) {
        for (int j=0; j< graph->vcount; ++j) {
            if (graph->matrixs[i][j] < INFINITE) {
                NodePosition * tmppos = new NodePosition(i,j);
                sortedEdgs.insert(
                        pair<int, NodePosition*>(graph->matrixs[i][j], tmppos));
            }
        }
    }

    // 将所有的边按照权值从小到大排序
    // map默认就是按照Key从小到大排序的

    // 循环按权值排序过的边，如果边的两个点分别属于不同的树，
    // 就将权值累加到计数器，并把节点加入节点记录器
    // 判断是否集合中已经包含所有的节点，如果是，完毕， 不是就继续
    multimap<int, NodePosition*>::const_iterator miter = sortedEdgs.begin();
    while (miter != sortedEdgs.end() ) {

        int  x = (*miter).second->x;
        int  y = (*miter).second->y;

        if  (!(bit_count & (0x1<< x)) || !(bit_count & (0x1<< y)) ) {
            cout << "x,y:"<< x << "," << y<< endl;
            bit_count = bit_count | (0x1<< x);
            bit_count = bit_count | (0x1<< y);
            priorities+= miter->first;
        }

        ++miter;
    }
    cout << "priorities:" << priorities << endl;
}

int main(void) {
    Graph<string> * graph = new Graph<string>();
    GNode<string> * na = new GNode<string>("A");
    GNode<string> * nb = new GNode<string>("B");
    GNode<string> * nc = new GNode<string>("C");
    GNode<string> * nd = new GNode<string>("D");
    GNode<string> * ne = new GNode<string>("E");
    GNode<string> * nf = new GNode<string>("F");
    GNode<string> * ng = new GNode<string>("G");
    GNode<string> * nh = new GNode<string>("H");
    GNode<string> * ni = new GNode<string>("I");

    graph->insert_vertex(na);
    graph->insert_vertex(nb);
    graph->insert_vertex(nc);
    graph->insert_vertex(nd);
    graph->insert_vertex(ne);
    graph->insert_vertex(nf);
    graph->insert_vertex(ng);
    graph->insert_vertex(nh);
    graph->insert_vertex(ni);

    graph->insert_edge(na, nb, 4);
    graph->insert_edge(nb, nc, 8);
    graph->insert_edge(nc, nd, 7);
    graph->insert_edge(nd, ne, 9);
    graph->insert_edge(ne, nf, 10);
    graph->insert_edge(nf, ng, 4);
    graph->insert_edge(nf, nd, 14);
    graph->insert_edge(nf, nc, 2);
    graph->insert_edge(nc, ni, 2);
    graph->insert_edge(ng, ni, 6);
    graph->insert_edge(ng, nh, 1);
    graph->insert_edge(nh, nb, 11);
    graph->insert_edge(nh, ni, 7);
    graph->insert_edge(nh, na, 8);

    graph->insert_edge(nb, na, 4);
    graph->insert_edge(nc, nb, 8);
    graph->insert_edge(nd, nc, 7);
    graph->insert_edge(ne, nd, 9);
    graph->insert_edge(nf, ne, 10);
    graph->insert_edge(ng, nf, 2);
    graph->insert_edge(nd, nf, 14);
    graph->insert_edge(nc, nf, 4);
    graph->insert_edge(ni, nc, 2);
    graph->insert_edge(ni, ng, 6);
    graph->insert_edge(nh, ng, 1);
    graph->insert_edge(nb, nh, 11);
    graph->insert_edge(ni, nh, 7);
    graph->insert_edge(na, nh, 8);
/*
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

    cout << "_______________" << endl;
    cout << graph->matrixs[0][0] << endl;
*/
    kruskal_mst(graph);

    return 0;
}

