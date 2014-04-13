/*
 * 归并排序
 * 需要额外的空间
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

void merge(vector<int> &source, int start, int pos, int end) {
    // 必须要有一个额外的空间
    // 临时存储排好序的元素
    vector<int> tmp;

    int i,j;
    i= start;
    j= pos +1;

    // 区两边集合中较小的部分填充到tmp中去
    while (i<=pos || j<=end) {
        // j已经到达终点，或者i，j都在有效范围内时，source[i]<=source[j]
        if ( (i<=pos&&j>end) || ((i<=pos && j<=end)&&source[i] <= source[j]) ) {
            tmp.push_back(source[i]);

            if (i<=pos)
                ++i;
        // i已经到达重点，或者i,j都在有效范围内时，source[i]>source[j]
        } else if ((i>pos&&j<=end) || ((i<=pos && j<=end) && source[i] > source[j] )) {
            tmp.push_back( source[j] );

            if (j<=end)
                j++;
        }
    }

    // 用排好序的tmp替换掉其在source中的位置
    j= start;
    for (i=0; i<tmp.size();++i) {
        source[j] = tmp[i];
        ++j;
    }
}

int msort(vector<int> &source, int start, int end) {
    int pos;

    pos = start + ( end-start )/2;

    if (pos > start)
        msort(source, start, pos);

    if (end > pos+1)
        msort(source, pos+1, end);

    merge(source, start, pos, end);

    return 0;
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
    msort(source, 0, source.size()-1);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    cout << "\n";

    return 0;
}
