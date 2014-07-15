#include <gtest/gtest.h>
#include "search.tree.h"

namespace {

    // Test for BinarySearchTree
    class BinarySearchTreeTest: public ::testing::Test {
    protected:
        virtual void SetUp() {
            t0_ = new BinarySearchTree();

            for (int i=0;i<11;++i) {
                t0_->insert(testDataArr[i]);
            }
        }

        virtual void TearDown() {
            delete t0_;

            t0_ = NULL;
        }

        BinarySearchTree * t0_;
        int testDataArr[11] = {30,20,40,10,25,35,50,5,15,28,41};
    };

    // findMin
    TEST_F(BinarySearchTreeTest, findMinTest) {
        int minElm = t0_->findMin();
        ASSERT_EQ(5, minElm);
    }

    // contains
    TEST_F(BinarySearchTreeTest, containsTest) {
        bool isContains = t0_->contains(5);
        ASSERT_EQ(true, isContains);
    }

    // insert
    TEST_F(BinarySearchTreeTest, insertTest) {
    }

} // namespace

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
