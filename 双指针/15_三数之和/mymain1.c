// 2026.6.3
#include <stdlib.h>

int cmp(const void *p1, const void *p2)
{
    return *(int *)p1 - *(int *)p2;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 0;
    qsort(nums, numsSize, sizeof(int), cmp);
    int **res = (int **)malloc(numsSize * numsSize * sizeof(int *));
    *returnColumnSizes = (int *)malloc(numsSize * numsSize * sizeof(int));
    for (int i = 0; i < numsSize - 2; i++)
    {
        if (nums[i] > 0)
            break;
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        int left = i + 1;
        int right = numsSize - 1;
        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum > 0)
                right--;
            else if (sum < 0)
                left++;
            else
            {
                res[*returnSize] = (int *)malloc(3 * sizeof(int));
                res[*returnSize][0] = nums[i];
                res[*returnSize][1] = nums[left];
                res[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;
                while (left < right && nums[left] == nums[left + 1])
                    left++;
                while (left < right && nums[right] == nums[right - 1])
                    right--;
                left++;
                right--;
            }
        }
    }
    // res = (int **)realloc(res, sizeof(int *) * (*returnSize));
    // *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * (*returnSize));
    return res;
}