//动态规划的思想
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
int coinChange(int* coins, int coinsSize, int amount) {
    if(amount==0) return 0;
    int *dp=(int*)malloc(sizeof(int)*(amount+1));
    int count=0;
    dp[0]=0;
    for(int i=1;i<=amount;i++){
        dp[i]=amount+1;
    }
    for(int i=1;i<=amount;i++){
        for(int j=0;j<coinsSize;j++){
            if(i>=coins[j]){
                dp[i]=MIN(dp[i],dp[i-coins[j]]+1);
            }
        }
    }
    return (dp[amount]>amount)?-1:dp[amount];
}