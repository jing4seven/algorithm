/*******************************************************************************
 二分搜索


 特征：
 1. 数据源必须是已经经过排序的;


 注：
 1. 数据元素直接用int实现，也是为了方便验证；

*******************************************************************************/
#include "search.h"

int BinarySearch(const vector<int> & s, const int k) {
    int start, end, pos, value;

    start = 0;
    end   = s.size()-1;

    while (end>=start ) {
        pos = (end+start)/2;
        value = s[pos];
        if (k == value)
            return pos;
        else if (k > value) {
            start = pos + 1;
        } else if (k < value) {
            end = pos - 1;
        }
    }

    //cout << start<< "," << end<< "," << pos<< endl;
    return -1;
}

////////////////////////////////////////////////////////////////////////////////
