// 2026.8.12
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *productExceptSelf(int *nums, int numsSize, int *returnSize)
{
    int *res = (int *)malloc(numsSize * sizeof(int));
    res[0] = 1;
    for (int i = 1; i < numsSize; i++)
    {
        res[i] = res[i - 1] * nums[i - 1];
    }
    int k = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; i--)
    {
        res[i] *= k;
        k *= nums[i];
    }
    *returnSize = numsSize;
    return res;
}