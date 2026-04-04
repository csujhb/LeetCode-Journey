---

# LeetCode 54. 螺旋矩阵 —— C 语言学习笔记

##  题目描述

给你一个 `m 行 n 列` 的矩阵 `matrix`，请按照 **顺时针螺旋顺序**，返回矩阵中的所有元素。

### 示例 1

**输入：**

```text
matrix = [[1,2,3],
          [4,5,6],
          [7,8,9]]
```
**输出：** `[1,2,3,6,9,8,7,4,5]`

---

## 题目本质

这道题本质上是一个 **矩阵模拟遍历** 问题。要求按照特定规则访问矩阵元素，每个元素访问且仅访问一次，并将访问顺序保存到结果数组中。

核心挑战在于：
1. 如何精确控制遍历边界。
2. 如何避免重复访问。
3. 如何处理单行、单列、空矩阵等特殊情况。

---

## 解题方法总览

### 方法一：边界收缩法（推荐）
用四个变量维护当前未遍历区域的边界：`top`、`bottom`、`left`、`right`。每轮按“左→右、上→下、右→左、下→上”的顺序遍历并收缩边界。

### 方法二：方向模拟法 + visited 标记

设定固定方向（右、下、左、上）行走，遇到边界或已访问过的位置则转向，需配合 `visited` 数组记录状态。

---

# 方法一：边界收缩法

## 思路分析

每一轮循环处理矩形的四个边：
1. **上边界**：从 `(top, left)` 到 `(top, right)`。
2. **右边界**：从 `(top + 1, right)` 到 `(bottom, right)`。
3. **下边界**：从 `(bottom, right - 1)` 到 `(bottom, left)`（需满足 `top <= bottom`）。
4. **左边界**：从 `(bottom - 1, left)` 到 `(top + 1, left)`（需满足 `left <= right`）。

每走完一圈，执行 `top++`, `bottom--`, `left++`, `right--`，直到边界交错。

---

## C 语言代码实现

```c
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    // 1. 空矩阵判空处理
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
        // 1. 从左到右遍历上边界
        for (int j = left; j <= right; j++) {
            ans[k++] = matrix[top][j];
        }
        top++;

        // 2. 从上到下遍历右边界
        for (int i = top; i <= bottom; i++) {
            ans[k++] = matrix[i][right];
        }
        right--;

        // 3. 从右到左遍历下边界 (注意 top <= bottom 判断)
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                ans[k++] = matrix[bottom][j];
            }
            bottom--;
        }

        // 4. 从下到上遍历左边界 (注意 left <= right 判断)
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

## 复杂度分析

* **时间复杂度**：$O(m \times n)$。每个元素仅访问一次。
* **空间复杂度**：$O(1)$。除返回数组外，仅使用常数级辅助变量。

---

#  方法二：方向模拟法 + visited 标记

## 思路分析
设定 4 个方向向量：右 `(0, 1)`、下 `(1, 0)`、左 `(0, -1)`、上 `(-1, 0)`。
1. 标记当前位置为已访问。
2. 尝试沿当前方向前进。
3. 若下一步越界或已访问过，则按“右→下→左→上”顺序切换方向。


---

## C 语言代码实现

```c
#include <stdlib.h>
#include <stdbool.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize, cols = matrixColSize[0];
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

        // 转向判定
        if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols || visited[nextRow * cols + nextCol]) {
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

## 两种方法对比

| 方法 | 核心思想 | 时间复杂度 | 空间复杂度 | 推荐程度 |
| :--- | :--- | :--- | :--- | :--- |
| **边界收缩法** | 四个边界变量逐圈缩小 | $O(mn)$ | **$O(1)$** | ⭐⭐⭐⭐⭐ |
| **方向模拟法** | 方向数组 + 状态标记 | $O(mn)$ | $O(mn)$ | ⭐⭐⭐ |

---

##  易错点总结

1. **忘记判空**：若矩阵 `matrixSize == 0`，直接访问 `matrixColSize[0]` 会崩溃。
2. **下/左边界重复遍历**：在处理单行或单列时，若没有 `if (top <= bottom)` 这类二次判断，会导致元素被重复放入结果。
3. **visited 下标计算**：二维坐标 `(row, col)` 转一维应为 `row * cols + col`。

---

##  一句话总结
> **记住四个边界变量 `top, bottom, left, right`，按照顺时针顺序依次遍历并收缩，是解决本题的最优解。**