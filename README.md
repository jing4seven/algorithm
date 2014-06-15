# 算法复习

> 创建这个Repository，是为了让最近复习的算法知识能够印象更加深刻。 
> 代码全部用C/C++实现， 至少一种实现方法。

## 大纲

1. 排序
    * 插入排序
        * [基于STL的实现](https://github.com/jing4seven/algorithm/blob/master/sort/insertsort.cc)
    * 归并排序
        * [基于STL的实现](https://github.com/jing4seven/algorithm/blob/master/sort/mergesort.cc)
    * 快速排序
        * [基于STL的实现, 随机选取中间值](https://github.com/jing4seven/algorithm/blob/master/sort/quicksort.cc)
        * [基于STL的实现, 选取固定中间值](https://github.com/jing4seven/algorithm/blob/master/sort/quicksort2.cc)
    * 堆排序
        * [基于STL的实现](https://github.com/jing4seven/algorithm/blob/master/sort/heapsort.cc)
    * 希尔排序
        * [基于STL的实现](https://github.com/jing4seven/algorithm/blob/master/sort/shellsort.cc)
    * 计数排序
        * [基于STL的实现](https://github.com/jing4seven/algorithm/blob/master/sort/countsort.cc)
    * 基数排序
        * [基于STL的实现](https://github.com/jing4seven/algorithm/blob/master/sort/radixsort.cc)
    * 桶排序
        * [基于STL的实现](https://github.com/jing4seven/algorithm/blob/master/sort/bucksort.cc)
    * [小结](https://github.com/jing4seven/algorithm/blob/master/sort/summary.md)
2. 散列
    * key为整数的散列
        * [除法散列(Division hashing)](https://github.com/jing4seven/algorithm/blob/master/hash/divi.hash.cc)
        * [乘法散列(Multiplication hashing)](https://github.com/jing4seven/algorithm/blob/master/hash/mult.hash.cc)
        * [全域散列(Universal hashing)](https://github.com/jing4seven/algorithm/blob/master/hash/uni.hash.cc)
    * key为字符串的散列
        * [BKDRHash](#)
        * [DJBHash](#)
        * [JSHash](#)
        * [RSHash](#)
        * [SDBMHash](#)
        * [PJWHash](https://github.com/jing4seven/algorithm/blob/master/hash/str.hash.ins1.cc)
        * [ELFHash](#)
    * 解决冲突的方法
        * [分离链接法](https://github.com/jing4seven/algorithm/blob/master/hash/linked.list.hashtable.cc)
        * 不使用链表的方法
            * [开放寻址发(Open addressing)](https://github.com/jing4seven/algorithm/blob/master/hash/open.addressing.cc)
            * [二次探测(Quadratic probing)](https://github.com/jing4seven/algorithm/blob/master/hash/quadratic.probing.cc)
            * [双重探测(Secondary clustering)](https://github.com/jing4seven/algorithm/blob/master/hash/secondary.clustering.cc)
    * [小结](https://github.com/jing4seven/algorithm/blob/master/hash/summary.md)
3. 树数据结构
    * 二叉查找树
        * [基于C++通过传值维护变更](https://github.com/jing4seven/algorithm/blob/master/tree/search.tree.cc)
        * [基于C++通过替换节点维护变更](https://github.com/jing4seven/algorithm/blob/master/tree/test.for.search.tree.cc)
    * 二叉平衡树(AVL)
    * 红黑树
    * B树
    * 小结
4. 搜索
    * 二分搜索
    * 广度优先搜索
    * 深度优先搜索
    * 小结
5. 分析方法
    * 动态规划
    * 贪心法
    * 摊还分析
    * 小结
6. 图算法
    * 最小生成树（Prim和Kruskal算法）
    * 单源最短路径（Bellman-Ford和Dijkstra算法）
    * 所有节点的最短路径问题
    * 最大流（Ford-Fulkerson算法）
    * 小结
7. 特殊算法
    * NP完全问题
    * 近似算法
    * 小结


