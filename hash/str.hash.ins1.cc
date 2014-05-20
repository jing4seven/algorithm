/*
 * 字符串哈希例子1
 *
 * 取自《算法精解-c语言描述》 哈希表章节
 */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <time.h>

#define PRIME_TALBLE_SIZE 1980
#define random(x) (rand()%(x))


using namespace std;

template <typename T>
void
printsource(vector<T> &source) {
    typename vector<T>::iterator itr = source.begin();

    while (itr != source.end()) {
        cout << *itr << "\t";
        ++itr;
    }

    cout << "\n";
}

void gen_str(vector<string> &source,int length, int size) {
    int i,j;

    // 26+26+10=62
    char char_arr[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string char_str(length, 0);

    i=0;
    srand((int)time(0));
    while (i<size) {
        j=0;
        while (j<length) {
            char_str[j] = char_arr[random(62)];
            ++j;
        }
        source.push_back(char_str);
        ++i;
    }
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



unsigned int hashpjw(const void * key) {
    const char * ptr;
    unsigned int val;

    val = 0;
    ptr = (char *)key;

    while (*ptr != '\0') {
        unsigned int tmp;
        // 将每个字符都乘以16然后相加
        // 比如key为：abc
        // val = (97*16+98)*16+99
        val = (val << 4) + (*ptr);

        // 检查看val是否到达29位，也就使是否大于等于2^29
        // 如果29位到32位有值，将其最高4位获取，
        // 存放在tmp字段
        if (( tmp = (val & 0xf0000000) )) {
            // 将其最高8位右移24位后修改val的值
            val = val ^ (tmp >> 24);
            // 删除最高4位，让其值一直在2^32内
            val = val ^ tmp;
        }
        ptr++;
    }

    return val % PRIME_TALBLE_SIZE;
}

int main() {
    vector<string> source;
    vector<int> testsource;
    int i = 0;
    int tmp = 0;
    int maxcount = 0;

    gen_str(source, 10, 4500);

    cout << "source:" <<endl;
    printsource(source);

    cout << "hashed source:" <<endl;

    vector<string>::iterator itr = source.begin();
    vector<int>::iterator titr = testsource.begin();
    while (itr != source.end()) {
        testsource.push_back(hashpjw((*itr).c_str()));
        ++itr;
        ++titr;
    }
    printsource(testsource);

    maxcount =  max_duplicate_count(testsource);
    cout << "max duplicate element count:" << endl;
    cout <<  maxcount << endl;

    return 0;
}
