# 单调栈与单调队列学习笔记（整合版）

## 一、概念与核心思想

- **单调栈**：栈内元素保持单调递增或递减。用于在线性时间内找到**每个元素左侧/右侧第一个比它大/小的元素**。
- **单调队列**：双端队列，队内元素保持单调性。用于**滑动窗口最值**或**优化特定形式的DP**。

> 共同点：利用单调性**及时淘汰不可能成为答案的候选者**，将暴力 O(n²) 优化到 O(n)。

---

## 二、什么时候用？—— 决策思维

### 2.1 使用单调栈的信号

| 题目特征 / 关键词                                           | 典型例子                                 |
| ---------------------------------------------------------- | ---------------------------------------- |
| “每个元素右边第一个比它大的元素”                           | 每日温度、下一个更大元素                  |
| “每个元素左边第一个比它小的元素”                           | 直方图最大矩形（需左右边界）              |
| “去除重复字母后字典序最小”                                 | 单调栈 + 计数                            |
| “接雨水”                                                   | 单调栈（或双指针）                       |
| “柱状图中最大矩形”                                         | 单调递增栈（找左右第一个更小的高度）      |

**思考路径**：  
遇到数组/序列 → 问题是否涉及“每个元素”与“左边/右边第一个更大/更小”的关系？ → 是 → 单调栈。

### 2.2 使用单调队列的信号

| 题目特征 / 关键词                                           | 典型例子                                 |
| ---------------------------------------------------------- | ---------------------------------------- |
| “滑动窗口最大值/最小值”                                    | 固定长度窗口内求最值                      |
| “和至少为 K 的最短子数组”                                  | 前缀和 + 单调递增队列                     |
| “绝对差不超过限制的最长连续子数组”                         | 两个单调队列（同时维护最大和最小）        |
| DP 转移形如 `dp[i] = min/max(dp[j] + cost(j,i))` 且 cost 有单调性 | 优化 DP                                  |

**思考路径**：  
有数组 + 固定长度窗口滑动 → 需要快速获取窗口内最值 → 暴力 O(nk) 太大 → 单调队列 O(n)。  
或：子数组和最值问题 → 前缀和 + 单调队列。

---

## 三、算法详解与 C 代码实现

### 3.1 单调栈

#### 原理（以“找右边第一个更大的元素”为例）
- 维护一个**单调递减栈**（栈底到栈顶递减）。
- 遍历数组，当前元素 `nums[i]`：
  - 若 `nums[i] > nums[栈顶]`，说明 `nums[i]` 就是栈顶元素的“右边第一个更大值”，弹出栈顶并记录。
  - 重复直到栈空或 `nums[i] ≤ nums[栈顶]`。
  - 将 `i` 入栈。
- 遍历结束后栈中剩余元素右边无更大值，记作 -1。

#### 代码：下一个更大元素

```c
#include <stdio.h>
#include <stdlib.h>

void nextGreaterElement(int *nums, int n, int *result) {
    int *stack = (int*)malloc(n * sizeof(int));
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top != -1 && nums[i] > nums[stack[top]]) {
            result[stack[top--]] = nums[i];
        }
        stack[++top] = i;
    }
    while (top != -1) result[stack[top--]] = -1;
    free(stack);
}

int main() {
    int nums[] = {2,1,5,6,2,3};
    int n = sizeof(nums)/sizeof(nums[0]);
    int *res = malloc(n * sizeof(int));
    nextGreaterElement(nums, n, res);
    for (int i = 0; i < n; i++) printf("%d -> %d\n", nums[i], res[i]);
    free(res);
    return 0;
}
```

#### 经典变体：直方图最大矩形

```c
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

### 3.2 单调队列

#### 原理（以“滑动窗口最大值”为例）
- 维护一个**单调递减的双端队列**（队头是当前窗口最大值下标）。
- 遍历数组，对于每个下标 `i`：
  1. **移除过期下标**：若队头下标 ≤ `i - k`，则弹出队头。
  2. **维护单调性**：从队尾弹出所有 `nums[下标] < nums[i]` 的下标（因为更大的新元素会挡住它们）。
  3. **加入当前下标**：将 `i` 从队尾入队。
  4. **记录答案**：当 `i ≥ k-1` 时，队头下标对应的值即为当前窗口最大值。

#### 代码：滑动窗口最大值

```c
#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int *nums, int n, int k, int *returnSize) {
    *returnSize = n - k + 1;
    int *res = malloc((*returnSize) * sizeof(int));
    int *dq = malloc(n * sizeof(int));  // 存储下标，模拟双端队列
    int front = 0, rear = -1, idx = 0;
    for (int i = 0; i < n; i++) {
        // 移除超出窗口的左边界
        while (front <= rear && dq[front] <= i - k) front++;
        // 维护递减队列：弹出所有小于 nums[i] 的队尾
        while (front <= rear && nums[dq[rear]] < nums[i]) rear--;
        dq[++rear] = i;
        // 窗口形成后记录最大值
        if (i >= k - 1) res[idx++] = nums[dq[front]];
    }
    free(dq);
    return res;
}

int main() {
    int nums[] = {1,3,-1,-3,5,3,6,7};
    int n = sizeof(nums)/sizeof(nums[0]), k = 3, returnSize;
    int *res = maxSlidingWindow(nums, n, k, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%d ", res[i]);
    free(res);
    return 0;
}
```

#### 经典变体：和至少为 K 的最短子数组（前缀和 + 单调队列）

```c
#include <limits.h>

int shortestSubarray(int *nums, int n, int K) {
    long long *prefix = malloc((n+1) * sizeof(long long));
    prefix[0] = 0;
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + nums[i];
    
    int *dq = malloc((n+1) * sizeof(int));
    int front = 0, rear = -1, minLen = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        // 当当前前缀和 - 队首前缀和 >= K，更新答案并弹出队首
        while (front <= rear && prefix[i] - prefix[dq[front]] >= K) {
            int len = i - dq[front];
            if (len < minLen) minLen = len;
            front++;
        }
        // 维护递增队列：保持队内 prefix 递增，弹出队尾中更大的 prefix
        while (front <= rear && prefix[i] <= prefix[dq[rear]]) rear--;
        dq[++rear] = i;
    }
    free(prefix); free(dq);
    return (minLen == INT_MAX) ? -1 : minLen;
}
```

---

## 四、快速决策表（查找用）

| 问题描述                                           | 使用工具     | 单调方向                     |
| -------------------------------------------------- | ------------ | ---------------------------- |
| 每个元素右边第一个更大的元素                       | 单调栈       | 递减栈（栈底→栈顶递减）      |
| 每个元素左边第一个更小的元素                       | 单调栈       | 递增栈                       |
| 直方图最大矩形（找左右第一个更小的高度）           | 单调栈       | 递增栈                       |
| 接雨水                                            | 单调栈       | 递减栈（或双指针）           |
| 滑动窗口最大值                                    | 单调队列     | 递减队列（队头最大）         |
| 滑动窗口最小值                                    | 单调队列     | 递增队列（队头最小）         |
| 和至少为 K 的最短子数组（前缀和）                  | 单调队列     | 递增队列（维护前缀和候选）   |
| 绝对差不超过 limit 的最长连续子数组                | 两个单调队列 | 一个递增，一个递减           |
| 移除 K 位数字使剩下数字最小                       | 单调栈       | 递增栈（遇到更小则弹出栈顶） |

---

## 五、总结口诀

- **单调栈**：左右找大找小，**一维扫描消逆序**，栈顶弹掉逆序对。
- **单调队列**：窗口滑来滑去，**队尾维护单调性，队头过期就扔掉**。

记住：  
> “下一个更大/更小” → 单调栈  
> “固定长度窗口的最值” → 单调队列  
> 如果同时涉及窗口和极值，优先单调队列；涉及元素左右关系，优先单调栈。