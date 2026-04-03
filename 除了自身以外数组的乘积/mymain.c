#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
	int* leftArr = (int*)calloc(numsSize, sizeof(int));
	int* rightArr = (int*)calloc(numsSize, sizeof(int));
	int* result = (int*)calloc(numsSize, sizeof(int));
	leftArr[0] = 1;
	rightArr[numsSize - 1] = 1;
	for (int i = 1; i < numsSize; i++) {
		leftArr[i] = nums[i - 1] * leftArr[i - 1];
	}
	for (int i = numsSize - 2; i >= 0; i--) {
		rightArr[i] = nums[i + 1] * rightArr[i + 1];
	}
	for (int i = 0; i < numsSize; i++) {
		result[i] = rightArr[i] * leftArr[i];
	}
	free(leftArr);
	free(rightArr);
	*returnSize = numsSize;
	return result;
}
