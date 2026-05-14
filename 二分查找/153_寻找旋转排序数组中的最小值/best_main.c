int findMin(int *nums, int numsSize)
{
    int left = 0;
    int right = numsSize - 1;

    // 注意这里是 left < right，而不是 left <= right
    while (left < right)
    {
        int mid = left + (right - left) / 2;

        // 拿中间值和最右边的值比较
        if (nums[mid] > nums[right]) // 或nums[mid] > nums[numsSize - 1]，有重复元素时必须nums[mid] > nums[right]
        {
            // 最小值在右半边，且肯定不是 mid
            left = mid + 1;
        }
        else
        {
            // 最小值在左半边，或者是 mid 本身
            right = mid;
        }
    }

    // 循环结束时，left 和 right 一定指向同一个位置，即最小值
    return nums[left];
}

// 最大值
/*
int findMax(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;

    // 处理完全升序的特殊情况（没有旋转，或者旋转了 n 次）
    if (nums[left] < nums[right]) {
        return nums[right];
    }

    while (left < right) {
        // ⚠️ 致命陷阱：求 mid 时必须向上取整（加 1）
        int mid = left + (right - left + 1) / 2;

        // 翻译：如果条件为 True
        if (nums[mid] >= nums[0]) {
            // mid 在 True 阵营里。
            // 第一个 False 在右边，最大值（最后一个 True）可能是 mid，也可能在 mid 右边。
            // 绝不能跳过 mid！
            left = mid;
        }
        // 翻译：如果条件为 False
        else {
            // mid 已经落入 False 阵营（右半边的小数部分）
            // 最大值一定在 mid 的严格左侧，我们要越过 mid。
            right = mid - 1;
        }
    }

    return nums[left];
}
*/