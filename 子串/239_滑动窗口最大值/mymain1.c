// 2026.6.6
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{
    *returnSize = numsSize - k + 1;
    if (k == 1)
    {
        return nums;
    }
    int *res = (int *)malloc((numsSize - k + 1) * sizeof(int));
    int *deque = (int *)malloc(numsSize * sizeof(int)); // 这里我对开始写的是k
    int front = 0;
    int rear = -1;
    for (int i = 0; i < numsSize; i++)
    {
        while (front <= rear && nums[deque[rear]] < nums[i])
        {
            rear--;
        }
        while (front <= rear && i - deque[front] + 1 > k)
            front++;
        deque[++rear] = i;
        if (i >= k - 1)
            res[i - k + 1] = nums[deque[front]];
    }
    free(deque);
    return res;
}