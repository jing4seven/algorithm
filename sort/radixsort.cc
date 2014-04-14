/*
 * 基数排序
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

void rsort(vector<int> &source, int maxBit ) {
    int tmp, i, j, k, t, m, n;
    i = 0; // 十进制位索引
    j = 0; // 元素索引

    vector<vector<int> > tmpVecArr;

    // 初始化临时二维数组
    for (n = 0; n<10; ++n) {
        vector<int> tmpVec;
        tmpVecArr.push_back(tmpVec);
    }

    // 从个位开始
    i = 1;
    while (i <= maxBit) {
        // 清空临时二维数组
        for (n = 0; n<10; ++n) {
            tmpVecArr[n].clear();
        }

        // 根据当前十进制位的大小，将元素进行分组
        for (j=0; j<source.size(); ++j)  {
            if (i> 1)
                tmp=(int)(source[j]/pow(10, i-1));
            else
                tmp=source[j];

            k = tmp%10;

            tmpVecArr[k].push_back(source[j]);
        }
        t = 0;
        m = 0;

        // 将source中的内容替换成临时数组中的内容
        while (t < tmpVecArr.size() ) {
            for (n=0; n<tmpVecArr[t].size(); ++n) {
                source[m+n]= tmpVecArr[t][n];
            }
            m = m + tmpVecArr[t].size() ;
            ++t;
        }
        ++i;
    }
}

int main() {
    vector<int> source, testsource;
    int i = 0;
    int tmp = 0;

    srand((int)time(0));
    while (i < 100) {
        tmp = random_btn(100, 1000);
        source.push_back(tmp);
        ++i;
    }

    testsource.assign(source.begin(), source.end());

    cout << "source:" <<endl;
    printsource(source);

    // 使用STL自带的排序方法：
    sort(testsource.begin(), testsource.end(), less<int>());
    rsort(source, 3);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    cout << "\n";

    return 0;
}
