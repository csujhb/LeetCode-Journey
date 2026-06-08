// 2026.6.8
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;
    int *res = (int *)malloc(2 * sizeof(int));
    res[0] = -1;
    res[1] = -1;
    if (numsSize == 0)
        return res;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target)
            right = mid - 1;
        else if (nums[mid] < target)
            left = mid + 1;
        else
        {
            while (mid >= 0 && nums[mid] == target)
            {
                mid--;
            }
            res[0] = ++mid;
            while (mid < numsSize && nums[mid] == target)
            {
                mid++;
            }
            res[1] = --mid;
            return res;
        }
    }
    return res;
}