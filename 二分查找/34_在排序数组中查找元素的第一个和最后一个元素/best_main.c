#include <stdlib.h>

int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    int *result = (int *)malloc(2 * sizeof(int));
    *returnSize = 2;
    result[0] = -1;
    result[1] = -1;

    if (numsSize == 0)
        return result;

    // --- 1. 寻找左边界 ---
    int left = 0;
    int right = numsSize - 1;
    while (left < right)
    {
        // 向下取整
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid + 1; // 彻底排除
        }
        else
        {
            right = mid; // mid 满足条件或大于 target，答案在 mid 或其左侧
        }
    }

    // 退出循环时 left == right。检查这个位置是不是我们要找的 target
    if (nums[left] != target)
    {
        return result; // 如果连左边界都没找到，说明数组里根本没这个数，直接返回 [-1, -1]
    }
    result[0] = left;

    // --- 2. 寻找右边界 ---
    // 左边界不用重置为 0，因为右边界肯定在左边界的右边或重合
    right = numsSize - 1;
    while (left < right)
    {
        // 向上取整！(加 1)，这是为了防止 left = mid 造成死循环
        int mid = left + (right - left + 1) / 2;
        if (nums[mid] > target)
        {
            right = mid - 1; // 彻底排除
        }
        else
        {
            left = mid; // mid 满足条件或小于 target，答案在 mid 或其右侧
        }
    }

    // 退出循环时 left == right，这就是右边界
    result[1] = left;

    return result;
}