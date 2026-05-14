int search(int *nums, int numsSize, int target)
{
    int left = 0;
    int right = numsSize - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        // 运气好，直接找到
        if (nums[mid] == target)
        {
            return mid;
        }

        // 判断哪一部分是严格有序的
        if (nums[left] <= nums[mid])
        {
            // 左半部分 [left, mid] 严格升序有序
            // 判断 target 是否落在左半边这个有序区间内
            if (target >= nums[left] && target < nums[mid])
            {
                right = mid - 1; // 目标在左边，缩小右边界
            }
            else
            {
                left = mid + 1; // 否则，目标肯定在右边包含旋转点的那一半
            }
        }
        else
        {
            // 右半部分 [mid, right] 严格升序有序
            // 判断 target 是否落在右半边这个有序区间内
            if (target > nums[mid] && target <= nums[right])
            {
                left = mid + 1; // 目标在右边，缩小左边界
            }
            else
            {
                right = mid - 1; // 否则，目标肯定在左边包含旋转点的那一半
            }
        }
    }

    return -1; // 没找到
}