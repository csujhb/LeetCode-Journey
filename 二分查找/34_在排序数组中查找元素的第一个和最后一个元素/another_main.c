#include <stdlib.h>

// 辅助函数：查找第一个目标值的位置
int findFirstPosition(int *nums, int numsSize, int target)
{
    int left = 0;
    int right = numsSize - 1;
    int firstPos = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // 防止 left + right 溢出
        if (nums[mid] == target)
        {
            firstPos = mid;  // 记录下当前找到的位置
            right = mid - 1; // 收缩右边界，继续在左侧查找是否有更早的
        }
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return firstPos;
}

// 辅助函数：查找最后一个目标值的位置
int findLastPosition(int *nums, int numsSize, int target)
{
    int left = 0;
    int right = numsSize - 1;
    int lastPos = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            lastPos = mid;  // 记录下当前找到的位置
            left = mid + 1; // 收缩左边界，继续在右侧查找是否有更晚的
        }
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return lastPos;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    // 动态分配大小为 2 的整数数组用于返回结果
    int *result = (int *)malloc(2 * sizeof(int));
    *returnSize = 2; // 必须设置返回数组的大小

    // 默认情况，找不到返回 [-1, -1]
    result[0] = -1;
    result[1] = -1;

    // 边界情况处理：空数组
    if (numsSize == 0)
    {
        return result;
    }

    // 1. 查找左边界
    int firstPos = findFirstPosition(nums, numsSize, target);

    // 如果左边界都没找到，说明数组中根本没有 target，直接返回即可
    if (firstPos == -1)
    {
        return result;
    }

    // 2. 查找右边界
    int lastPos = findLastPosition(nums, numsSize, target);

    result[0] = firstPos;
    result[1] = lastPos;

    return result;
}