
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
	*returnSize = 0;
	int* result = (int*)malloc((numsSize-k+1) * sizeof(int));
    int* deque = (int*)malloc(sizeof(int) * numsSize); // 存储索引的双端队列
    int front = 0, rear = -1;

    for (int i = 0; i < numsSize; i++) {
        // 移除队尾所有小于当前元素的索引（保持递减）
        while (front <= rear && nums[deque[rear]] < nums[i]) {
            rear--;
        }
        // 当前元素索引入队
        deque[++rear] = i;

        // 移除队首超出窗口的索引
        if (deque[front] <= i - k) {
            front++;
        }

        // 当窗口形成时，输出最大值
        if (i >= k - 1) {
            result[(*returnSize)++] = nums[deque[front]];
        }
    }
    free(deque);
    return result;
}
