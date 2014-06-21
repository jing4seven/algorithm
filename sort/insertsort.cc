/*
 * 插入排序
 */

#include <iostream>
#include <vector>
#include "sort.h"

using namespace std;

int isort(vector<int> &source) {
    vector<int>::iterator iiter;
    vector<int>::iterator jiter;
    int tmp;

    jiter = source.begin()+ 1;

    while (jiter != source.end()) {
        iiter = jiter-1;
        tmp = *jiter;
        // 将每个jiter所对应的元素跟已经排序好的
        // 元素进行比较，通过交换，让其停留在合适
        // 的位置
        while (iiter >= source.begin()) {
            if (*( iiter +1) < *iiter) {
                swap(*iiter, *( iiter+1 ));
            }
            --iiter;
        }
        ++jiter;
    }

    return 0;
}
/*
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
    isort(source);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valided source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    return 0;

}*/
