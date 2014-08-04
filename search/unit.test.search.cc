#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "search.h"

#define MAX_COUNT       100
#define RDM_MAX_NUM     1000
#define POS             50
#define random(x)       (rand()%(x))

using namespace std;

namespace {

////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void printsource(const vector<T> &source) {
        typename vector<T>::const_iterator itr = source.begin();
        while (itr != source.end()) {
            cout << *itr << "\t";
            ++itr;
        }

        cout << "\n";
    }
    // Test for all binary search.
    class BinarySearchTest: public ::testing::Test{
    protected:
        virtual void SetUp() {
            int i(0), tmp(0);

            srand((int)time(0));
            while (i < MAX_COUNT) {
                tmp = random(RDM_MAX_NUM);
                // 初始化
                testSource.push_back(tmp);
                if (i== POS)
                    key = tmp;
                ++i;
            }

            sort(testSource.begin(), testSource.end(), less<int>());
        }

        virtual void TearDown() {
        }

        vector<int> testSource;
        int key;
    };

    // BinarySearch
    TEST_F(BinarySearchTest, BinarySearch) {
        //printsource(testSource);
        ASSERT_EQ(true, BinarySearch(testSource, key) >= 0);
        ASSERT_EQ(true, BinarySearch(testSource, -5) < 0);
    }
} // namespace

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
