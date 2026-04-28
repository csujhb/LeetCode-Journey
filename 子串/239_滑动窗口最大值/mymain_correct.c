#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    int* deque = (int*)malloc(sizeof(int) * numsSize); // 存下标

    int front = 0, rear = -1;

    for (int i = 0; i < numsSize; i++) {
        // 1. 移除队首过期元素
        while (front <= rear && deque[front] <= i - k) {
            front++;
        }

        // 2. 维持单调递减队列
        while (front <= rear && nums[deque[rear]] <= nums[i]) {
            rear--;
        }

        // 3. 当前下标入队
        deque[++rear] = i;

        // 4. 窗口形成后记录答案
        if (i >= k - 1) {
            result[i-k+1] = nums[deque[front]];
        }
    }

    free(deque);
    return result;
}
