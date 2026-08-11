// 2026.8.4

int removeDuplicates(int *nums, int numsSize)
{
    int k = 1;
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] != nums[i - 1])
        {
            nums[k++] = nums[i];
        }
    }
    return k;
}

// 更简单
int removeDuplicates(int *nums, int numsSize)
{
    int k = 0;
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[k] != nums[i])
        {        // 双指针，对比要写入的位置和整个原始数组
            k++; // 唯一元素个数/写入索引+1
            nums[k] = nums[i];
        }
    }
    return k + 1;
}