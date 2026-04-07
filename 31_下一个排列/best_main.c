void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int *arr, int left, int right) {
    while (left < right) {
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    int right = numsSize - 2;
    
    // 1. 从后向前找第一个升序对
    while (right >= 0 && nums[right] >= nums[right + 1]) {
        right--;
    }
    
    // 2. 如果找到了，再从后向前找第一个比 nums[right] 大的数并交换
    if (right >= 0) {
        int i = numsSize - 1;
        while (nums[i] <= nums[right]) {
            i--;
        }
        swap(&nums[i], &nums[right]);
    }
    
    // 3. 反转 right 之后的所有元素（如果 right < 0，正好反转整个数组）
    reverse(nums, right + 1, numsSize - 1);
}