// 不对，会超时
#include <limits.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int targetNum = (nums1Size + nums2Size + 1) / 2;
    int left2 = 0, left1 = 0;
    if (nums1Size < nums2Size)
    {
        int left1 = (nums1Size + 1) / 2;
        int left2 = targetNum - left1;
    }
    else
    {
        int left2 = (nums2Size + 1) / 2;
        int left1 = targetNum - left2;
    }
    while (left1 >= 0 && left2 >= 0 && left1 <= nums1Size && left2 <= nums2Size)
    {
        int r1 = (left1 == 0 ? INT_MIN : nums1[left1 - 1]);
        int r2 = (left2 == 0 ? INT_MIN : nums2[left2 - 1]);
        int l1 = (left1 >= nums1Size ? INT_MAX : nums1[left1]);
        int l2 = (left2 >= nums1Size ? INT_MAX : nums2[left2]);
        if (l1 > r2)
        {
            left1--;
            left2++;
        }
        if (l2 > r1)
        {
            left1++;
            left2--;
        }
        if (l1 <= r2 && l2 <= r1)
        {
            break;
        }
    }

    return (nums1Size + nums2Size) % 2 == 1 ? MAX(nums1[left1 - 1], nums2[left2 - 1]) : (MAX(nums1[left1 - 1], nums2[left2 - 1]) + MIN(nums1[left1], nums2[left2])) * 1.0 / 2;
}