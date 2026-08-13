// 2026.8.12

int jump(int *nums, int numsSize)
{
    if (numsSize == 1)
        return 0;
    int step = 0;
    int curend = 0;
    int maxdis = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (i + nums[i] > maxdis)
        {
            maxdis = i + nums[i];
        }
        if (i == curend)
        {
            step++;
            curend = maxdis;
            if (maxdis >= numsSize - 1)
                break;
        }
    }
    return step;
}

// 最优做法
int jump(int *nums, int numsSize)
{
    int step = 0;
    int curEnd = 0;
    int maxDis = 0;

    for (int i = 0; i < numsSize - 1; i++)
    {
        // 当前这一跳覆盖范围内，下一跳最远能到哪里
        if (i + nums[i] > maxDis)
        {
            maxDis = i + nums[i];
        }

        // 已经走到当前这一跳的边界
        if (i == curEnd)
        {
            step++;
            curEnd = maxDis;
        }
    }

    return step;
}