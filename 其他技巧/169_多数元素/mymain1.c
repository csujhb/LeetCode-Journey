// 2026.6.10
int majorityElement(int *nums, int numsSize)
{
    int res = 0;
    int count = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (res == nums[i])
        {
            count++;
        }
        else
        {
            if (count == 0)
            {
                count = 1;
                res = nums[i];
            }
            else
            {
                count--;
            }
        }
    }
    return res;
}