#include <gtest/gtest.h>
#include "search.tree.h"

namespace {

    class BinarySearchTreeTest: public ::testing::Test {
    protected:
        virtual void SetUp() {
            t0_ = new BinarySearchTree();
            t1_ = new BinarySearchTree();
            t2_ = new BinarySearchTree();

            // init t0_
            t0_->insert(30);
            t0_->insert(20);
            t0_->insert(40);
            t0_->insert(10);
            t0_->insert(25);
            t0_->insert(35);
            t0_->insert(50);
            t0_->insert(5);
            t0_->insert(15);
            t0_->insert(28);
            t0_->insert(41);

            // init t1_
            t1_->insert(30);
            t1_->insert(20);
            t1_->insert(40);
            t1_->insert(1);
            t1_->insert(25);
            t1_->insert(35);
            t1_->insert(50);
            t1_->insert(5);
            t1_->insert(15);
            t1_->insert(28);
            t1_->insert(41);

            // init t2_
            t2_->insert(30);
            t2_->insert(20);
            t2_->insert(40);
            t2_->insert(10);
            t2_->insert(25);
            t2_->insert(3);
            t2_->insert(50);
            t2_->insert(5);
            t2_->insert(15);
            t2_->insert(28);
            t2_->insert(41);
        }

        virtual void TearDown() {
            delete t0_;
            delete t1_;
            delete t2_;

            t0_ = NULL;
            t1_ = NULL;
            t2_ = NULL;
        }

        BinarySearchTree * t0_;
        BinarySearchTree * t1_;
        BinarySearchTree * t2_;
    };

    TEST_F(BinarySearchTreeTest, findMinTest) {
        int minElm = t0_->findMin();
        ASSERT_EQ(5, minElm);

        minElm = t1_->findMin();
        ASSERT_EQ(1, minElm);

        minElm = t2_->findMin();
        ASSERT_EQ(3, minElm);
    }

} // namespace

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
