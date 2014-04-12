/*
 * 快速排序, 版本2
 */

#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>

#define random(x) (rand()%(x))

using namespace std;

void printsource(vector<int> &source) {
    vector<int>::iterator itr = source.begin();
    while (itr != source.end()) {
        cout << *itr << "\t";
        ++itr;
    }

    cout << "\n";
}

// 分割函数
int partition(vector<int> &source, int start, int end) {
    int k, pos, t;
    k = start +1;
    // 选取第一个元素为pos
    pos = start;

    // 让pos所在的元素和它后面的元素逐一比较
    // 如果source[pos]>=source[k]
    // 则将source[k]插入到source[pos]的前面，
    // 同时更新pos的位置
    while (k<=end) {
        if (source[pos]>=source[k]) {
            t = k;
            while (t>pos) {
                swap(source[t-1], source[t]);
                --t;
            }
            ++pos;
        }
        ++k;
    }

    return pos;
}

void qsort(vector<int> &source, int start, int end) {
    int pos;

    pos = partition(source, start, end);

    if (pos-1 >start)
        qsort(source, start, pos-1);

    if (end>pos+1)
        qsort(source, pos+1, end);

    return;
}

int main () {
    vector<int> source, testsource;
    vector<int>::iterator iter;

    int tmp, i=0;
    srand((int)time(0));
    while (i<100) {
        tmp = random(100);
        source.push_back(tmp);
        ++i;
    }

    cout << "source:" << endl;

    printsource(source);

    cout << "ordered source:" <<endl;
    qsort(source, 0, source.size()-1);

    // 使用STL自带的排序方法：
    testsource.assign(source.begin(), source.end());
    sort(testsource.begin(), testsource.end(), less<int>());

    cout << "valided source:" << endl;
    printsource(source);

    // 测试
    assert(testsource == source);

    printsource(source);

}
