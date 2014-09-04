/*******************************************************************************
  最小生成树

  问题：
  一个连通无向图, 带权值， 找到一个无环子集，能将所有的节点都连接起来，但是同时
  具有最小的权值，这样得到一个树就是最小生成树；

  prim 算法：
  开始随便选取一个顶点作为起始点，然后迭代找出次节点与其他节点最小权重的那条边，
  随机将其加入到最小生成树中，如果产生环路则跳过，选择下一个顶点。当所有的节点
  都加入到最小生成树之后，所求即完成。
*******************************************************************************/

#include "graph_matrix.cc"
#include <iostream>
#include <stdio.h>
#include <map>
#include <algorithm>


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
process(const Graph<T> * graph, int bit_count, int  &tmp_priority,
        int &x, int &y){
    int len = graph->vcount;
    int posmap[len], m(0), n(0);

    // 找出bit_count中记录的所有节点
    while (n<len) {
        if ((bit_count & (0x1 << n))) {
            posmap[n] = 1;
        }
        ++n;
    }
    // 计算记录的每个节点的临界点，找到最小的那条
    n = 0;
    while (n<len) {
        if (posmap[n] == 1) {
            m = 0;
            while (m < graph->vcount) {
                if (!(bit_count & (0x1 << m)) && tmp_priority > graph->matrixs[n][m]) {
                    tmp_priority = graph->matrixs[n][m];
                    // 更新y
                    x = n;
                    y = m;
                }
                ++m;
            }
        }
        ++n;
    }
}

template <typename T>
void
prim_mst(Graph<T> * graph) {
    if (graph == NULL) {
        return;
    }

    // 定义一个计数器，记录累加权值
    int priorities = 0;

    // 定义一个节点索引集合，记录已经加入的节点
    int bit_count = 0x0;

    // 遍历所有的顶点，对每个顶点的所有边进行比较，取最小的加入最小生成树
    // 当所有的节点都已经被加入，即完成
    int x(0);
    //while (i< graph->vcount && chktag < graph->vcount) {
    bit_count = bit_count | (0x1 << x);
    while (check_pos_bit_count(bit_count) < graph->vcount) {
        int tmp_priority(INFINITE), y(-1);

        process((const Graph<T> *)graph, bit_count, tmp_priority, x, y);
        //cout << "--------------------x,y:" << x<<","<<y << endl;
        if (y >= 0) {
            bit_count = bit_count | (0x1 << y);
        //cout << "priorities:"<< priorities << endl;
            priorities += tmp_priority;
        }
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
    graph->insert_edge(nf, ng, 2);
    graph->insert_edge(nf, nd, 14);
    graph->insert_edge(nf, nc, 4);
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
    //cout << graph->matrixs[0][0] << endl;

    prim_mst(graph);

    return 0;
}
