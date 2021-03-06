/*
 * 计数排序
 *
 * 前提条件：
 * 1. 需要知道序列中最大的数
 * 2. 所有需要排序的元素在一定区间
 *
 * 需要两个额外的存储空间
 * 一个是存放元素计数信息
 * 一个是存放临时结果
 */
#include <iostream>
#include <vector>
#include "sort.h"

using namespace std;

int countsort(vector<int> &source, int maxvalue) {
    // 初始化计数信数组，长度为maxvalue， 并将所有元素置为0
    vector<int> countArr(maxvalue, 0);
    // 临时结果变量，将所有元素置为0
    vector<int> resultArr(source.size(), 0);

    int i;

    // 填入计数信息
    for (i=0; i<source.size(); ++i) {
        countArr[source[i]] = countArr[source[i]] + 1;
    }

    // 整理计数信息
    for (i=1; i<countArr.size(); ++i) {
        countArr[i] = countArr[i] + countArr[i-1];
    }

    for (i=0; i<source.size(); ++i) {
        resultArr[countArr[source[i]]-1] = source[i];
        --countArr[source[i]];
    }

    source.assign(resultArr.begin(), resultArr.end());
    return 0;
}
/*
int main() {
    vector<int> source, testsource;
    int i, tmp, maxvalue;
    tmp = 0;
    maxvalue = 61;

    srand((int)time(0));

    i=1;
    // 这里初始化100个元素，索引从1到100
    while (i < 100) {
        tmp = random(maxvalue);
        source.push_back(tmp);
        ++i;
    }

    // 被测试的数组也是从1到100, 第0位不在范围内
    testsource.assign(source.begin(), source.end());

    cout << "source:" <<endl;
    printsource(source);

    // 使用STL自带的排序方法：
    sort(testsource.begin(), testsource.end(), less<int>());
    countsort(source, maxvalue);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    //assert(source == testsource);

    cout << "\n";

    return 0;
}*/
