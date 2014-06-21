#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include "search.tree.h"
#include "search.tree2.h"
#include "avl.tree.h"
#include "printTree.h"
#include "rb.tree.h"

namespace {

////////////////////////////////////////////////////////////////////////////////
    // Test for all binary search trees.
    class BinarySearchTreeTest: public ::testing::Test{
    protected:
        virtual void SetUp() {
            t0_ = new BinarySearchTree();
            t1_ = new BinarySearchTree2();
            t2_ = new AvlTree();
            t3_ = new RBTree();
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
                t3_->insert(*iter);
                ++iter;
            }
        }

        virtual void TearDown() {
            delete t0_;
            delete t1_;
            delete t2_;
            delete t3_;

            t0_ = NULL;
            t1_ = NULL;
            t2_ = NULL;
            t3_ = NULL;
        }

        BinarySearchTree    * t0_;
        BinarySearchTree2   * t1_;
        AvlTree             * t2_;
        RBTree              * t3_;
        vector<int> testData;
    };

    // findMin
    TEST_F(BinarySearchTreeTest, findMinTest) {
        ASSERT_EQ(5, t0_->findMin());
        ASSERT_EQ(5, t1_->findMin());
        ASSERT_EQ(5, t2_->findMin());
        ASSERT_EQ(5, t3_->findMin());
    }

    // contains
    TEST_F(BinarySearchTreeTest, containsTest) {
        ASSERT_EQ(true, t0_->contains(5));
        ASSERT_EQ(true, t1_->contains(5));
        ASSERT_EQ(true, t2_->contains(5));
        ASSERT_EQ(true, t3_->contains(5));
    }

    // traversal
    TEST_F(BinarySearchTreeTest, traversalTest) {
        ostringstream osm0, osm1, osm2, osm3, testDataOsm;

        t0_->traversal(osm0);
        t1_->traversal(osm1);
        t2_->traversal(osm2);
        t3_->traversal(osm3);

        sort(testData.begin(), testData.end(), less<int>());

        vector<int>::const_iterator iter = testData.begin();
        while (iter != testData.end()) {
            testDataOsm << *iter << ",";
            ++iter;
        }

        ASSERT_EQ(testDataOsm.str(), osm0.str());
        ASSERT_EQ(testDataOsm.str(), osm1.str());
        ASSERT_EQ(testDataOsm.str(), osm2.str());
        ASSERT_EQ(testDataOsm.str(), osm3.str());
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
        t2_->traversal(osm2);

        testDataOsm << "";

        //printPretty(t0_->root, 1, 0, cout);
        ASSERT_EQ(testDataOsm.str(), osm0.str());
        ASSERT_EQ(testDataOsm.str(), osm1.str());
        ASSERT_EQ(testDataOsm.str(), osm2.str());
    }

    TEST_F(BinarySearchTreeTest, makeEmptyTest) {
        ostringstream osm0, osm1, osm2, osm3, testDataOsm;

        t0_->makeEmpty();
        t1_->makeEmpty();
        t2_->makeEmpty();
        t3_->makeEmpty();

        t0_->traversal(osm0);
        t1_->traversal(osm1);
        t2_->traversal(osm2);
        t3_->traversal(osm2);

        testDataOsm << "";

        ASSERT_EQ(testDataOsm.str(), osm0.str());
        ASSERT_EQ(testDataOsm.str(), osm1.str());
        ASSERT_EQ(testDataOsm.str(), osm2.str());
        ASSERT_EQ(testDataOsm.str(), osm3.str());
    }

    // clone
    TEST_F(BinarySearchTreeTest, cloneTest) {
        ostringstream osm0, osm1, osm2, osm3, testDataOsm;

        BinarySearchTree * _t0  = new BinarySearchTree();
        BinarySearchTree2 * _t1 = new BinarySearchTree2();
        AvlTree * _t2           = new AvlTree();
        RBTree * _t3            = new RBTree();

        // 通过等号运算符重载运行clone
        *_t0 = *t0_;
        *_t1 = *t1_;
        *_t2 = *t2_;
        *_t3 = *t3_;

        t0_->makeEmpty();
        t1_->makeEmpty();
        t2_->makeEmpty();
        t3_->makeEmpty();

        _t0->traversal(osm0);
        _t1->traversal(osm1);
        _t2->traversal(osm2);
        _t3->traversal(osm3);

        sort(testData.begin(), testData.end(), less<int>());
        vector<int>::const_iterator iter = testData.begin();
        while (iter != testData.end()) {
            testDataOsm << *iter << ",";
            ++iter;
        }

        ASSERT_EQ(testDataOsm.str(), osm0.str());
        ASSERT_EQ(testDataOsm.str(), osm1.str());
        ASSERT_EQ(testDataOsm.str(), osm2.str());
        ASSERT_EQ(testDataOsm.str(), osm3.str());
    }

    // rbtree insert test
    TEST_F(BinarySearchTreeTest, RBTreeInsertTest) {
        //printPretty(t3_->root, 4, 0, cout);

        t3_->insert(22);
        t3_->insert(6);
        t3_->insert(11);
        t3_->insert(16);
        t3_->insert(21);
        t3_->insert(23);
        t3_->insert(26);
        t3_->insert(29);
        t3_->insert(1);

        vector<RBNode *> vecrb;
        t3_->preOrder(vecrb);
        vector<RBNode *>::iterator iter = vecrb.begin();

        //printPretty(t3_->root, 3, 0, cout);

        // 红黑树特征测试
        // 特征1. 每个节点，不是红色就使黑色；
        iter  = vecrb.begin();
        while (iter != vecrb.end()) {
            ASSERT_GE(BLACK_COLOR, ((RBNode *)(*iter))->color);
            ASSERT_LE(RED_COLOR, ((RBNode *)(*iter))->color);
            ++iter;
        }

        // 特征2：根节点是黑色
        ASSERT_EQ(BLACK_COLOR, t3_->root->color);

        // 特征3：每个叶节点（NIL）都是黑色的；
        // 一直成立

        // 特征4：如果一个节点是红的，那么它的两个子节点都使黑色的；
        iter  = vecrb.begin();
        RBNode * cn, * ln, *rn;
        while (iter != vecrb.end()) {
            cn = (RBNode *)(*iter);
            ln = (RBNode *)((RBNode *)(*iter)->left);
            rn = (RBNode *)((RBNode *)(*iter)->right);

            if ( cn !=NULL && cn->color == RED_COLOR) {
                if ((*iter)->left != NULL)
                    ASSERT_EQ(BLACK_COLOR, ln->color);

                if ((*iter)->right !=NULL)
                    ASSERT_EQ(BLACK_COLOR, rn->color);
            }
            ++iter;
        }

        // 特征5：对于每个节点，从该节点到其后代节点的简单路径，均含有相同数目黑
        // 色节点；
        iter  = vecrb.begin();
        const RBNode * cln, * crn;
        int lbn(0), rbn(0);
        while (iter != vecrb.end()) {
            cln = (const RBNode *)((RBNode *)(*iter)->left);
            crn = (const RBNode *)((RBNode *)(*iter)->right);

            if (cln != NULL)
                lbn = t3_->getBlackHeight(cln);
            else
                lbn = 1;

            if (crn !=NULL)
                rbn = t3_->getBlackHeight(crn);
            else
                rbn = 1;

            ASSERT_TRUE(lbn == rbn);

            ++iter;
        }
    }

    // rbtree remove test
    TEST_F(BinarySearchTreeTest, RBTreeRemoveTest) {
        //printPretty(t3_->root, 4, 0, cout);

        printPretty(t3_->root, 4, 0, cout);
        t3_->remove(30);
        printPretty(t3_->root, 4, 0, cout);
        t3_->remove(20);
        printPretty(t3_->root, 4, 0, cout);
/*        t3_->remove(40);*/
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(10);
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(25);
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(35);
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(50);
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(5);
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(15);
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(28);
        //printPretty(t3_->root, 4, 0, cout);
        //t3_->remove(41);
        /*printPretty(t3_->root, 4, 0, cout);*/
/*
        vector<RBNode *> vecrb;
        t3_->preOrder(vecrb);
        vector<RBNode *>::iterator iter = vecrb.begin();

        //printPretty(t3_->root, 3, 0, cout);

        // 红黑树特征测试
        // 特征1. 每个节点，不是红色就使黑色；
        iter  = vecrb.begin();
        while (iter != vecrb.end()) {
            ASSERT_GE(BLACK_COLOR, ((RBNode *)(*iter))->color);
            ASSERT_LE(RED_COLOR, ((RBNode *)(*iter))->color);
            ++iter;
        }

        // 特征2：根节点是黑色
        ASSERT_EQ(BLACK_COLOR, t3_->root->color);

        // 特征3：每个叶节点（NIL）都是黑色的；
        // 一直成立

        // 特征4：如果一个节点是红的，那么它的两个子节点都使黑色的；
        iter  = vecrb.begin();
        RBNode * cn, * ln, *rn;
        while (iter != vecrb.end()) {
            cn = (RBNode *)(*iter);
            ln = (RBNode *)((RBNode *)(*iter)->left);
            rn = (RBNode *)((RBNode *)(*iter)->right);

            if ( cn !=NULL && cn->color == RED_COLOR) {
                if ((*iter)->left != NULL)
                    ASSERT_EQ(BLACK_COLOR, ln->color);

                if ((*iter)->right !=NULL)
                    ASSERT_EQ(BLACK_COLOR, rn->color);
            }
            ++iter;
        }

        // 特征5：对于每个节点，从该节点到其后代节点的简单路径，均含有相同数目黑
        // 色节点；
        iter  = vecrb.begin();
        const RBNode * cln, * crn;
        int lbn(0), rbn(0);
        while (iter != vecrb.end()) {
            cln = (const RBNode *)((RBNode *)(*iter)->left);
            crn = (const RBNode *)((RBNode *)(*iter)->right);

            if (cln != NULL)
                lbn = t3_->getBlackHeight(cln);
            else
                lbn = 1;

            if (crn !=NULL)
                rbn = t3_->getBlackHeight(crn);
            else
                rbn = 1;

            ASSERT_TRUE(lbn == rbn);

            ++iter;
        } */
    }
////////////////////////////////////////////////////////////////////////////////

} // namespace

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
