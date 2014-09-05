/*******************************************************************************
  最小生成树

  问题：
  一个连通无向图, 带权值， 找到一个无环子集，能将所有的节点都连接起来，但是同时
  具有最小的权值，这样得到一个树就是最小生成树；

  Gkruskal算法
  此算法需要利用“不相交集”概念，具体步骤为：
  1. 遍历每个节点，将每个节点变成一个不相交集，组成一个不相交集森林；
  2. 遍历每条边，如果边的两个节点不属于同一颗树，即将这两棵树合并；
  3. 最终将不相交森林合并成为一棵树，即最小生成树；如果最终不是一棵树，则说明图
    的所有节点没有完全连通;

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

template <typename T>
class SetTreeNode: public GNode<T> {
public:
    SetTreeNode * parent;
    int rank;
    SetTreeNode(GNode<T> * gn): parent(NULL), rank(0), GNode<T>(gn) {};
};

template <typename T>
void
make_set(list<SetTreeNode<T>*> & trees,  SetTreeNode<T> * n) {
    if ( n == NULL) {
        return;
    }

    trees.push_back(n);
}

template <typename T>
SetTreeNode<T> *
find_set(SetTreeNode<T> * &stn) {
    if (stn != stn->parent) {
        stn->parent = find_set(stn->parent);
    }

    return stn->parent;
}

template <typename T>
void
combine_set(list<SetTreeNode<T>*> &trees, SetTreeNode<T> * &a,
        SetTreeNode<T> * &b) {
    SetTreeNode<T> * ap = find_set(a);
    SetTreeNode<T> * bp = find_set(b);

    if ((ap->rank) < (bp->rank)) {
        ap->parent = bp;
        trees.remove(ap);
    } else {
        if (ap->rank == bp->rank){
            bp->parent = ap;
            ap->rank=+1;
        }
        trees.remove(bp);
    }
}

template <typename T>
void
kruskal_mst(Graph<T> * graph) {
    if (graph == NULL) {
        return;
    }

    // 定义一个计数器，记录累加权值
    int priorities = 0;

    // 定义一个不相交森林
    list<SetTreeNode<T> *> trees;

    // 定义一个映射表，可以通过GNode的指针找到SetTreeNode的指针
    map<GNode<T> *, SetTreeNode<T> *> nodemaps;

    // 定义一个存放排序结构的关联表
    multimap<int, NodePosition*> sortedEdgs;

    // 定义一个集合记录边
    //vector<pair<int, int> > minEdgs;

    // 遍历每个节点，创建不相交树森林
    typename vector<GNode<T> *>::iterator iter = graph->vertexs.begin();
    while (iter != graph->vertexs.end()) {

        SetTreeNode<T> * stn = new SetTreeNode<T>(*iter);
        stn->parent = stn;
        stn->rank = 0;

        nodemaps.insert(pair<GNode<T>*, SetTreeNode<T> *>(*iter, stn));
        make_set(trees, stn);
        ++iter;
    }

    // 闯将边长度和节点坐标的匹配映射表，并按照边权值从小到大排列
    for (int i=0; i< graph->vcount; ++i) {
        for (int j=0; j<= i; ++j) {
            if (graph->matrixs[i][j] < INFINITE) {
                NodePosition * tmppos = new NodePosition(i,j);
                sortedEdgs.insert(
                        pair<int, NodePosition*>(graph->matrixs[i][j], tmppos));
            }
        }
    }

    // 遍历每条边， 更新不相交集森林
    multimap<int, NodePosition*>::const_iterator miter = sortedEdgs.begin();
    while (miter != sortedEdgs.end() ) {
        // 得到坐标
        int x = miter->second->x;
        int y = miter->second->y;
        // 得到节点指针
        SetTreeNode<T> * ind = nodemaps[graph->vertexs[x]];
        SetTreeNode<T> * jnd = nodemaps[graph->vertexs[y]];

        // 判断边的两个端点是否属于同一个不相交树
        if (find_set(ind) != find_set(jnd) ) {
            // 如果不是，就合并他们
            combine_set(trees, ind, jnd);
            //minEdgs.push_back(pair<int, int>(x, y));
            //cout << miter->first << endl;
            priorities+=miter->first;
        }
        ++miter;
    }
/*
    vector<pair<int, int> >::const_iterator eiter = minEdgs.begin();
    while (eiter != minEdgs.end()) {
        int idx = eiter->first;
        int jdx = eiter->second;
        priorities += graph->matrixs[idx][jdx];
        ++eiter;
    }
*/
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
    graph->insert_edge(ng, nf, 4);
    graph->insert_edge(nd, nf, 14);
    graph->insert_edge(nc, nf, 2);
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

    kruskal_mst(graph);

    return 0;
}

