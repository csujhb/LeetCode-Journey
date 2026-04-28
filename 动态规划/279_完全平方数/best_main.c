/*
只考虑完全平方数作为可能的拆分项，将问题转化为“完全背包”或直接使用如下状态转移：
dp[i] = min(dp[i - j²] + 1)  对所有满足 j² ≤ i 的 j 成立
这样内层循环只需遍历 √i 次，整体时间复杂度 O(n·√n)，在 n ≤ 10⁴ 时非常快（约 10⁶ 次运算）。
*/

#include <limits.h>
#include <stdlib.h>

int numSquares(int n) {
    int *dp = (int*)malloc(sizeof(int) * (n + 1));
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        //最坏情况
        dp[i] = i;
        // 尝试减去一个完全平方数
        for (int j = 1; j * j <= i; ++j) {
            int tmp = dp[i - j * j] + 1;
            if (tmp < dp[i]) dp[i] = tmp;
        }
    }
    int res = dp[n];
    free(dp);
    return res;
}