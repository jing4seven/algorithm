/*******************************************************************************
 深度优先搜索

 特征：
 1. 必须是有向无环图；
 2. 可以实现节点的拓扑排序；

 示例：
 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14
 |__|__|__|__|__|__|__|__|__|__|__|__|__|__|
    |______________________________________|    A(1/14)
       |________________________________|       B(2/13)
                                  |__|          C(11/12)
          |____________________|                D(3/10)
                         |__|                   G(8/9)
             |________|                         C(4/7)
                |__|                            F(5/6)
*******************************************************************************/
#include "../graph/graph.cc"
#include <stdio.h>
#include <iostream>
#include <deque>

#define COLOR_WHITE     0
#define COLOR_BLACK     1

#define NIL             NULL
#define INFINITE        ~(1<<(sizeof(int)*8-1))

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class DfsGNode: public GNode<T> {
public:
    int color;
    int start;      // 开始时间
    int finish;     // 结束时间
    DfsGNode<T> * parent;

    DfsGNode(T d): GNode<T>(d), color(COLOR_WHITE), parent(NIL),
        start(INFINITE), finish(INFINITE) { }
};

// ToDo: 添加有环检测功能
template <typename T>
void dfs_view(Graph<T> * graph, DfsGNode<T> * gnode, int & time) {
    ++time;

    gnode->start = time;

    typename set<GNode<T>*>::iterator iter = gnode->adjacent.begin();

    while (iter != gnode->adjacent.end()) {
        if (((DfsGNode<T>*)*iter)->color == COLOR_WHITE) {
            dfs_view(graph, ((DfsGNode<T>*)*iter), time);
        }
        ++iter;
    }

    ++time;
    gnode->color = COLOR_BLACK;
    gnode->finish = time;

    cout << gnode->data << ":" << gnode->start << "/" << gnode->finish << endl;
}

template <typename T>
void dfs(Graph<T> * graph) {
    if (graph == NULL) {
        return;
    }

    int time = 0;

    typename list<GNode<T> *>::iterator iter = graph->adjacents.begin();

    while (iter != graph->adjacents.end() ) {
        if (((DfsGNode<T> *)*iter)->color == COLOR_WHITE) {
            dfs_view(graph, ((DfsGNode<T>*)*iter), time);
        }
        ++iter;
    }
}

int main(void) {
    Graph<string> * graph = new Graph<string>();

    DfsGNode<string> * na = new DfsGNode<string>("A");
    DfsGNode<string> * nb = new DfsGNode<string>("B");
    DfsGNode<string> * nc = new DfsGNode<string>("C");
    DfsGNode<string> * nd = new DfsGNode<string>("D");
    DfsGNode<string> * ne = new DfsGNode<string>("E");
    DfsGNode<string> * nf = new DfsGNode<string>("F");
    DfsGNode<string> * ng = new DfsGNode<string>("G");

    graph->insert_vertex(na);
    graph->insert_vertex(nb);
    graph->insert_vertex(nc);
    graph->insert_vertex(nd);
    graph->insert_vertex(ne);
    graph->insert_vertex(nf);
    graph->insert_vertex(ng);

    graph->insert_edge(na, nd);
    graph->insert_edge(na, nc);
    graph->insert_edge(na, nb);

    graph->insert_edge(nb, nd);
    graph->insert_edge(nb, ne);

    graph->insert_edge(nc, nf);

    graph->insert_edge(nd, nf);
    graph->insert_edge(nd, ng);
    graph->insert_edge(nd, nc);

    graph->insert_edge(ne, nd);
    graph->insert_edge(ne, ng);

    graph->insert_edge(ng, nf);

    dfs(graph);

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
