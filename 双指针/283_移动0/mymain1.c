// 2026.6.3
void moveZeroes(int *nums, int numsSize)
{
    int k = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != 0)
        {
            nums[k++] = nums[i];
        }
    }
    for (int i = k; i < numsSize; i++)
    {
        nums[i] = 0;
    }
}