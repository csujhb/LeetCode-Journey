# LeetCode 322. 零钱兑换 - 学习笔记

## 题目描述
给定不同面额的硬币 `coins` 和一个总金额 `amount`，计算可以凑成总金额所需的最少硬币个数。如果没有任何一种硬币组合能组成总金额，返回 `-1`。  
假设每种硬币数量无限。

## 核心思路
完全背包问题：物品为硬币面额，背包容量为 `amount`，求装满背包所需的最少物品数。

## 常见解法

### 1. 动态规划（O(amount × len(coins))）
**状态定义**：`dp[i]` 表示凑成金额 i 所需的最少硬币数。  
**转移方程**：`dp[i] = min(dp[i - coin] + 1)`，对所有 `coin ≤ i`。  
**初始化**：`dp[0] = 0`，其余为 `amount + 1`（表示不可达）。  
**返回**：若 `dp[amount] > amount` 则 `-1`，否则 `dp[amount]`。

**C语言实现**
```c
#include <stdlib.h>

int coinChange(int* coins, int coinsSize, int amount) {
    int *dp = (int*)malloc(sizeof(int) * (amount + 1));
    for (int i = 0; i <= amount; ++i) dp[i] = amount + 1;
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (int j = 0; j < coinsSize; ++j) {
            if (coins[j] <= i) {
                int tmp = dp[i - coins[j]] + 1;
                if (tmp < dp[i]) dp[i] = tmp;
            }
        }
    }
    int res = dp[amount] > amount ? -1 : dp[amount];
    free(dp);
    return res;
}
```

**复杂度**  
- 时间：O(amount × coinsSize)  
- 空间：O(amount)

### 2. 广度优先搜索（BFS）
**思路**：将金额看作节点，每次减去一枚硬币得到新节点，首次到达 0 时的层数即为最少硬币数。  
**优点**：可提前终止，无需计算所有金额。  
**注意**：需用 `visited` 数组避免重复入队。

**C语言实现**
```c
#include <stdlib.h>
#include <string.h>

int coinChange(int* coins, int coinsSize, int amount) {
    if (amount == 0) return 0;
    int *queue = (int*)malloc(sizeof(int) * (amount + 1));
    int *visited = (int*)calloc(amount + 1, sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = amount;
    visited[amount] = 1;
    int steps = 0;
    while (front < rear) {
        int size = rear - front;
        steps++;
        for (int i = 0; i < size; ++i) {
            int cur = queue[front++];
            for (int j = 0; j < coinsSize; ++j) {
                int next = cur - coins[j];
                if (next == 0) {
                    free(queue); free(visited);
                    return steps;
                }
                if (next > 0 && !visited[next]) {
                    visited[next] = 1;
                    queue[rear++] = next;
                }
            }
        }
    }
    free(queue); free(visited);
    return -1;
}
```

**复杂度**  
- 时间：最坏 O(amount × coinsSize)  
- 空间：O(amount)

## 总结
- DP 方法直观、通用，适合所有完全背包问题。
- BFS 方法在目标金额较小或硬币面额较大时更快，且能早期退出。
- 两种方法均需处理无解情况（返回 -1）。