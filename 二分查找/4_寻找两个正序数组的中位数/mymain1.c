// 2026.6.8
#include <limits.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    if (nums1Size > nums2Size)
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    int left = 0;
    int right = nums1Size;
    int all_left = (nums1Size + nums2Size + 1) / 2;
    while (left <= right)
    {
        int mid1 = left + (right - left) / 2;
        int mid2 = all_left - mid1;
        int leftMax1 = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
        int rightMin1 = (mid1 == nums1Size) ? INT_MAX : nums1[mid1];
        int leftMax2 = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];
        int rightMin2 = (mid2 == nums2Size) ? INT_MAX : nums2[mid2];
        if (leftMax1 <= rightMin2 && leftMax2 <= rightMin1)
        {
            if ((nums1Size + nums2Size) % 2 == 1)
                return MAX(leftMax1, leftMax2);
            else
                return (MAX(leftMax1, leftMax2) + MIN(rightMin1, rightMin2)) / 2.0;
        }
        else if (leftMax1 > rightMin2)
            right = mid1 - 1;
        else
            left = mid1 + 1;
    }
    return 0.0;
}