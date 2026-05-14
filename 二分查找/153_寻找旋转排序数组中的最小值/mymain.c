#include <limits.h>
#define MIN(a, b) ((a) > (b) ? (b) : (a))
int findMin(int *nums, int numsSize)
{
    if (numsSize == 1)
        return nums[0];
    int min = INT_MAX;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[left] <= nums[mid])
        {
            if (nums[left] < nums[right])
            {
                min = MIN(min, nums[left]);
                right = mid - 1;
            }
            else
            {
                min = MIN(min, nums[right]);
                left = mid + 1;
            }
        }
        else
        {
            min = MIN(min, nums[mid]);
            right = mid - 1;
        }
    }
    return min;
}