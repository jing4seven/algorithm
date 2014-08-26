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
class SampleGNode: public GNode<T> {
public:
    int color;
    int dist;
    SampleGNode<T> * parent;

    SampleGNode(T d): GNode<T>(d), color(COLOR_WHITE), parent(NIL),
        dist(INFINITE) { }
};

template <typename T>
void bfs(Graph<T> * graph, SampleGNode<T> * gnode) {
    if (gnode == NULL || graph == NULL) {
        return;
    }

    deque<SampleGNode<T> *> que;
    typename set<GNode<T> *>::iterator iter;
    set<GNode<T>*> nodeadj;
    // 所有的节点初始化时，就默认都是白色，所以这里可以省略标白这一步了
    que.push_back(gnode);

    while (!que.empty()) {
        SampleGNode<T> * sgnode;
        // 弹出一个节点, 对其邻接表进行遍历
        sgnode = que.front();
        // 已经选择过的表黑色
        sgnode->color = COLOR_BLACK;
        // 更新distance
        sgnode->dist = sgnode->parent == NIL ? 0: (sgnode->parent->dist+ 1);
        //cout << sgnode->data << ":" << sgnode->dist << endl;
        nodeadj = sgnode->adjacent;
        iter = nodeadj.begin();

        while (iter != nodeadj.end()) {
            SampleGNode<T> * ssgnode = (SampleGNode<T> *) *iter;

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

    SampleGNode<string> * n1 = new SampleGNode<string>("A");
    SampleGNode<string> * n2 = new SampleGNode<string>("B");
    SampleGNode<string> * n3 = new SampleGNode<string>("C");
    SampleGNode<string> * n4 = new SampleGNode<string>("D");
    SampleGNode<string> * n5 = new SampleGNode<string>("E");
    SampleGNode<string> * n6 = new SampleGNode<string>("F");
    SampleGNode<string> * n7 = new SampleGNode<string>("G");

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

    bfs(graph, n1);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
