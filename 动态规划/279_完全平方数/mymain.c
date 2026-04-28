/*
时间复杂度为O(N*N)，虽然也能解出来，但是不太适合
*/
#include <limits.h>
#include <stdlib.h>
int numSquares(int n) {
    if(n==1) return 1;
    int *dp=(int*)malloc(sizeof(int)*(n+1));
    dp[1]=1;
    dp[0]=0;
    for(int i=2;i<=n;i++)  dp[i]=INT_MAX;
    for(int i=2;i*i<=n;i++)  dp[i*i]=1;
    for(int i=2;i<=n;i++){
        if(dp[i]!=1){
            for(int j=1;j<=i/2;j++){
            dp[i]=((dp[i-j]+dp[j])>dp[i])?dp[i]:(dp[i-j]+dp[j]);
            }
        }
    }
    int res=dp[n];
    free(dp);
    return res;
}