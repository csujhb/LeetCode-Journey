// 2026.8.12
#include <stdbool.h>
bool canJump(int *nums, int numsSize)
{
    int fastest = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (fastest < i)
            return false;
        if (fastest < i + nums[i])
            fastest = i + nums[i];
        if (fastest >= numsSize - 1)
            return true;
    }
    return false;
}