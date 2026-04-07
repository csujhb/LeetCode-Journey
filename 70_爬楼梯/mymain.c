#include <stdlib.h>
int climbStairs(int n) {
    if(n<=2) return n; 
    int *dp=(int*)malloc((n+1)*sizeof(int));
    dp[0]=1;
    dp[1]=1;
    for(int i=2;i<=n;i++){
        dp[i]=dp[i-1]+dp[i-2];
    }
    int res=dp[n];
    free(dp);
    return res;
}