/*******************************************************************************
 广度优先搜索

 特征：
 1. 有向无向都可以，有环五环都可以。
*******************************************************************************/
#include "../graph/graph.cc"
#include <stdio.h>
#include <iostream>
#include <deque>

#define COLOR_WHITE     0
#define COLOR_GRAY      1
#define COLOR_BLACK     2

#define NIL             NULL
#define INFINITE        ~(1<<(sizeof(int)*8-1))

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class BfsGNode: public GNode<T> {
public:
    int color;
    int dist;
    BfsGNode<T> * parent;

    BfsGNode(T d): GNode<T>(d), color(COLOR_WHITE), parent(NIL),
        dist(INFINITE) { }
};

template <typename T>
void bfs(Graph<T> * graph, BfsGNode<T> * gnode) {
    if (gnode == NULL || graph == NULL) {
        return;
    }

    deque<BfsGNode<T> *> que;
    typename set<GNode<T> *>::iterator iter;
    set<GNode<T>*> nodeadj;
    // 所有的节点初始化时，就默认都是白色，所以这里可以省略标白这一步了
    que.push_back(gnode);

    while (!que.empty()) {
        BfsGNode<T> * sgnode;
        // 弹出一个节点, 对其邻接表进行遍历
        sgnode = que.front();
        // 已经选择过的表黑色
        sgnode->color = COLOR_BLACK;
        // 更新distance
        sgnode->dist = sgnode->parent == NIL ? 0: (sgnode->parent->dist+ 1);
        cout << sgnode->data << ":" << sgnode->dist << endl;
        nodeadj = sgnode->adjacent;
        iter = nodeadj.begin();

        while (iter != nodeadj.end()) {
            BfsGNode<T> * ssgnode = (BfsGNode<T> *) *iter;

            if (ssgnode->color == COLOR_WHITE) {
                ssgnode->parent = sgnode;
                ssgnode->color = COLOR_GRAY;
                que.push_back(ssgnode);
            }

            ++iter;
        }

        que.pop_front();
    }
}


int main(void) {
    Graph<string> * graph = new Graph<string>();

    BfsGNode<string> * na = new BfsGNode<string>("A");
    BfsGNode<string> * nb = new BfsGNode<string>("B");
    BfsGNode<string> * nc = new BfsGNode<string>("C");
    BfsGNode<string> * nd = new BfsGNode<string>("D");
    BfsGNode<string> * ne = new BfsGNode<string>("E");
    BfsGNode<string> * nf = new BfsGNode<string>("F");
    BfsGNode<string> * ng = new BfsGNode<string>("G");

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

    bfs(graph, na);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
