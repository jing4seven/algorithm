/*
 * 堆排序
 * 使用最大堆模型
 * 在排序之前，先构造最大堆
 * 然后将根节点顺序移出到到最后，即排序完成
 */
#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>

#define random(x) (rand()%(x))

#define parent(x) ((x)/2)
#define left(x) ((x)*2)
#define right(x) ((x)*2+1)

#define sourcevalue(x) (source[x-1])

using namespace std;

void printsource(vector<int> &source) {
    vector<int>::iterator itr = source.begin();
    while (itr != source.end()) {
        cout << *itr << "\t";
        ++itr;
    }

    cout << "\n";
}

void maxheapfy(vector<int> &source, int pos, int maxlen) {
    int l, r, largest;

    l       = left(pos);
    r       = right(pos);
    largest = pos;

    if (l <= maxlen && sourcevalue(l) > sourcevalue(largest)) {
        largest = l;
    }

    if (r<= maxlen && sourcevalue(r) > sourcevalue(largest)) {
        largest = r;
    }

    if (largest != pos) {
        swap(sourcevalue(pos), sourcevalue(largest));
        // 从上到下，依次整理,确保自己以及其子节点满足最大堆
        maxheapfy(source, largest, maxlen);
    }
}


void buildheap(vector<int> &source) {
    vector<int>::size_type maxlen = source.size();
    int pos = maxlen/2;

    // 依次对数组中的前半部分节点进行整理,直到根节点为止，
    // 此时即把零散的数组, 转化为最大堆
    while (pos > 0) {
        maxheapfy(source, pos, maxlen);
        --pos;
    }
}

void heapsort(vector<int> &source) {
    vector<int>::size_type maxlen = source.size();

    // 讲零散的数组转化为最大堆
    buildheap(source);

    while (maxlen>0) {
        // 根节点已经是最大值，直接放到最后
        swap(sourcevalue(1), sourcevalue(maxlen));

        --maxlen;
        maxheapfy(source, 1, maxlen);
    }
}

int main() {
    vector<int> source, testsource;
    int i = 0;
    int tmp = 0;

    srand((int)time(0));
    while (i < 100) {
        tmp = random(1000);
        source.push_back(tmp);
        ++i;
    }

    testsource.assign(source.begin(), source.end());

    cout << "source:" <<endl;
    printsource(source);

    // 使用STL自带的排序方法：
    sort(testsource.begin(), testsource.end(), less<int>());
    heapsort(source);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    cout << "\n";

    return 0;
}
