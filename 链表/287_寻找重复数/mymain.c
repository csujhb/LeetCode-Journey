// 2026.8.13
int findDuplicate(int *nums, int numsSize)
{
    int fast = nums[nums[0]], slow = nums[0];
    while (fast != slow)
    {
        fast = nums[nums[fast]];
        slow = nums[slow];
    }
    fast = 0;
    while (fast != slow)
    {
        fast = nums[fast];
        slow = nums[slow];
    }
    return slow;
}

// 最优做法
int findDuplicate(int *nums, int numsSize)
{
    int slow = 0;
    int fast = 0;

    // 第一阶段：找到环中相遇点
    do
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // 第二阶段：寻找环入口
    fast = 0;

    while (fast != slow)
    {
        fast = nums[fast];
        slow = nums[slow];
    }

    return slow;
}