// 不对,left可能越界
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;
    int *res = (int *)malloc(sizeof(int) * (*returnSize));
    if (numsSize == 0)
    {
        res[0] = -1;
        res[1] = -1;
    }
    int left = 0;
    int right = numsSize - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    if (nums[left] == target)
    {
        res[0] = left;
        while (left < numsSize && nums[left] == target)
        {
            left++;
        }
        res[1] = left - 1;
    }
    return res;
}