#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "sort.h"

#define SUCCESS         0
#define RDM_MAX_NUM     1000
#define MAX_COUNT       100

using namespace std;

namespace {
/*    template <typename T>
    void printsource(vector<T> &source) {
        vector<T>::iterator itr = source.begin();
        while (itr != source.end()) {
            cout << *itr << "\t";
            ++itr;
        }

        cout << "\n";
    }

    void printsource2(const vector<double> &source) {
        vector<double>::const_iterator itr = source.begin();
        while (itr != source.end()) {
            cout << *itr << "\t";
            ++itr;
        }

        cout << "\n";
    }*/
    class SortTest: public ::testing::Test {
    protected:
        virtual void SetUp() {
            int i(0), tmp(0);

            srand((int)time(0));
            while (i < MAX_COUNT) {
                tmp = random(RDM_MAX_NUM);
                // 初始化
                source.push_back(tmp);
                ++i;
            }

            // 将source的内容复制到testSource
            testSource.assign(source.begin(), source.end());
            sort(testSource.begin(), testSource.end(), less<int>());
        }

        virtual void TearDown() {
            source.clear();
            testSource.clear();
        }

        vector<int> source, testSource;
    };

    // insertSort
    TEST_F(SortTest, InsertSortTest) {
        ASSERT_EQ(SUCCESS, isort(source));
        ASSERT_EQ(testSource, source);
        //printsource(source);
        //printsource(testSource);
    }

    // mergeSort
    TEST_F(SortTest, MergeSortTest) {
        ASSERT_EQ(SUCCESS, msort(source, 0, source.size()-1));
        ASSERT_EQ(testSource, source);
        //printsource(source);
        //printsource(testSource);
    }

    // quickSort1
    TEST_F(SortTest, QuickSort1Test) {
        ASSERT_EQ(SUCCESS, qsort1(source, 0, source.size() -1 ));
        ASSERT_EQ(testSource, source);
        //printsource(source);
        //printsource(testSource);
    }

    // quickSort2
    TEST_F(SortTest, QuickSort2Test) {
        ASSERT_EQ(SUCCESS, qsort2(source, 0, source.size()-1));
        ASSERT_EQ(testSource, source);
        //printsource(source);
        //printsource(testSource);
    }

    // heapsort
    TEST_F(SortTest, HeapSortTest) {
        ASSERT_EQ(SUCCESS, heapsort(source));
        ASSERT_EQ(testSource, source);
        //printsource(source);
        //printsource(testSource);
    }

    // shellsort
    TEST_F(SortTest, ShellSortTest) {
        ASSERT_EQ(SUCCESS, shellsort(source));
        ASSERT_EQ(testSource, source);
        //printsource(source);
        //printsource(testSource);
    }

    // countsort
    TEST_F(SortTest, CountSortTest) {
        int i(1), tmp(0), maxvalue(61);

        srand((int)time(0));

        // 因为基数排序要求的数据比较特殊
        // 所以这里重新初始化测试数据
        source.clear();
        testSource.clear();

        // 这里初始化100个元素，索引从1到100
        while (i < MAX_COUNT) {
            tmp = random(maxvalue);
            source.push_back(tmp);
            ++i;
        }
        testSource.assign(source.begin(), source.end());
        sort(testSource.begin(), testSource.end(), less<int>());

        ASSERT_EQ(SUCCESS, countsort(source, maxvalue));
        ASSERT_EQ(testSource, source);

        //printsource(source);
        //printsource(testSource);
    }

    // radixsort
    TEST_F(SortTest, RadixSortTest) {
        /*vector<int> source, testSource;
        int i(0), tmp(0), result(-1);

        srand((int)time(0));
        while (i < MAX_COUNT) {
            tmp = random_btn(50, 1000);
            source.push_back(tmp);
            ++i;
        }

        testSource.assign(source.begin(), source.end());
        sort(testSource.begin(), testSource.end(), less<int>());

        // 这里默认基数是10, 表示10进制，实际上也可以用其他的数
        // 效果是一样的
        result = rsort(source, 3, 10);

        ASSERT_EQ(SUCCESS, result);
        ASSERT_EQ(testSource, source);*/

        //printsource(source);
        //printsource(testSource);
    }

    // bucksort
    TEST_F(SortTest, BuckSortTest) {
        vector<double> source2, testSource2;
        int i;
        float tmp = 0;

        srand((int)time(0));

        i=1;
        // 这里初始化100个元素，索引从1到100
        while (i < 100) {
            tmp = random_db();
            source2.push_back(tmp);
            ++i;
        }

        testSource2.assign(source2.begin(), source2.end());
        sort(testSource2.begin(), testSource2.end(), less<double>());

        ASSERT_EQ(SUCCESS, bsort(source2, 10));
        ASSERT_EQ(testSource2, source2);

        //printsource((vector<double> &)source2);
        //printsource((vector<double> &)testSource2);

    }
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
