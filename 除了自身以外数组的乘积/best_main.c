/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* answer = (int*)malloc(sizeof(int) * numsSize);
    answer[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        answer[i] = nums[i - 1] * answer[i - 1];
    }
    int right = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; i--) {
        answer[i] *= right;
        right *= nums[i];
    }
    return answer;
}
