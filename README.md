# 算法复习

创建这个Repository，是为了让最近复习的算法知识能够印象更加深刻。代码全部用C/C++实现， 至少一种实现方法。

每种算法/模型都有相应的`UNIT TEST`,都基于[googletest](https://code.google.com/p/googletest/)实现。

## 大纲

1. 排序
    * 插入排序
        * [C++](https://github.com/jing4seven/algorithm/blob/master/sort/insertsort.cc)
    * 归并排序
        * [C++](https://github.com/jing4seven/algorithm/blob/master/sort/mergesort.cc)
    * 快速排序
        * [C++, 随机选取中间值](https://github.com/jing4seven/algorithm/blob/master/sort/quicksort.cc)
        * [C++, 选取固定中间值](https://github.com/jing4seven/algorithm/blob/master/sort/quicksort2.cc)
    * 堆排序
        * [C++](https://github.com/jing4seven/algorithm/blob/master/sort/heapsort.cc)
    * 希尔排序
        * [C++](https://github.com/jing4seven/algorithm/blob/master/sort/shellsort.cc)
    * 计数排序
        * [C++](https://github.com/jing4seven/algorithm/blob/master/sort/countsort.cc)
    * 基数排序
        * [C++](https://github.com/jing4seven/algorithm/blob/master/sort/radixsort.cc)
    * 桶排序
        * [C++](https://github.com/jing4seven/algorithm/blob/master/sort/bucksort.cc)
    * [UNIT TEST](https://github.com/jing4seven/algorithm/blob/master/sort/unit.test.sort.cc)
    * [小结](https://github.com/jing4seven/algorithm/blob/master/sort/summary.md)
2. 散列
    * key为整数的散列
        * [除法散列(Division hashing)](https://github.com/jing4seven/algorithm/blob/master/hash/divi.hash.cc)
        * [乘法散列(Multiplication hashing)](https://github.com/jing4seven/algorithm/blob/master/hash/mult.hash.cc)
        * [全域散列(Universal hashing)](https://github.com/jing4seven/algorithm/blob/master/hash/uni.hash.cc)
    * key为字符串的散列
        * [BKDRHash]
        * [DJBHash]
        * [JSHash]
        * [RSHash]
        * [SDBMHash]
        * [PJWHash](https://github.com/jing4seven/algorithm/blob/master/hash/str.hash.ins1.cc)
        * [ELFHash]
    * 解决冲突的方法
        * [分离链接法](https://github.com/jing4seven/algorithm/blob/master/hash/linked.list.hashtable.cc)
        * 不使用链表的方法
            * [开放寻址发(Open addressing)]
            * [二次探测(Quadratic probing)]
            * [双重探测(Secondary clustering)]
    * [小结](https://github.com/jing4seven/algorithm/blob/master/hash/summary.md)
3. 树数据结构
    * 树接口的定义
        * [C++](https://github.com/jing4seven/algorithm/blob/master/tree/tree.definition.md)
    * 二叉查找树
        * [C++ 物理删除 header](https://github.com/jing4seven/algorithm/blob/master/tree/search.tree.h)
        * [C++,物理删除](https://github.com/jing4seven/algorithm/blob/master/tree/search.tree.cc)
        * [C++ 惰性删除 header](https://github.com/jing4seven/algorithm/blob/master/tree/search.tree2.h)
        * [C++,惰性删除](https://github.com/jing4seven/algorithm/blob/master/tree/search.tree2.cc)
    * 二叉平衡树(AVL)
        * [C++ header](https://github.com/jing4seven/algorithm/blob/master/tree/avl.tree.h)
        * [C++](https://github.com/jing4seven/algorithm/blob/master/tree/avl.tree.cc)
    * 红黑树
        * [C++ header](https://github.com/jing4seven/algorithm/blob/master/tree/rb.tree.h)
        * [C++](https://github.com/jing4seven/algorithm/blob/master/tree/rb.tree.cc)
    * B树
    * [UNIT TEST](https://github.com/jing4seven/algorithm/blob/master/tree/unit.test.tree.cc)
    * 小结
4. 搜索
    * 二分搜索
        * [C++](https://github.com/jing4seven/algorithm/blob/master/search/binary.search.cc)
    * 广度优先搜索
        * [C++](https://github.com/jing4seven/algorithm/blob/master/search/bfs.cc)
    * 深度优先搜索
        * [C++](https://github.com/jing4seven/algorithm/blob/master/search/dfs.cc)
    * [UNIT TEST](https://github.com/jing4seven/algorithm/blob/master/search/unit.test.search.cc)
    * 小结
5. 分析方法
    * 动态规划
    * 贪心法
    * 小结
6. 图算法
    * 图接口的定义
        * [C++](https://github.com/jing4seven/algorithm/blob/master/graph/graph.definition.md)
    * 最小生成树
        * Dijkstra 算法
        * Prim 算法
        * Kruskal 算法
    * 单源最短路径
        * Bellman-Ford 算法
        * Dijkstra 算法
    * 所有节点的最短路径问题
    * 最大流（Ford-Fulkerson算法）
    * 小结
7. 特殊算法
    * NP完全问题
    * 近似算法
    * 小结
8. 资源
    * [googletest](https://github.com/jing4seven/algorithm/blob/master/res/googletest.setup.md)
