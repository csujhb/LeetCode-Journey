#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 回溯主函数
// nums: 原数组, numsSize: 数组大小
// used: 标记数组, 记录数字是否被使用过
// path: 当前路径数组, pathIndex: 当前路径的长度
// res: 最终结果的二维数组, returnSize: 结果二维数组的行数
void backtrack(int *nums, int numsSize, bool *used, int *path, int pathIndex, int **res, int *returnSize)
{
    // 触发结束条件：当路径长度等于原数组长度时，说明找到了一组全排列
    if (pathIndex == numsSize)
    {
        // 为当前这组排列申请内存
        res[*returnSize] = (int *)malloc(sizeof(int) * numsSize);
        // 将当前路径深拷贝到结果集中
        for (int i = 0; i < numsSize; i++)
        {
            res[*returnSize][i] = path[i];
        }
        (*returnSize)++; // 结果集行数加 1
        return;
    }

    // 遍历所有可能的选择
    for (int i = 0; i < numsSize; i++)
    {
        // 如果该数字在当前路径中已经被使用过，则跳过
        if (used[i])
            continue;

        // 做选择：将数字加入路径，并标记为已使用
        path[pathIndex] = nums[i];
        used[i] = true;

        // 进入下一层决策树
        backtrack(nums, numsSize, used, path, pathIndex + 1, res, returnSize);

        // 撤销选择（回溯过程）：将状态重置，以便尝试下一个数字
        used[i] = false;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    // 1. 计算全排列的最大数量 (题目限制 nums.length <= 6，6! = 720)
    int maxPermutations = 1;
    for (int i = 1; i <= numsSize; i++)
    {
        maxPermutations *= i;
    }

    // 2. 分配结果集二维数组的内存
    int **res = (int **)malloc(sizeof(int *) * maxPermutations);
    // 3. 分配记录每一行长度的一维数组的内存
    *returnColumnSizes = (int *)malloc(sizeof(int) * maxPermutations);
    *returnSize = 0;

    // 4. 分配路径数组和标记数组
    int *path = (int *)malloc(sizeof(int) * numsSize);
    bool *used = (bool *)calloc(numsSize, sizeof(bool)); // calloc 自动初始化数组为 false (0)

    // 5. 开始回溯
    backtrack(nums, numsSize, used, path, 0, res, returnSize);

    // 6. 填充 returnColumnSizes 数组
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = numsSize; // 全排列的每一行长度都是固定的 numsSize
    }

    // 7. 释放辅助数组（注意：res 和 returnColumnSizes 需要返回，不能释放）
    free(path);
    free(used);

    return res;
}