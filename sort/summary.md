# 排序部分小结

## 回顾
排序算法主要分为_基于比较的排序_和_线性时间排序_, 也就是说_基于比较的排序_有个时间复杂度下限。

### 基于比较的排序
如果把_基于比较的排序_过程用_决策树_来表示，可以得到一个二叉树，且具有N个待比较元素的决策树最坏情况下至少需要_log(N!)_次比较，因为深度为d的二叉树，最多有2^d片树叶, 其实比较的次数也就是树的平均深度。

根据公式变换，最坏情况下，_基于比较的排序_需要NLogN次比较，也就是说时间复杂度是O(NlogN)。

决策树模型:

![决策树](http://jing4seven.github.io/assets/images/decision.tree.jpg)

本节中属于_基于比较的排序_的有：

> * 插入排序
> * 快速排序
> * 归并排序
> * 堆排序
> * 希尔排序

### 线性时间排序

线性时间排序没有_基于比较的排序_的下限，所以在时间上复杂度上，更有优势，能够达到O(N)。但是，_线性时间排序_依赖于数据集合中某些特征，所以并不是所有的场合都适用。另外，_线性时间排序_中有些是需要额外的空间来临时保存中间结果，所以这些也成为它的劣势。

本节中属于_线性排序_的有：

> * 计数排序
> * 基数排序
> * 桶排序

## 分析

### 时间复杂度

| 算法       | 最坏情况运行时间  | 平均情况/期望运行时间  |
| ---------- | ----------------: | ---------------------: |
| 插入排序   | Theta(n^2)        | Theta(n^2)             |
| 归并排序   | Theta(nlogn)      | Theta(nlogn)           |
| 堆排序     | O(nlogn)          | --                     |
| 快速排序   | Theta(n^2)        | Theta(nlogn)（期望）   |
| 希尔排序   | O(n^2)            | --                     |
| 计数排序   | Theta(k+n)        | Theta(k+n)             |
| 基数排序   | Theta(d(n+k))     | Theta(d(n+k))          |
| 桶排序     | Theta(n^2)        | Theta(n)（平均情况）   |

上表中计数排序中的k表示带排集合中最大数，基数排序中的k代表基数。
