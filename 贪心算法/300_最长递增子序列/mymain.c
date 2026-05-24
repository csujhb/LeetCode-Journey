// 动态规划
#include <stdlib.h>
int lengthOfLIS(int *nums, int numsSize)
{
    int *res = (int *)malloc(numsSize * sizeof(int));
    int max = 1;
    for (int i = 0; i < numsSize; i++)
    {
        res[i] = 1;
    }
    for (int i = 1; i < numsSize; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[j] < nums[i] && res[j] + 1 > res[i])
            {
                res[i] = res[j] + 1;
            }
        }
        if (res[i] > max)
            max = res[i];
    }
    free(res);
    return max;
}