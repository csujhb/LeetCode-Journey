// 2026.6.10
void reverse(int *nums, int left, int right)
{
    while (left < right)
    {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
        left++;
        right--;
    }
}

void nextPermutation(int *nums, int numsSize)
{
    int i = numsSize - 2;

    while (i >= 0 && nums[i] >= nums[i + 1])
    {
        i--;
    }
    if (i >= 0)
    {
        int new = numsSize - 1;
        while (nums[new] <= nums[i])
        {
            new--;
        }
        int temp = nums[new];
        nums[new] = nums[i];
        nums[i] = temp;
    }
    reverse(nums, i + 1, numsSize - 1);
}