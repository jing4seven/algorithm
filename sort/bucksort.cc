/*
 * 桶排序
 *
 *
 */
#include <iostream>
#include "sort.h"

using namespace std;

int bsort(vector<double> &source, int buckets_size) {
    int i, j, k;
    vector<list<double> > buckets(buckets_size);

    // 初始化桶
    for (i=0; i<buckets_size; ++i) {
        list<double> tmp;
        buckets.push_back(tmp);
    }

    for (i=0; i<source.size(); ++i) {
        // 找到桶索引
        j = (int)(source[i]*buckets_size);

        // 找到链表头
        list<double>::iterator l_iter = buckets[j].begin();

        // 按顺序将元素插入链表
        while (*(l_iter)  <= source[i] && l_iter != buckets[j].end())
            ++l_iter;

        buckets[j].insert(l_iter, source[i]);
    }

    // 清空原始数组
    source.clear();

    // 遍历桶中的链表，按顺序将数据插入到原始数组中
    for (i=0 ; i<buckets_size; ++i) {
        list<double>::iterator l_iter = buckets[i].begin();

        while (l_iter!=buckets[i].end()) {
            source.push_back(*l_iter);
            ++l_iter;
        }
    }

    return 0;
}
/*
int main() {
    vector<double> source, testsource;
    int i;
    float tmp = 0;

    srand((int)time(0));

    i=1;
    // 这里初始化100个元素，索引从1到100
    while (i < 100) {
        tmp = random_db();
        source.push_back(tmp);
        ++i;
    }

    // 被测试的数组也是从1到100, 第0位不在范围内
    testsource.assign(source.begin(), source.end());

    cout << "source:" <<endl;
    printsource(source);

    // 使用STL自带的排序方法：
    sort(testsource.begin(), testsource.end(), less<double>());
    bsort(source, 10);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    cout << "\n";

    return 0;
}*/
