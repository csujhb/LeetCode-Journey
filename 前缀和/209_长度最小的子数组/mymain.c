// 2026.8.11

int minSubArrayLen(int target, int *nums, int numsSize)
{
    int sum = 0;
    int minLen = numsSize + 1;
    int left = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum += nums[i];
        while (left <= i && sum >= target)
        {
            sum -= nums[left];
            left++;
            if (sum < target && minLen > i - left + 2)
            {
                minLen = i - left + 2;
            }
        }
    }
    if (minLen == numsSize + 1)
        return 0;
    return minLen;
}