# LeetCode 56. 合并区间 学习笔记

## 题目描述

给定一个区间集合 `intervals`，其中每个区间表示为：

Plaintext

```
[start, end]
```

要求合并所有重叠的区间，并返回一个 **不重叠的区间数组**，该数组恰好覆盖输入中的所有区间。

------

## 示例

### 示例 1

Plaintext

```
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
```

解释：

- `[1,3]` 和 `[2,6]` 有重叠
- 合并后变成 `[1,6]`

------

### 示例 2

Plaintext

```
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
```

解释：

- `[1,4]` 和 `[4,5]` 在端点处相接
- 按题意可视为重叠，可以合并成 `[1,5]`

------

### 示例 3

Plaintext

```
输入：intervals = [[4,7],[1,4]]
输出：[[1,7]]
```

解释：

- 排序后为 `[[1,4],[4,7]]`
- 两个区间相接，可合并为 `[1,7]`

------

## 题目本质

这题本质上是在问：

> 如何把一组可能乱序、可能重叠的区间整理成若干个互不重叠的大区间？

关键点有两个：

1. 区间是 **乱序的**
2. 只有在区间有序后，才能高效判断“当前区间和下一个区间是否重叠”

所以这题最核心的第一步就是：

> **先排序**

------

## 为什么必须先排序

假设区间乱序时：

Plaintext

```
[[8,10],[1,3],[2,6],[15,18]]
```

如果不排序，你很难直接知道：

- `[1,3]` 应该和谁合并
- `[2,6]` 又会不会和更后面的区间相连

但如果先按左端点排序：

Plaintext

```
[[1,3],[2,6],[8,10],[15,18]]
```

那么只需要从左到右扫描，就能逐个决定：

- 和当前合并区间重叠？ 扩展右端点
- 不重叠？ 把当前区间存起来，开始新区间

所以这题的标准套路就是：

> **排序 + 一次线性扫描**

------

##  核心思路

###  先按区间左端点升序排序

例如：

Plaintext

```
[[1,3],[2,6],[8,10],[15,18]]
```

排序后仍然是：

Plaintext

```
[[1,3],[2,6],[8,10],[15,18]]
```

###  维护当前正在合并的区间

设当前正在合并的区间为：

Plaintext

```
[start, end]
```

然后依次看后面的区间 `[l, r]`

#### 情况 1：有重叠

如果是：

Plaintext

```
l <= end
```

说明新区间和当前区间有交集，或者在端点处相接，可以合并。

此时更新：

Plaintext

```
end = max(end, r)
```

------

#### 情况 2：没有重叠

如果：

Plaintext

```
l > end
```

说明新区间和当前区间完全分开。

此时：

- 先把当前区间 `[start, end]` 加入结果
- 再把 `[l, r]` 作为新的当前区间

------

##  标准算法流程

1. 按左端点对所有区间排序
2. 用 `start` 和 `end` 表示当前正在合并的区间
3. 从第二个区间开始遍历：
   - 如果能合并，更新 `end`
   - 否则把当前区间加入结果，并开始新区间
4. 遍历结束后，别忘了把最后一个区间加入结果

------

## C语言代码实现（标准写法）

C

```
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int* row_a = *(int**)a;
    int* row_b = *(int**)b;
    return row_a[0] - row_b[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

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

------

## 基于你原写法的修正版

你原来是这种思路：

- 每次以 `intervals[i]` 为当前区间起点
- 然后用 `while` 一路向后吞并所有有重叠的区间

这种写法也是对的，只要修好内存分配问题即可。

C

```
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int* row_a = *(int**)a;
    int* row_b = *(int**)b;
    return (row_a[0] > row_b[0]) - (row_a[0] < row_b[0]);
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

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

------

##你原代码运行出问题的原因

你原来最大的问题是：

C

```
int** result = (int**)malloc(intervalsSize * sizeof(int*));
```

这里只给“第一层指针数组”分配了空间。

但是你后面直接写道：

C

```
result[*returnSize][0] = intervals[i][0];
result[*returnSize][1] = max;
```

此时 `result[*returnSize]` 还是一个未初始化指针，没有指向有效内存，所以会发生：

- 野指针访问
- 程序崩溃
- 运行错误

正确写法必须先给每一行分配空间：

C

```
result[*returnSize] = (int*)malloc(2 * sizeof(int));
```

然后才能访问 `result[*returnSize][0]` 和 `result[*returnSize][1]`。

------

## 为什么这题里 `intervalsColSize` 基本没用

LeetCode 这类二维数组题常常统一提供参数：

C

```
int* intervalsColSize
```

表示输入二维数组中每一行的列数。

但这题已经保证：

Plaintext

```
intervals[i].length == 2
```

所以每个区间一定就是两个数。

真正需要你设置的是：

C

```
*returnColumnSizes
```

它表示输出二维数组每一行的列数，这里每一行也都是 2。

------

## 结合示例理解过程

以 `intervals = [[1,3],[2,6],[8,10],[15,18]]` 为例：

###  第一步：排序

排序后：`[[1,3],[2,6],[8,10],[15,18]]`

###  第二步：初始化当前区间

当前区间为：`[start, end] = [1,3]`

### 第三步：遍历后续区间

- **对于 `[2,6]`**：

  因为 `2 <= 3`，说明有重叠。更新 `end = max(3, 6) = 6`。当前区间变成 `[1,6]`。

- **对于 `[8,10]`**：

  因为 `8 > 6`，说明不重叠。将 `[1,6]` 放入结果，再开始新区间：`[start, end] = [8,10]`。

- **对于 `[15,18]`**：

  因为 `15 > 10`，不重叠。将 `[8,10]` 放入结果，再开始新区间：`[start, end] = [15,18]`。

###  第四步：遍历结束

别忘了把最后一个区间 `[15,18]` 放入结果。最终结果：`[[1,6],[8,10],[15,18]]`

------

## 复杂度分析

### 时间复杂度

- 排序：`O(n log n)`
- 扫描合并：`O(n)`
- 总复杂度为：`O(n log n)`

### 空间复杂度

- 返回结果数组：`O(n)`
- 通常写作：`O(n)`

------

## 这两种写法的优缺点

###  你的修正版优点

- 更贴近你原来的思路，改动小。

### 你的修正版缺点

- `for` 里面又修改 `i`，可读性稍差，容易出边界问题。

###  标准写法优点

- 逻辑更清晰，`i` 只在 `for` 中变化，更适合当模板记忆和面试表达。

### 标准写法缺点

- 对刚学的人来说稍显抽象，要注意遍历结束后补存最后一个区间。

------

## 易错点总结

1. **必须先排序**：不排序无法高效判断重叠关系。
2. **判断重叠条件是**：`intervals[i][0] <= end`。注意是 `<=`，端点相接也算重叠。
3. **二维返回数组要给每一行单独分配空间**：不能直接给 `result[i][0]` 赋值，必须先 `malloc` 行空间。
4. **别改 `intervalsColSize`**：那是输入参数，不需要修改。
5. **标准写法别忘了加入最后一个区间**：循环结束后的补存操作非常关键。

------

##  这道题的模板思想

以后遇到区间问题、合并重叠区间、插入新区间、统计不重叠区间数量：

> **先排序，再扫描**

------

## 面试答题模板

> 这题要求合并所有重叠区间，标准做法是先按区间左端点升序排序。排序后，重叠区间一定会相邻出现。
>
> 接着从左到右扫描，维护当前正在合并的区间 `[start, end]`。
>
> 如果下一个区间的左端点小于等于当前 `end`，说明有重叠，更新 `end = max(end, nextEnd)`。
>
> 否则说明没有重叠，就把当前区间加入结果，并开始新的区间。
>
> 最后把最后一个区间加入结果。总复杂度为 `O(n log n)`。

------

##  一句话总结

> **合并区间 = 先按左端点排序，再线性扫描合并相邻重叠区间。**

------

## 适合记住的结论

1. 区间合并题，第一步通常是 **排序**。
2. 排序后，只需要关心当前区间和下一个区间是否重叠。
3. 重叠条件是：`下一个区间左端点 <= 当前区间右端点`。
4. 二维返回数组中，每一行都要单独 `malloc`。
5. 本题最优时间复杂度是 `O(n log n)`。
