# LeetCode 54. 螺旋矩阵 —�?C 语言学习笔记

## 1. 题目描述

给你一�?`m �?n 列` 的矩�?`matrix`，请按照 **顺时针螺旋顺�?* ，返回矩阵中的所有元素�?

### 示例 1

输入�?

```text
matrix = [[1,2,3],
          [4,5,6],
          [7,8,9]]
````

输出�?

```text
[1,2,3,6,9,8,7,4,5]
```

### 示例 2

输入�?

```text
matrix = [[1,2,3,4],
          [5,6,7,8],
          [9,10,11,12]]
```

输出�?

```text
[1,2,3,4,8,12,11,10,9,5,6,7]
```

---

## 2. 题目本质

这道题本质上是一�?**矩阵模拟遍历** 问题�?

要求不是排序，不是搜索，而是�?

* 按照特定规则访问矩阵元素
* 每个元素访问且仅访问一�?
* 最终把访问顺序保存到结果数组中

这类题目的核心通常是：

1. **如何控制遍历边界**
2. **如何避免重复访问**
3. **如何处理单行、单列、空矩阵等特殊情�?*

---

## 3. 解题方法总览

这题至少有两种常见做法：

### 方法一：边界收缩法

用四个变量维护当前未遍历区域的边界：

* `top`
* `bottom`
* `left`
* `right`

每次按以下顺序遍历一圈：

1. 从左到右
2. 从上到下
3. 从右到左
4. 从下到上

然后缩小边界，继续下一圈�?

### 方法二：方向模拟�?+ visited 标记

按照固定方向行走�?

* �?
* �?
* �?
* �?

每次判断下一步是否越界或已经访问过，如果不能走就换方向，并用 `visited` 数组记录访问状态�?

---

# 4. 方法一：边界收缩法

## 4.1 思路分析

假设当前还没有遍历的区域是一个矩形：

* 上边界：`top`
* 下边界：`bottom`
* 左边界：`left`
* 右边界：`right`

每一轮做四件事：

### 第一步：遍历上边�?

�?`(top, left)` �?`(top, right)`

### 第二步：遍历右边�?

�?`(top + 1, right)` �?`(bottom, right)`

### 第三步：遍历下边�?

�?`(bottom, right - 1)` �?`(bottom, left)`
注意：只有在 `top <= bottom` 时才可以遍历

### 第四步：遍历左边�?

�?`(bottom - 1, left)` �?`(top, left)`
注意：只有在 `left <= right` 时才可以遍历

每走完一圈，边界收缩�?

* `top++`
* `bottom--`
* `left++`
* `right--`

直到没有元素可遍历�?

---

## 4.2 动态过程示�?

以矩阵：

```text
1 2 3
4 5 6
7 8 9
```

为例�?

### 第一�?

* 上边：`1 2 3`
* 右边：`6 9`
* 下边：`8 7`
* 左边：`4`

剩余�?

```text
5
```

### 第二�?

* 上边：`5`

最终结果：

```text
1 2 3 6 9 8 7 4 5
```

---

## 4.3 C 语言代码实现

```c
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    // 空矩阵处�?
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int total = rows * cols;

    int* ans = (int*)malloc(sizeof(int) * total);
    *returnSize = total;

    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int k = 0;

    while (top <= bottom && left <= right) {
        // 1. 从左到右遍历上边�?
        for (int j = left; j <= right; j++) {
            ans[k++] = matrix[top][j];
        }
        top++;

        // 2. 从上到下遍历右边�?
        for (int i = top; i <= bottom; i++) {
            ans[k++] = matrix[i][right];
        }
        right--;

        // 3. 从右到左遍历下边�?
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                ans[k++] = matrix[bottom][j];
            }
            bottom--;
        }

        // 4. 从下到上遍历左边�?
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                ans[k++] = matrix[i][left];
            }
            left++;
        }
    }

    return ans;
}
```

---

## 4.4 复杂度分�?

### 时间复杂�?

```text
O(m * n)
```

因为每个元素只会被访问一次�?

### 空间复杂�?

```text
O(1)
```

这里只使用了若干辅助变量�?
注意�?*不计返回结果数组的空�?*�?

---

## 4.5 方法一的优�?

* 写法经典，面试最常见
* 不需要额外的 `visited` 数组
* 空间复杂度更�?
* 更适合这道�?

---

# 5. 方法二：方向模拟�?+ visited 标记

## 5.1 思路分析

这是一种更直观的“走路”思路�?

设定 4 个方向：

* 向右：`(0, 1)`
* 向下：`(1, 0)`
* 向左：`(0, -1)`
* 向上：`(-1, 0)`

初始位置在左上角 `(0, 0)`，初始方向为“右”�?

每次�?

1. 把当前位置加入答�?
2. 标记当前位置已访�?
3. 试图向当前方向走一�?
4. 如果下一步越界，或者已经访问过，则转向
5. 继续走，直到访问完全部元�?

---

## 5.2 C 语言代码实现

```c
#include <stdlib.h>
#include <stdbool.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int total = rows * cols;

    int* ans = (int*)malloc(sizeof(int) * total);
    *returnSize = total;

    bool* visited = (bool*)calloc(total, sizeof(bool));

    // 方向：右、下、左、上
    int dr[4] = {0, 1, 0, -1};
    int dc[4] = {1, 0, -1, 0};

    int row = 0, col = 0, dir = 0;

    for (int k = 0; k < total; k++) {
        ans[k] = matrix[row][col];
        visited[row * cols + col] = true;

        int nextRow = row + dr[dir];
        int nextCol = col + dc[dir];

        // 如果下一步越界，或者已经访问过，就转向
        if (nextRow < 0 || nextRow >= rows ||
            nextCol < 0 || nextCol >= cols ||
            visited[nextRow * cols + nextCol]) {
            dir = (dir + 1) % 4;
            nextRow = row + dr[dir];
            nextCol = col + dc[dir];
        }

        row = nextRow;
        col = nextCol;
    }

    free(visited);
    return ans;
}
```

---

## 5.3 复杂度分�?

### 时间复杂�?

```text
O(m * n)
```

每个元素依旧只访问一次�?

### 空间复杂�?

```text
O(m * n)
```

因为使用�?`visited` 数组�?

---

## 5.4 方法二的优点与不�?

### 优点

* 思路直观
* 很像机器人沿方向行走
* 适合理解“模拟”类题目

### 不足

* 需要额外空间记录访问状�?
* 实际上没有边界法简�?
* 不是这题最优写�?

---

# 6. 两种方法对比

| 方法    | 核心思想       | 时间复杂�?| 空间复杂�?| 推荐程度  |
| ----- | ---------- | ----- | ----- | ----- |
| 边界收缩�?| 一圈一圈缩小矩形边�?| O(mn) | O(1)  | ⭐⭐⭐⭐�?|
| 方向模拟�?| 按右下左上行走并转向 | O(mn) | O(mn) | ⭐⭐�?  |

### 结论

这题优先推荐�?

```text
边界收缩�?
```

因为它空间复杂度更低，而且是最经典的标准解法�?

---

# 7. 易错点总结

## 易错�?1：忘记判�?

如果矩阵为空�?

```c
matrixSize == 0
```

此时不能直接访问 `matrixColSize[0]`�?

---

## 易错�?2：下边界和左边界重复遍历

在边界收缩法中：

```c
if (top <= bottom)
if (left <= right)
```

这两个判断非常关键�?

例如只有一行时，如果不判断，就会把这一行遍历两次�?

---

## 易错�?3：结果数组大小分配错�?

结果数组长度必须是：

```c
rows * cols
```

不能少，也不能忘记赋值给 `returnSize`�?

---

## 易错�?4：方向模拟法�?visited 下标写错

如果用一维数组表示二维访问状态：

```c
visited[row * cols + col]
```

这里一定是 `row * cols + col`，不是别的�?

---

# 8. 推荐背诵版本

这份代码最适合面试和刷题时记忆�?

```c
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize, cols = matrixColSize[0];
    int* ans = (int*)malloc(sizeof(int) * rows * cols);
    *returnSize = rows * cols;

    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int k = 0;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) ans[k++] = matrix[top][j];
        top++;

        for (int i = top; i <= bottom; i++) ans[k++] = matrix[i][right];
        right--;

        if (top <= bottom) {
            for (int j = right; j >= left; j--) ans[k++] = matrix[bottom][j];
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) ans[k++] = matrix[i][left];
            left++;
        }
    }

    return ans;
}
```

---

# 9. 面试回答模板

面试时可以这样说�?

> 这题是一个矩阵模拟遍历问题�?
> 我会优先使用边界收缩法，定义上、下、左、右四个边界，每轮按照上行、右列、下行、左列的顺序遍历一圈，然后逐步缩小边界�?
> 这样每个元素只访问一次，时间复杂度是 O(mn)，额外空间复杂度�?O(1)�?
> 另外也可以用方向数组�?visited 标记来模拟行走，但空间复杂度更高�?

---

# 10. 本题知识点总结

这题需要掌握的核心内容有：

* 矩阵模拟遍历
* 边界控制
* 顺时针方向规�?
* 防止重复访问
* 特殊情况处理（单行、单列、空矩阵�?

---

# 11. 同类题目举一反三

学完这题后，可以继续练这些题�?

1. **螺旋矩阵 II**

   * 不是读取矩阵，而是生成螺旋矩阵

2. **顺时针打印矩阵（剑指 Offer�?*

   * 和本题几乎同类型

3. **旋转图像**

   * 也是矩阵处理题，但重点是原地旋转

4. **二维矩阵遍历类题�?*

   * 比如对角线遍历、Z 字形遍历�?

---

# 12. 最终总结

## 这题最优思路

```text
边界收缩�?
```

## 原因

* 思路清晰
* 代码简�?
* 无需额外 visited 数组
* 面试中最常用

## 结论

只要记住四个边界�?

```text
top, bottom, left, right
```

并按顺序完成�?

```text
左到�?-> 上到�?-> 右到�?-> 下到�?
```

再不断缩小边界，就能解决这道题�?

---

```


