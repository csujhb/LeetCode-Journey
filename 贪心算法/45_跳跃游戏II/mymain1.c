int jump(int *nums, int numsSize)
{
    int count = 0;
    int curEnd = 0;
    int dis = 0;
    for (int i = 0; i < numsSize - 1; i++)
    {
        if (i + nums[i] > dis)
        {
            dis = i + nums[i];
        }
        if (i == curEnd)
        {
            count++;
            curEnd = dis;
            if (curEnd >= numsSize - 1)
                break;
        }
    }
    return count;
}