int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        while (nums[i] >= 1 &&
            nums[i] <= numsSize &&
            nums[nums[i] - 1] != nums[i]) {
            int target = nums[i] - 1;
            int temp = nums[target];
            nums[target] = nums[i];
            nums[i] = temp;
        }
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    return numsSize + 1;
}
