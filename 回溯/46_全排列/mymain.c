#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 40320
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 回溯函数：在原始数组上通过交换生成全排列
void backtrack(int *nums, int numsSize, int start, int **result, int *returnSize)
{
    if (start == numsSize)
    {
        // 将当前排列拷贝到结果数组
        result[*returnSize] = (int *)malloc(sizeof(int) * numsSize);
        memcpy(result[*returnSize], nums, sizeof(int) * numsSize);
        (*returnSize)++;
        return;
    }
    for (int i = start; i < numsSize; i++)
    {
        swap(&nums[start], &nums[i]); // 做选择：交换元素
        backtrack(nums, numsSize, start + 1, result, returnSize);
        swap(&nums[start], &nums[i]); // 撤销选择：回溯
    }
}
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 0;
    int **result = (int **)malloc(MAX_SIZE * sizeof(int *));
    backtrack(nums, numsSize, 0, result, returnSize);
    // 按要求填写每行长度
    *returnColumnSizes = (int *)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = numsSize;
    }
    return result;
}