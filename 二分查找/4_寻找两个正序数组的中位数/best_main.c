#include <stdio.h>
#include <limits.h>

// 辅助宏：求最大值和最小值
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    // 保证 nums1 是较短的数组，这样可以最小化二分查找的范围，并防止 j 越界
    if (nums1Size > nums2Size)
    {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int m = nums1Size;
    int n = nums2Size;

    // left 和 right 是在较短数组 nums1 上二分查找的边界
    int left = 0;
    int right = m;

    // 左半部分需要的总元素个数
    int totalLeft = (m + n + 1) / 2;

    while (left <= right)
    {
        // nums1 的分割线位置
        int i = left + (right - left) / 2;
        // nums2 的分割线位置
        int j = totalLeft - i;

        // 获取边界前后的值，处理越界情况（用极值代替）
        int nums1LeftMax = (i == 0) ? INT_MIN : nums1[i - 1];
        int nums1RightMin = (i == m) ? INT_MAX : nums1[i];
        int nums2LeftMax = (j == 0) ? INT_MIN : nums2[j - 1];
        int nums2RightMin = (j == n) ? INT_MAX : nums2[j];

        // 判断是否找到了正确的分割线
        if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin)
        {
            // 找到了满足条件的划分
            if ((m + n) % 2 == 1)
            {
                // 如果总长度是奇数，中位数就是左半部分的最大值
                return MAX(nums1LeftMax, nums2LeftMax);
            }
            else
            {
                // 如果总长度是偶数，中位数是左半部分最大值和右半部分最小值的平均数
                return (MAX(nums1LeftMax, nums2LeftMax) + MIN(nums1RightMin, nums2RightMin)) / 2.0;
            }
        }
        else if (nums1LeftMax > nums2RightMin)
        {
            // nums1 的左边元素太大，说明分割线 i 偏右了，需要向左移动
            right = i - 1;
        }
        else
        {
            // nums2 的左边元素太大，说明分割线 i 偏左了，需要向右移动
            left = i + 1;
        }
    }

    // 正常情况下不会走到这里，除非输入不是有序数组
    return 0.0;
}