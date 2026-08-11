#include <stdbool.h>
bool canJump(int *nums, int numsSize)
{
    int dis = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (i > dis)
            return false;
        if (i + nums[i] > dis)
            dis = i + nums[i];
        if (dis >= numsSize - 1)
            return true;
    }
    return false;
}