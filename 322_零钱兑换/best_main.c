//动态规划的思想
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