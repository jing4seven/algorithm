#ifndef ALG_SORT_H
#define ALG_SORT_H

#include <iostream>
#include <vector>
#include <list>

#define random(x)   (rand()%(x))

// use for heap sort.
#define parent(x) ((x)/2)
#define left(x) ((x)*2)
#define right(x) ((x)*2+1)
#define sourcevalue(x) (source[x-1])

// use for radix sort
#define random_btn(x,y) ((x) + (rand()%((y)-(x))))

// use for buck sort
#define random_db() ((double)(rand()/(double)RAND_MAX))

using namespace std;

int isort(vector<int> &source);
int msort(vector<int> &source, int start, int end);
int qsort1(vector<int> &source, int start, int end);
int qsort2(vector<int> &source, int start, int end);
int heapsort(vector<int> &source);
int shellsort(vector<int> &source);
int countsort(vector<int> &source, int maxvalue);
int rsort(vector<int> &source, int maxBit, int base );
int bsort(vector<double> &source, int buckets_size);

#endif
