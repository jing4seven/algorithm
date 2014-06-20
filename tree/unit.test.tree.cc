#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include "search.tree.h"
#include "search.tree2.h"
#include "avl.tree.h"
#include "printTree.h"

namespace {

////////////////////////////////////////////////////////////////////////////////
    // Test for all binary search trees.
    class BinarySearchTreeTest: public ::testing::Test {
    protected:
        virtual void SetUp() {
            t0_ = new BinarySearchTree();
            t1_ = new BinarySearchTree2();
            t2_ = new AvlTree();
            /*
                    ______30______
                   /              \
                __20__          __40__
               /      \        /      \
              10      25      35      50
             /  \       \            /
             5  15      28          41
            */
            testData.push_back(30);
            testData.push_back(20);
            testData.push_back(40);
            testData.push_back(10);
            testData.push_back(25);
            testData.push_back(35);
            testData.push_back(50);
            testData.push_back(5);
            testData.push_back(15);
            testData.push_back(28);
            testData.push_back(41);

            vector<int>::const_iterator iter = testData.begin();

            while (iter != testData.end()) {
                t0_->insert(*iter);
                t1_->insert(*iter);
                t2_->insert(*iter);
                ++iter;
            }
        }

        virtual void TearDown() {
            delete t0_;
            delete t1_;
            delete t2_;

            t0_ = NULL;
            t1_ = NULL;
            t2_ = NULL;
        }

        BinarySearchTree    * t0_;
        BinarySearchTree2   * t1_;
        AvlTree             * t2_;
        vector<int> testData;
    };

    // findMin
    TEST_F(BinarySearchTreeTest, findMinTest) {
        ASSERT_EQ(5, t0_->findMin());
        ASSERT_EQ(5, t1_->findMin());
        ASSERT_EQ(5, t2_->findMin());
    }

    // contains
    TEST_F(BinarySearchTreeTest, containsTest) {
        ASSERT_EQ(true, t0_->contains(5));
        ASSERT_EQ(true, t1_->contains(5));
        ASSERT_EQ(true, t2_->contains(5));
    }

    // traversal
    TEST_F(BinarySearchTreeTest, traversalTest) {
        ostringstream osm0, osm1, osm2, testDataOsm;

        t0_->traversal(osm0);
        t1_->traversal(osm1);
        t2_->traversal(osm2);

        sort(testData.begin(), testData.end(), less<int>());

        vector<int>::const_iterator iter = testData.begin();
        while (iter != testData.end()) {
            testDataOsm << *iter << ",";
            ++iter;
        }

        ASSERT_EQ(testDataOsm.str(), osm0.str());
        ASSERT_EQ(testDataOsm.str(), osm1.str());
        ASSERT_EQ(testDataOsm.str(), osm2.str());
    }

    // insert
    TEST_F(BinarySearchTreeTest, insertTest) {
        ostringstream osm0, osm1, osm2, testDataOsm;

        t0_->insert(24);
        t0_->insert(42);

        t1_->insert(24);
        t1_->insert(42);

        t2_->insert(24);
        t2_->insert(42);

        testData.push_back(24);
        testData.push_back(42);

        t0_->traversal(osm0);
        t1_->traversal(osm1);
        t2_->traversal(osm2);

        sort(testData.begin(), testData.end(), less<int>());
        vector<int>::const_iterator iter = testData.begin();
        while (iter != testData.end()) {
            testDataOsm << *iter << ",";
            ++iter;
        }

        //printPretty(t0_->root, 1, 0, cout);
        ASSERT_EQ(testDataOsm.str(), osm0.str());
        ASSERT_EQ(testDataOsm.str(), osm1.str());
        ASSERT_EQ(testDataOsm.str(), osm2.str());
    }

    // remove
    TEST_F(BinarySearchTreeTest, removeTest) {
        ostringstream osm0, osm1, osm2, testDataOsm;

        //t0_/////////////////////////////////////////////
        // 删除一个不存在的元素
        t0_->remove(115);

        // 按同样顺序删除全部元素
        t0_->remove(30);
        t0_->remove(20);
        t0_->remove(5);
        t0_->remove(10);
        t0_->remove(50);
        t0_->remove(41);
        t0_->remove(40);
        t0_->remove(28);
        t0_->remove(25);
        t0_->remove(35);
        t0_->remove(15);

        //t1_/////////////////////////////////////////////
        // 按同样顺序删除全部元素
        t1_->remove(115);

        // 将全部元素删除
        t1_->remove(30);
        t1_->remove(20);
        t1_->remove(5);
        t1_->remove(10);
        t1_->remove(50);
        t1_->remove(41);
        t1_->remove(40);
        t1_->remove(28);
        t1_->remove(25);
        t1_->remove(35);
        t1_->remove(15);

        //t2_/////////////////////////////////////////////
        // 按同样顺序删除全部元素
        t2_->remove(115);

        // 将全部元素删除
        t2_->remove(30);
        t2_->remove(20);
        t2_->remove(5);
        t2_->remove(10);
        t2_->remove(50);
        t2_->remove(41);
        t2_->remove(40);
        t2_->remove(28);
        t2_->remove(25);
        t2_->remove(35);
        t2_->remove(15);

        t0_->traversal(osm0);
        t1_->traversal(osm1);
        t1_->traversal(osm2);

        /*sort(testData.begin(), testData.end(), less<int>());
        vector<int>::const_iterator iter = testData.begin();
        while (iter != testData.end()) {
            if (*iter != 30 && *iter != 25)
                testDataOsm << *iter << ",";
            ++iter;
        }*/
        testDataOsm << "";

        //printPretty(t0_->root, 1, 0, cout);
        ASSERT_EQ(testDataOsm.str(), osm0.str());
        ASSERT_EQ(testDataOsm.str(), osm1.str());
        ASSERT_EQ(testDataOsm.str(), osm2.str());
    }

    // clone
    TEST_F(BinarySearchTreeTest, cloneTest) {

    }
////////////////////////////////////////////////////////////////////////////////

} // namespace

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
