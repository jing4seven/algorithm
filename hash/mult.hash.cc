/*
 * 乘法散列
 *
 * 将整个键值k乘以一个常数A(0<A<1)，取结果的小数部分，
 * 然后乘以m取结果的整数部分；通常情况下，A取0.618,
 * 它由根号5减去1再除以2得到。
 */

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <time.h>
#include <assert.h>

using namespace std;

#define random_btn(x, y) (x+rand()%((y)-(x)))
#define HASH_SIZE 2000
#define HASH_ELM_COUNT 4500
#define A (double)((sqrt(5)-1)/2)

void printsource(vector<int> const  &source) {
    vector<int>::const_iterator itr = source.begin();
    while (itr != source.end()) {
        cout << *itr << "\t";
        ++itr;
    }

    cout << "\n";
}

int mult_hashing(int k) {
    double ds = k * A;
    int is = (int)ds;

    return HASH_SIZE * (ds - (double)is);
}

int max_duplicate_count(vector<int> &source) {
    map<int, int> tmpMap;
    int maxcount;
    vector<int>::const_iterator iter = source.begin();

    maxcount = 0;
    while (iter!=source.end()) {
        if (tmpMap.count(*iter)) {
            ++tmpMap[*iter];
        } else {
            tmpMap[*iter] = 1;
        }
        ++iter;
    }

    map<int, int>::const_iterator mapiter = tmpMap.begin();

    while (mapiter != tmpMap.end()) {
        if (mapiter->second > maxcount)
            maxcount=mapiter->second;

        ++mapiter;
    }

    return maxcount;
}

int main() {
    vector<int> source;
    map<int, int> testmap;
    int i = 0;
    int tmp = 0;
    int maxcount = 0;

    srand((int)time(0));
    while (i < HASH_ELM_COUNT) {
        tmp = random_btn(1,RAND_MAX);
        if (testmap.count(tmp)) {
            continue;
        } else {
            testmap[tmp] = 1;
            source.push_back(tmp);
        }
        ++i;
    }

    //sort(source.begin(), source.end(), less<int>());
    cout << "source by sort:" <<endl;
    printsource(source);

    cout << "total count:" << endl;
    cout << source.size() << endl;

    vector<int>::iterator iter;
    iter = source.begin();

    while (iter != source.end()) {
        *iter = mult_hashing(*iter);
        ++iter;
    }

    cout << "hash key by sort:" << endl;
    //sort(source.begin(), source.end(), less<int>());
    printsource(source);

    cout << "total count:" << endl;
    cout << source.size() << endl;

    maxcount = max_duplicate_count(source);
    cout << "max duplicate element count:" << endl;
    cout <<  maxcount << endl;

    return 0;
}

