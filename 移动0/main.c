void moveZeroes(int* nums, int numsSize) {
    int k = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[k++] = nums[i];
        }
    }

    while (k < numsSize) {
        nums[k++] = 0;
    }
}

/*
void moveZeroes(int* nums, int numsSize) {
    int k = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            int temp = nums[i];
            nums[i] = nums[k];
            nums[k] = temp;
            k++;
        }
    }
}*/
