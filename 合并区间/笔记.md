

---

# LeetCode 56. 合并区间 学习笔记

## 1. 题目描述

给定一个区间集�?`intervals`，其中每个区间表示为�?

```text
[start, end]
```

要求合并所有重叠的区间，并返回一�?**不重叠的区间数组**，该数组恰好覆盖输入中的所有区间�?

---

## 2. 示例

### 示例 1

```text
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
```

解释�?

* `[1,3]` �?`[2,6]` 有重�?
* 合并后变�?`[1,6]`

---

### 示例 2

```text
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
```

解释�?

* `[1,4]` �?`[4,5]` 在端点处相接
* 按题意可视为重叠，可以合并成 `[1,5]`

---

### 示例 3

```text
输入：intervals = [[4,7],[1,4]]
输出：[[1,7]]
```

解释�?

* 排序后为 `[[1,4],[4,7]]`
* 两个区间相接，可合并�?`[1,7]`

---

## 3. 题目本质

这题本质上是在问�?

> 如何把一组可能乱序、可能重叠的区间整理成若干个互不重叠的大区间�?

关键点有两个�?

1. 区间�?**乱序�?*
2. 只有在区间有序后，才能高效判断“当前区间和下一个区间是否重叠�?

所以这题最核心的第一步就是：

> **先排�?*

---

## 4. 为什么必须先排序

假设区间乱序�?

```text
[[8,10],[1,3],[2,6],[15,18]]
```

如果不排序，你很难直接知道：

* `[1,3]` 应该和谁合并
* `[2,6]` 又会不会和更后面的区间相�?

但如果先按左端点排序�?

```text
[[1,3],[2,6],[8,10],[15,18]]
```

那么只需要从左到右扫描，就能逐个决定�?

* 和当前合并区间重�?�?扩展右端�?
* 不重�?�?把当前区间存起来，开始新区间

所以这题的标准套路就是�?

> **排序 + 一次线性扫�?*

---

## 5. 核心思路

---

## 5.1 先按区间左端点升序排�?

例如�?

```text
[[1,3],[2,6],[8,10],[15,18]]
```

排序后仍然是�?

```text
[[1,3],[2,6],[8,10],[15,18]]
```

---

## 5.2 维护当前正在合并的区�?

设当前正在合并的区间为：

```text
[start, end]
```

然后依次看后面的区间 `[l, r]`

### 情况 1：有重叠

如果�?

```text
l <= end
```

说明新区间和当前区间有交集，或者在端点处相接，可以合并�?

此时更新�?

```text
end = max(end, r)
```

---

### 情况 2：没有重�?

如果�?

```text
l > end
```

说明新区间和当前区间完全分开�?

此时�?

* 先把当前区间 `[start, end]` 加入结果
* 再把 `[l, r]` 作为新的当前区间

---

## 6. 标准算法流程

1. 按左端点对所有区间排�?
2. �?`start` �?`end` 表示当前正在合并的区�?
3. 从第二个区间开始遍历：

   * 如果能合并，更新 `end`
   * 否则把当前区间加入结果，并开始新区间
4. 遍历结束后，别忘了把最后一个区间加入结�?

---

## 7. C语言代码实现（标准写法）

```c
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int* row_a = *(int**)a;
    int* row_b = *(int**)b;
    return row_a[0] - row_b[0];
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    int** result = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));
    *returnSize = 0;

    int start = intervals[0][0];
    int end = intervals[0][1];

    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][0] <= end) {
            if (intervals[i][1] > end) {
                end = intervals[i][1];
            }
        } else {
            result[*returnSize] = (int*)malloc(2 * sizeof(int));
            result[*returnSize][0] = start;
            result[*returnSize][1] = end;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;

            start = intervals[i][0];
            end = intervals[i][1];
        }
    }

    result[*returnSize] = (int*)malloc(2 * sizeof(int));
    result[*returnSize][0] = start;
    result[*returnSize][1] = end;
    (*returnColumnSizes)[*returnSize] = 2;
    (*returnSize)++;

    return result;
}
```

---

## 8. 基于你原写法的修正版

你原来是这种思路�?

* 每次�?`intervals[i]` 为当前区间起�?
* 然后�?`while` 一路向后吞并所有有重叠的区�?

这种写法也是对的，只要修好内存分配问题即可�?

```c
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int* row_a = *(int**)a;
    int* row_b = *(int**)b;
    return (row_a[0] > row_b[0]) - (row_a[0] < row_b[0]);
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    int** result = (int**)malloc(intervalsSize * sizeof(int*));

    for (int i = 0; i < intervalsSize; i++) {
        result[*returnSize] = (int*)malloc(2 * sizeof(int));

        result[*returnSize][0] = intervals[i][0];
        int max = intervals[i][1];

        while (i + 1 < intervalsSize && max >= intervals[i + 1][0]) {
            i++;
            if (max < intervals[i][1]) {
                max = intervals[i][1];
            }
        }

        result[*returnSize][1] = max;
        (*returnSize)++;
    }

    *returnColumnSizes = (int*)malloc(*returnSize * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    return result;
}
```

---

## 9. 你原代码运行出问题的原因

你原来最大的问题是：

```c
int** result = (int**)malloc(intervalsSize * sizeof(int*));
```

这里只给“第一层指针数组”分配了空间�?

但是你后面直接写�?

```c
result[*returnSize][0] = intervals[i][0];
result[*returnSize][1] = max;
```

此时 `result[*returnSize]` 还是一个未初始化指针，没有指向有效内存，所以会发生�?

* 野指针访�?
* 程序崩溃
* 运行错误

正确写法必须先给每一行分配空间：

```c
result[*returnSize] = (int*)malloc(2 * sizeof(int));
```

然后才能�?`result[*returnSize][0]` �?`result[*returnSize][1]`

---

## 10. 为什么这题里 `intervalsColSize` 基本没用

LeetCode 这类二维数组题常常统一提供参数�?

```c
int* intervalsColSize
```

表示输入二维数组中每一行的列数�?

但这题已经保证：

```text
intervals[i].length == 2
```

所以每个区间一定就是两个数�?

* `intervals[i][0]`
* `intervals[i][1]`

因此在本题中，这个参数通常**不用也没问题**�?

真正需要你返回的是�?

```c
*returnColumnSizes
```

它表示输出二维数组每一行的列数，这里每一行也都是 `2`�?

---

## 11. 结合示例理解过程

以：

```text
intervals = [[1,3],[2,6],[8,10],[15,18]]
```

为例�?

---

### 第一步：排序

排序后：

```text
[[1,3],[2,6],[8,10],[15,18]]
```

---

### 第二步：初始化当前区�?

当前区间为：

```text
[start, end] = [1,3]
```

---

### 第三步：遍历后续区间

#### �?`[2,6]`

因为�?

```text
2 <= 3
```

说明和当前区间有重叠�?

更新�?

```text
end = max(3, 6) = 6
```

当前区间变成�?

```text
[1,6]
```

---

#### �?`[8,10]`

因为�?

```text
8 > 6
```

说明不重叠�?

所以先�?`[1,6]` 放入结果，再开始新区间�?

```text
[start, end] = [8,10]
```

---

#### �?`[15,18]`

因为�?

```text
15 > 10
```

不重叠�?

�?`[8,10]` 放入结果，再开始新区间�?

```text
[start, end] = [15,18]
```

---

### 第四步：遍历结束

别忘了把最后一个区�?`[15,18]` 放入结果�?

最终结果：

```text
[[1,6],[8,10],[15,18]]
```

---

## 12. 复杂度分�?

### 时间复杂�?

* 排序：`O(n log n)`
* 扫描合并：`O(n)`

总复杂度�?

```text
O(n log n)
```

---

### 空间复杂�?

* 返回结果数组：`O(n)`
* 如果不把返回结果算入额外空间，则扫描部分只用了常数变�?

通常写作�?

```text
O(n)
```

---

## 13. 这两种写法的优缺�?

---

### 13.1 你的修正版优�?

* 更贴近你原来的思路
* 改动�?
* 更容易理解“原来错的是内存分配，不是整体思路�?

### 13.2 你的修正版缺�?

* `for` 里面又修�?`i`，可读性稍�?
* 以后扩展逻辑时更容易出边界问�?

---

### 13.3 标准写法优点

* 逻辑更清�?
* `i` 只在 `for` 中变�?
* 更适合当模板记�?
* 更适合面试表达

### 13.4 标准写法缺点

* 对刚开始写这题的人来说，稍微抽象一�?
* 要注意遍历结束后补存最后一个区�?

---

## 14. 易错点总结

### 14.1 必须先排�?

不排序就无法高效判断重叠关系�?

---

### 14.2 判断重叠条件是：

```text
intervals[i][0] <= end
```

注意这里�?`<=`，因为端点相接也算重叠�?

例如�?

```text
[1,4] �?[4,5]
```

应合并成�?

```text
[1,5]
```

---

### 14.3 二维返回数组要给每一行单独分配空�?

错误写法�?

```c
int** result = malloc(n * sizeof(int*));
result[i][0] = ...
```

这里 `result[i]` 还没分配空间，会崩�?

正确写法�?

```c
result[i] = malloc(2 * sizeof(int));
```

---

### 14.4 别改 `intervalsColSize`

这个是输入参数，不需要修改�?

你要设置的是�?

```c
*returnColumnSizes
```

---

### 14.5 标准写法别忘了加入最后一个区�?

很多人会在循环中只处理“遇到不重叠就存”，结果漏掉最后一段�?

---

## 15. 这道题的模板思想

以后遇到这类题：

* 区间问题
* 合并重叠区间
* 插入新区�?
* 统计不重叠区间数�?

通常第一反应应该是：

> **先排序，再扫�?*

区间题里，“排序”几乎是最重要的第一步�?

---

## 16. 面试答题模板

如果面试官问你思路，可以这样回答：

> 这题要求合并所有重叠区间，标准做法是先按区间左端点升序排序�?
> 排序后，重叠区间一定会相邻出现�?
> 接着从左到右扫描，维护当前正在合并的区间 `[start, end]`�?
> 如果下一个区间的左端点小于等于当�?`end`，说明有重叠，可以合并，并更�?`end = max(end, nextEnd)`�?
> 否则说明没有重叠，就把当前区间加入结果，并开始新的区间�?
> 最后再把最后一个区间加入结果即可�?
> 排序复杂度是 `O(n log n)`，扫描是 `O(n)`，总复杂度�?`O(n log n)`�?

---

## 17. 一句话总结

> **合并区间 = 先按左端点排序，再线性扫描合并相邻重叠区�?*

---

## 18. 适合记住的结�?

### 结论 1

区间合并题，第一步通常�?**排序**�?

### 结论 2

排序后，只需要关心“当前区间”和“下一个区间”是否重叠�?

### 结论 3

重叠条件是：

```text
下一个区间左端点 <= 当前区间右端�?
```

### 结论 4

二维返回数组中，每一行都要单�?`malloc`�?

### 结论 5

本题最优时间复杂度是：

```text
O(n log n)
```

因为排序无法省掉�?

---

