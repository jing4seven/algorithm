/*
 * 基数排序
 * 基于基数，按照基数的位从小到达进行计数排序
 */
#include <iostream>
#include "sort.h"

using namespace std;

int rsort(vector<int> &source, int maxBit, int base ) {
    int idx, i, k, cidx, bitBase;
    idx = 0; // 基数位索引
    i = 0; // 元素索引
    cidx = 0; // counts的索引值
    bitBase = 1; // 为了获取每位上得值而使用的位基数

    vector<int> counts(base, 0);
    vector<int> tmpArr(source.size(), 0);

    // 从最小的位开始
    idx = 1;
    while (idx <= maxBit) {
        counts.assign(source.size(), 0);
        bitBase = (int)pow(base, idx-1);

        // 根据当前基数进制位的大小，将元素进行分组
        for (i=0; i<source.size(); ++i)  {
            cidx = (source[i]/bitBase)%base;

            counts[cidx] = counts[cidx]+1;
        }

        for (i=1; i<base; ++i) {
            counts[i] = counts[i] + counts[i-1];
        }

        for (i=source.size()-1;i>=0;--i) {
            cidx = (int)(source[i]/bitBase)%base;
            tmpArr[counts[cidx]-1] = source[i];
            counts[cidx]=counts[cidx]-1;
        }

        source.assign(tmpArr.begin(), tmpArr.end());

        ++idx;
    }
    return 0;
}
/*
int main() {
    vector<int> source, testsource;
    int i = 0;
    int tmp = 0;

    srand((int)time(0));
    while (i < 10) {
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
    //assert(source == testsource);

    cout << "\n";

    return 0;
}*/
