# LeetCode 45. 跳跃游戏 II 学习笔记

## 题目描述
给定一个非负整数数组 `nums`，初始位置为下标 0。每个元素表示在该位置能跳跃的最大长度。求到达最后一个下标的最少跳跃次数。**题目保证可以到达终点。**

## 解法一：贪心（最优解）
### 思路
- 维护**当前步数能到达的最远位置** `curEnd` 和**下一步能到达的最远位置** `farthest`。
- 遍历数组（不遍历最后一个元素），每步更新 `farthest = max(farthest, i + nums[i])`。
- 当 `i == curEnd` 时，必须再跳一次：步数加1，`curEnd = farthest`。若 `curEnd >= n-1` 则提前结束。

### C 语言实现
```c
int jump(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;
    int steps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        farthest = (i + nums[i] > farthest) ? i + nums[i] : farthest;
        if (i == curEnd) {
            steps++;
            curEnd = farthest;
            if (curEnd >= numsSize - 1) break;
        }
    }
    return steps;
}
```

### 复杂度
- 时间：O(n)，空间：O(1)

## 解法二：动态规划
### 思路
- 定义 `dp[i]` 表示到达下标 `i` 的最少跳跃次数。
- 初始化 `dp[0] = 0`，其余为一个大数（如 `n`）。
- 对于每个 `i`，从 `i` 出发能到达的范围是 `[i+1, i+nums[i]]`，更新：`dp[j] = min(dp[j], dp[i] + 1)`。
- 最终答案为 `dp[n-1]`。

### C 语言实现
```c
int jump(int* nums, int numsSize) {
    int dp[numsSize];
    for (int i = 0; i < numsSize; i++) dp[i] = numsSize; // 初始化为大数
    dp[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j <= i + nums[i] && j < numsSize; j++) {
            if (dp[i] + 1 < dp[j]) dp[j] = dp[i] + 1;
        }
    }
    return dp[numsSize - 1];
}
```

### 复杂度
- 时间：O(n²)，空间：O(n)（不适合大数据量）

## 解法三：BFS（按层遍历）

### 思路

- 将数组看作图，从起点开始，每一层扩展当前层所有点能一步到达的位置。
- 使用队列，但可优化为只维护当前层的左右边界（与贪心本质相同）。
- 到达终点时返回层数。

### C 语言实现（队列模拟）
```c
int jump(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;
    int *queue = (int*)malloc(numsSize * sizeof(int));
    int front = 0, rear = 0;
    int *dist = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) dist[i] = -1;
    dist[0] = 0;
    queue[rear++] = 0;
    while (front < rear) {
        int cur = queue[front++];
        int step = dist[cur] + 1;
        for (int next = cur + 1; next <= cur + nums[cur] && next < numsSize; next++) {
            if (dist[next] == -1) {
                if (next == numsSize - 1) {
                    free(queue); free(dist);
                    return step;
                }
                dist[next] = step;
                queue[rear++] = next;
            }
        }
    }
    free(queue); free(dist);
    return -1;
}
```

### 复杂度
- 时间：O(n)，空间：O(n)

## 关键点
- 贪心法最优：时间 O(n)，空间 O(1)
- 动态规划简单直观，但效率低
- BFS 易于理解层数，但需额外空间
- 题目保证可达，无需处理不可达情况