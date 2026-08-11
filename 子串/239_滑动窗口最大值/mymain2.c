// 2026.8.11
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{
    *returnSize = 0;
    if (k == 1)
    {
        *returnSize = numsSize;
        return nums;
    }
    int *res = (int *)malloc(sizeof(int) * (numsSize - k + 1));
    int *queue = (int *)malloc(sizeof(int) * numsSize);
    int front = 0, rear = -1;
    queue[++rear] = 0;
    for (int i = 1; i < numsSize; i++)
    {
        while (front <= rear && nums[queue[rear]] < nums[i])
        {
            rear--;
        }

        while (front <= rear && queue[front] < i - k + 1)
        {
            front++;
        }
        queue[++rear] = i;
        if (i >= k - 1)
        {
            res[(*returnSize)++] = nums[queue[front]];
        }
    }
    free(queue);
    return res;
}
