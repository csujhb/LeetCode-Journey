// 2026.6.10
int findDuplicate(int *nums, int numsSize)
{
    int fast = nums[nums[0]];
    int slow = nums[0];
    while (fast != slow)
    {
        fast = nums[nums[fast]];
        slow = nums[slow];
    }
    fast = 0;
    while (slow != fast)
    {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}