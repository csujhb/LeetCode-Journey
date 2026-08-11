// 2026.8.3
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
    int maxCapacity = numsSize * numsSize;
    int **res = (int **)malloc(maxCapacity * sizeof(int *));
    for (int i = 0; i < numsSize - 2; i++)
    {
        if (nums[i] > 0)
            break;
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int j = i + 1;
        int k = numsSize - 1;

        while (j < k)
        {
            if (nums[i] + nums[j] + nums[k] > 0)
            {
                k--;
            }
            else if (nums[i] + nums[j] + nums[k] < 0)
            {
                j++;
            }
            else
            {
                res[*returnSize] = (int *)malloc(3 * sizeof(int));
                res[*returnSize][0] = nums[i];
                res[*returnSize][1] = nums[j];
                res[*returnSize][2] = nums[k];
                (*returnSize)++;
                while (j < k && nums[j] == nums[j + 1])
                {
                    j++;
                }
                while (j < k && nums[k] == nums[k - 1])
                {
                    k--;
                }
                k--;
                j++;
            }
        }
    }
    *returnColumnSizes = (int *)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < (*returnSize); i++)
    {
        (*returnColumnSizes)[i] = 3;
    }
    return res;
}