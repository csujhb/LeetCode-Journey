// 超时，进入死循环
int search(int *nums, int numsSize, int target)
{
    if (numsSize == 1 && nums[0] != target)
        return -1;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target)
        {
            if (nums[mid] < nums[left])
            {
                right = mid - 1;
            }
            else if (nums[mid] > nums[right])
            {
                left = mid + 1;
            }
        }
        else if (nums[mid] < target)
        {
            if (nums[mid] < nums[left])
            {
                left = mid + 1;
            }
            else if (nums[mid] > nums[right])
            {
                right = mid - 1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}