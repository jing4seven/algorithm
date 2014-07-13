#include "../graph/graph.h"
#include <iostream>
#include <stdio>
#include <deque>

#define COLOR_WHITE     0
#define COLOR_GRAY      1
#define COLOR_BLACK     2
#define INFINITE        ~(1<<(sizeof(int)*8-1))

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class SampleGNode: GNode {
public:
    int color;
    int distance;

    SampleGNode(T d): GNode(d), color(COLOR_WHITE), distance(INFINITE) { }
};

void bfs(Graph<T> * graph, SampleGNode<T> * gnode) {
    if (gnode == NULL || graph == NULL) {
        return;
    }

    deque<SampleGNode<T> *> que;
    SampleGNode<T> sgnode;
    set<GNode<T> *>::iterator iter;
    set<GNode<T>*> nodeadj;
    // 所有的节点初始化时，就默认都是白色，所以这里可以省略标白这一步了
    que.push_back(gnode);

    while (!que.empty()) {
        // 弹出一个节点, 对其邻接表进行遍历
        sgnode = que.front();
        //已经选择过的
        sgnode->color = COLOR_BLACK;

        nodeadj = sgnode->adjacent;
        iter = nodeadj.begin();

        while (iter != nodeadj.end()) {
            SampleGNode<T> * ssgnode = (SampleGNode<T> *) *iter;

            ssgnode->color = COLOR_GRAY;
            que.push_back(ssgnode);
            ++iter;
        }
        que.pop_front();
    }
}

////////////////////////////////////////////////////////////////////////////////
