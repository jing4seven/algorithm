/*
 * 全域散列
 *
 * 这里仅只演示概念
 *
 * 为了使k与散列函数独立，设置一种机制随机选取散列函数
 */
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <time.h>
#include <assert.h>

#define HASH_SIZE 1699
#define HASH_ELM_COUNT 4500
#define HASH_METHD_COUNT 2

#define A (double)((sqrt(5)-1)/2)
#define random_btn(x, y) (x+rand()%((y)-(x)))
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

int divi_hash(int k) {
    if (k < 0 )
        return -1;

    return k%HASH_SIZE;
}

int mult_hashing(int k) {
    double ds = k * A;
    int is = (int)ds;

    return HASH_SIZE * (ds - (double)is);
}

int uni_hashing(int k) {
    srand((int)time(0));
    return random(HASH_ELM_COUNT) == 0 ? divi_hash(k) : mult_hashing(k);
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
        *iter = uni_hashing(*iter);
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
