// 2026.6.3
#include <limits.h>
int maxSubArray(int *nums, int numsSize)
{
    int max = INT_MIN;
    int curPre = 0;
    int minPre = 0;
    for (int i = 0; i < numsSize; i++)
    {
        curPre += nums[i];
        if (max < curPre - minPre)
            max = curPre - minPre;
        if (curPre < minPre)
            minPre = curPre;
    }
    return max;
}