# LeetCode 279. 完全平方数 - 学习笔记

## 题目描述
给定正整数 n，找到若干个完全平方数（如 1, 4, 9, 16, ...）使其和等于 n，且使用数量最少。返回最少数量。

## 核心思路
将问题转化为**完全背包**：物品为所有 ≤ n 的完全平方数，每个物品无限使用，求装满容量 n 的最少物品数。

## 常见解法

### 1. 动态规划（O(n√n)）
状态定义：`dp[i]` 表示组成 i 所需的最少完全平方数个数。  
转移方程：  
`dp[i] = min(dp[i - j*j] + 1)`，对所有满足 `j*j ≤ i` 的 j 成立。  
初始条件：`dp[0] = 0`，其余初始化为无穷大。

**C语言实现**
```c
#include <limits.h>
#include <stdlib.h>

int numSquares(int n) {
    int *dp = (int*)malloc(sizeof(int) * (n + 1));
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = INT_MAX;
        for (int j = 1; j * j <= i; ++j) {
            int tmp = dp[i - j * j] + 1;
            if (tmp < dp[i]) dp[i] = tmp;
        }
    }
    int res = dp[n];
    free(dp);
    return res;
}
```

**复杂度**  
- 时间：O(n√n)  
- 空间：O(n)

### 2. 数学方法（四平方定理，O(√n)）
- **四平方定理**：任何自然数均可表示为至多 4 个完全平方数之和。
- **判断规则**：
  1. 若 n 本身是完全平方数 → 返回 1
  2. 若存在 j 使 `n - j*j` 是完全平方数 → 返回 2
  3. 若 n 形如 `4^k * (8m + 7)` → 返回 4
  4. 否则返回 3

**C语言实现**
```c
#include <math.h>

int isSquare(int x) {
    int r = sqrt(x);
    return r * r == x;
}

int numSquares(int n) {
    if (isSquare(n)) return 1;
    for (int i = 1; i * i <= n; ++i)
        if (isSquare(n - i * i)) return 2;
    while (n % 4 == 0) n /= 4;
    if (n % 8 == 7) return 4;
    return 3;
}
```

**复杂度**  
- 时间：O(√n)  
- 空间：O(1)

## 总结
- DP 方法通用、易理解，适合面试。
- 数学方法效率极高，但需要数论知识。
- 两种方法均可通过本题（n ≤ 10⁴）。