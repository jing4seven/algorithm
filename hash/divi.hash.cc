/*
 * 除法散列(Division hasing)
 *
 * h(k) = k mod m
 *
 * k: 关键字
 * m: 散列表的大小
 *
 * 除法散列的关键在于m的选取，
 * 选取m值时，最好不要选取2^p即2的某次幂，2^p-1也不是个好的选择；
 *
 * 而要选取一个这样的数：
 * 1. 素数；
 * 2. 不太接近2的幂；
 * 3. 和负载因子有关系；
 *
 * 负载因子=需要插入的总数/散列表容量
 */
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <assert.h>

#define random_btn(x, y) (x+rand()%((y)-(x)))
// 这里假设需要插入的元素约4500左右，负载因子要求为3左右
// 所以4500/3=1500，然后取m为1699，其正好是介于2^10(1024)和2^11(2048)
// 负载因子为4500/1699=2.6，可以满足每个位置最多放3个元素
#define HASH_SIZE 1699
#define HASH_ELM_COUNT 4500

using namespace std;

void printsource(vector<int> const  &source) {
    vector<int>::const_iterator itr = source.begin();
    while (itr != source.end()) {
        cout << *itr << "\t";
        ++itr;
    }

    cout << "\n";
}

int divi_hash(int k) {
    if (k < 0 )
        return -1;

    return k%HASH_SIZE;
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
        *iter = divi_hash(*iter);
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

}
