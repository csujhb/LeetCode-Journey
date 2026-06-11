// 2026.6.10
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sortColors(int *nums, int numsSize)
{
    int idx0 = 0;
    int idx2 = numsSize - 1;
    int i = 0;
    while (i <= idx2)
    {
        if (nums[i] == 2)
        {
            swap(nums + i, nums + idx2);
            idx2--;
        }
        else if (nums[i] == 0)
        {
            swap(nums + i, nums + idx0);
            i++;
            idx0++;
        }
        else
        {
            i++;
        }
    }
}