# LeetCode 84. 柱状图中最大的矩形 学习笔记

## 题目描述
给定 n 个非负整数，表示柱状图中各个柱子的高度。每个柱子宽度为 1。求在该柱状图中能勾勒出的矩形的最大面积。

**示例：**
```
输入: heights = [2,1,5,6,2,3]
输出: 10
解释：高度为 5 和 6 的矩形，最大面积为 10。
```

## 最优解法：单调栈（O(n) 时间，O(n) 空间）

### 核心思路
- 使用**单调递增栈**存储柱子的下标，保证栈内对应的高度递增。
- 遍历每个柱子，当当前高度 `heights[i]` **小于**栈顶高度时，**弹出栈顶**，并以该弹出高度作为矩形高，计算宽度：
  - 左边界 = 新栈顶下标（弹出后的栈顶，即左边第一个比它低的柱子）
  - 右边界 = i（当前柱子，即右边第一个比它低的柱子）
  - 宽度 = 右边界 - 左边界 - 1
  - 面积 = 弹出高度 × 宽度，更新最大面积。
- 遍历结束后，弹出栈中剩余柱子，此时右边界 = `heightsSize`。

### C 语言实现（自定义 MAX 宏）
```c
#define MAX(a,b) (((a)>(b))?(a):(b))

int largestRectangleArea(int* heights, int heightsSize) {
    int stack[heightsSize + 1];   // 存储下标
    int top = -1;
    stack[++top] = -1;            // 哨兵，便于计算宽度
    int maxArea = 0;
    for (int i = 0; i < heightsSize; i++) {
        while (top > 0 && heights[i] < heights[stack[top]]) {
            int h = heights[stack[top--]];
            int width = i - stack[top] - 1;
            maxArea = MAX(maxArea, h * width);
        }
        stack[++top] = i;
    }
    // 处理栈中剩余柱子（右边无更低的柱子）
    while (top > 0) {
        int h = heights[stack[top--]];
        int width = heightsSize - stack[top] - 1;
        maxArea = MAX(maxArea, h * width);
    }
    return maxArea;
}

或
#include <stdlib.h>
int largestRectangleArea(int *heights, int n) {
    int *stack = malloc((n+1)*sizeof(int));
    int top = -1, maxArea = 0;
    for (int i = 0; i <= n; i++) {
        int curH = (i == n) ? 0 : heights[i];
        while (top != -1 && curH < heights[stack[top]]) {
            int h = heights[stack[top--]];
            int left = (top == -1) ? 0 : stack[top] + 1;
            int area = h * (i - left);
            if (area > maxArea) maxArea = area;
        }
        stack[++top] = i;
    }
    free(stack);
    return maxArea;
}
```

### 复杂度
- 时间复杂度：O(n)，每个元素最多入栈出栈一次。
- 空间复杂度：O(n)，栈空间。

## 其他解法（了解即可）
1. **暴力枚举**：枚举每个柱子作为高，向左右扩展至更低柱子，O(n²)。
2. **分治法**：找区间最矮柱子，递归左右，平均 O(n log n)，最坏 O(n²)。

## 关键点
- 单调栈保证每次弹出的柱子，其左右边界都是**第一个比它矮的柱子**，因此能正确计算最大宽度。
- 哨兵 `-1` 简化边界处理，避免栈空判断。