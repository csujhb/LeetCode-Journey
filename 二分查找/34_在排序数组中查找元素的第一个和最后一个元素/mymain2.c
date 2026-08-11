int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;
    int *res = (int *)malloc(sizeof(int) * 2);
    res[0] = res[1] = -1;
    if (numsSize == 0)
        return res;

    // 找左边界（第一个 >= target）
    int l = 0, r = numsSize - 1;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] >= target)
            r = mid;
        else
            l = mid + 1;
    }
    if (nums[l] != target)
        return res;
    res[0] = l;

    // 找右边界（最后一个 <= target）
    r = numsSize - 1;
    while (l < r)
    {
        int mid = l + (r - l + 1) / 2; // 取右中位数，避免死循环
        if (nums[mid] <= target)
            l = mid;
        else
            r = mid - 1;
    }
    res[1] = l; // 此时 l == 右边界

    return res;
}