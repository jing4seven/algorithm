#include <iostream>
#include <vector>

using namespace std;

int BinarySearch(const vector<int> & s, const int k);

////////////////////////////////////////////////////////////////////////////////

class GraphNode {
public:
    int color;
    int distance;
    GraphNode * pre;

    GraphNode(int c, int d, GraphNode * p): color(c), distance(d), pre(p){}
};

class SampleGraph {
public:
    int vcount;
    int ecount;

    vector<GraphNode *> adjectList;
};

////////////////////////////////////////////////////////////////////////////////
