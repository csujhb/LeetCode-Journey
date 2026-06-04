// 2026.6.3
int firstMissingPositive(int *nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        while (nums[i] >= 1 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1])
        {
            int temp1 = nums[i] - 1;
            int temp2 = nums[temp1];
            nums[temp1] = nums[i];
            nums[i] = temp2;
        }
    }
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != i + 1)
            return i + 1;
    }
    return numsSize + 1;
}