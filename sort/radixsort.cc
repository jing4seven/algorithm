/*
 * 基数排序
 * 基于基数，按照基数的位从小到达进行计数排序
 */
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <assert.h>

#define random_btn(x,y) ((x) + (rand()%((y)-(x))))

using namespace std;

void printsource(const vector<int> &source) {
    vector<int>::const_iterator itr = source.begin();
    while (itr != source.end()) {
        cout << *itr << "\t";
        ++itr;
    }

    cout << "\n";
}

void rsort(vector<int> &source, int maxBit, int base ) {
    int tmp, idx, i, k;
    idx = 0; // 基数位索引
    i = 0; // 元素索引
    vector<int> counts(base, 0);

    // 从最小的位开始
    idx = 1;
    while (idx <= maxBit) {
        // 根据当前基数进制位的大小，将元素进行分组
        for (i=0; i<source.size(); ++i)  {
            if (idx> 1)
                tmp=(int)(source[i]/pow(base, idx-1));
            else
                tmp=source[i];

            k = tmp%base;

            counts[k] = counts[k]+1;
        }

        for (i=1; i<base; ++i) {
            counts[i] = counts[i] + counts[i-1];
        }

        for (int i=0; i<source.size(); ++i) {
            source[counts[source[i]]-1] = source[i];
            --counts[source[i]];
        }

        ++idx;
    }
}

int main() {
    vector<int> source, testsource;
    int i = 0;
    int tmp = 0;

    srand((int)time(0));
    while (i < 100) {
        tmp = random_btn(50, 1000);
        source.push_back(tmp);
        ++i;
    }

    testsource.assign(source.begin(), source.end());

    cout << "source:" <<endl;
    printsource(source);

    // 使用STL自带的排序方法：
    sort(testsource.begin(), testsource.end(), less<int>());
    // 这里默认基数是10, 表示10进制，实际上也可以用其他的数
    // 效果是一样的
    rsort(source, 3, 10);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    cout << "\n";

    return 0;
}
