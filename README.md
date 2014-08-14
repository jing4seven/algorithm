# 算法知识梳理与实践

数据结构与算法是计算机软件工程的基石，好比武功秘籍九阳神功。夯实理论最好的办法就是实践，创建这个Repository，是希望创建一个循序渐进的实践环境，以便逐步掌握整个理论知识体系。

算法基于c++实现，大部分都用到了STL，部分算法给出了相应的`UNIT TEST`,都基于[googletest](https://code.google.com/p/googletest/)实现。

## 大纲

1. 排序
    * 基于比较的排序（非线性时间）
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
    * 线性时间排序
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
    * DFS（广度优先搜索）
        * [C++](https://github.com/jing4seven/algorithm/blob/master/search/bfs.cc)
    * BFS（深度优先搜索）
        * [C++](https://github.com/jing4seven/algorithm/blob/master/search/dfs.cc)
    * [UNIT TEST](https://github.com/jing4seven/algorithm/blob/master/search/unit.test.search.cc)
    * 小结
5. 图算法
    * 图接口的定义
        * [C++](https://github.com/jing4seven/algorithm/blob/master/graph/graph.definition.md)
        * [C++ header 邻接表实现](https://github.com/jing4seven/algorithm/blob/master/graph/graph.h)
        * [C++ header 邻接矩阵实现](https://github.com/jing4seven/algorithm/blob/master/graph/graph_matrix.h)
    * 最小生成树
        * Kruskal 算法
            * [C++ 基于邻接矩阵实现](https://github.com/jing4seven/algorithm/blob/master/graph/kruskal.mst.cc)
        * Prim 算法
            * [C++ 基于邻接矩阵实现](https://github.com/jing4seven/algorithm/blob/master/graph/prim.mst.cc)
    * 单源最短路径
        * Bellman-Ford 算法
        * Dijkstra 算法
    * 所有节点对的最短路径问题
        * Floyd-Warshall算法
    * 最大流
        * Ford-Fulkerson算法
    * 小结
6. 分析方法
    * 动态规划
    * 贪心法
    * 小结
7. 算法应用
    * 多线程算法
    * 矩阵运算
    * 线性规划
    * 数论算法
    * 字符串匹配
        * Rabin-Karp算法
        * DFA（有限状态自动机）算法
        * Knuth-Morris-Pratt算法
    * 几何算法
    * NP完全性
    * 近似算法
    * 小结
8. 资源
    * [googletest](https://github.com/jing4seven/algorithm/blob/master/res/googletest.setup.md)

## 参考
1. [算法导论 （第三版）](http://www.amazon.cn/%E7%AE%97%E6%B3%95%E5%AF%BC%E8%AE%BA-Thomas-H-Cormen/dp/B00AK7BYJY/ref=sr_1_1?ie=UTF8&qid=1410230607&sr=8-1&keywords=%E7%AE%97%E6%B3%95%E5%AF%BC%E8%AE%BA) 
2. [算法精解](http://www.amazon.cn/%E7%AE%97%E6%B3%95%E7%B2%BE%E8%A7%A3-C%E8%AF%AD%E8%A8%80%E6%8F%8F%E8%BF%B0-Kyle-Loudon/dp/B00E87TVL0/ref=sr_1_5?ie=UTF8&qid=1410230731&sr=8-5&keywords=%E7%AE%97%E6%B3%95)
3. [数据结构与算法分析：C++描述（第3版）](http://item.jd.com/10062313.html)
