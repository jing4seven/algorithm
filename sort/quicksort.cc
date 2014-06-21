/*
 * 快速排序：
 *
 */
#include <iostream>
#include <vector>
#include "sort.h"

using namespace std;

int qsort1(vector<int> &source, int start, int end) {
    srand((int)time(0));
    int i,j,t,pos, result(0);
    i   = start;
    j   = end;
    t   = 0; // 插入操作用到的索引值
    pos = start + random(j-i); // 随机中间值

    while (i<j) {
        // 元素相等时如何处理
        while (i<pos && source[i]<= source[pos])
            ++i;

        while (j> pos && source[j]> source[pos])
            --j;

        if (i<j && i!=pos && j!=pos) {
            // 如果i和j都未到达pos
            // 则交换 source[i], source[j]
            swap(source[i], source[j]);
        } else if (i== pos && j!=pos) {
            // 如果i已经移动到pos处，j还没有，
            // 则讲j插入i的左边，
            // 随即更新相应索引
            t = j;
            while (t > pos) {
                swap(source[t], source[t-1]);
                --t;
            }
            if (pos<j)
                pos++;
        } else if ( i!=pos && j == pos) {
            // 如果j到达pos， i还没有的时候
            // 同上相反操作
            t = i;
            while (t < pos) {
                swap(source[t], source[t+1]);
                ++t;
            }
            if (pos>i)
                pos--;
        }
    }

    // pos处的元素在全局的位置已经固定
    // 此时它已经排好，只需要排列其他元素即可
    if (start< pos-1)
        result = qsort1(source, start, pos-1);

    if (pos<end-1)
        result = result + qsort1(source, pos+1, end);

    return result;
}

/*
int main(int argc, char * argv[]) {
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
    qsort(source, 0, (int)( source.size() -1 ));

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    cout << "\n";

    return 0;
}*/
