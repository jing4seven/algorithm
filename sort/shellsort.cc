/*
 * 希尔排序
 */
#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>

#define random(x) (rand()%(x))

using namespace std;

void printsource(vector<int> const  &source) {
    vector<int>::const_iterator itr = source.begin();
    while (itr != source.end()) {
        cout << *itr << "\t";
        ++itr;
    }

    cout << "\n";
}

void shellsort(vector<int> &source) {
    int i, j, k;
    int tmp;

    // 递减的的希尔序列是n/2, n/4 .... 1
    for (i=source.size()/2; i>=1; i/=2) {
        cout << i << endl;
        for (j=i; j<source.size(); ++j) {
            // 保留当前元素的值
            tmp = source[j];

            //  这里堆间隔为i的元素进行插入排序
            //  用tmp来比较，即每次都用当前元素来比较
            //  这样的话，只需要计算当前元素移动的位置
            //  即可
            for (k=j; k>=i && tmp< source[k-i]; k-=i) {
                source[k] = source[k-i];
            }

            source[k] = tmp;

            // 或者用交换实现也行
            // 不过如果这样的话，就的用source[k]来判断了
            /*for (k=j;k>=i&&source[k]<source[k-i];k-=i)*/
                /*swap(source[k], source[k-i]);*/
        }

        printsource(source);
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
    shellsort(source);

    cout << "ordered source:" <<endl;
    printsource(source);

    cout << "valied source:" << endl;
    printsource(testsource);

    // 测试
    assert(source == testsource);

    cout << "\n";


    return 0;
}
