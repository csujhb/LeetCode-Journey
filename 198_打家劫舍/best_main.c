/*
理解有误，误以为不能连续偷相邻的房屋
*/
#include <stdio.h>

int rob(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];
    
    int prev2 = 0;      // dp[i-2]
    int prev1 = nums[0]; // dp[i-1]
    
    for (int i = 2; i <= numsSize; i++) {
        int current = (prev1 > prev2 + nums[i-1]) ? prev1 : (prev2 + nums[i-1]);
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}