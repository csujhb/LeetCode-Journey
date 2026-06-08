// 2026.6.8
//  第一遍没做出来
//   int search(int *nums, int numsSize, int target)
//   {
//       int left = 0;
//       int right = numsSize - 1;
//       while (left <= right)
//       {
//           int mid = left + (right - left) / 2;
//           if (nums[mid] < target)
//           {
//               if (nums[mid] > nums[0])
//               {
//                   left = mid + 1;
//               }
//               else
//               {
//                   right = mid - 1;
//               }
//           }
//           else if (nums[mid] > target)
//           {
//               if (nums[mid] > nums[0])
//               {
//                   right = mid - 1;
//               }
//               else
//               {
//                   left = mid + 1;
//               }
//           }
//       }
//   }
int search(int *nums, int numsSize, int target)
{
    int left = 0;
    int right = numsSize - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] >= nums[left])
        {
            if (nums[left] <= target && nums[mid] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        else
        {
            if (target > nums[mid] && target <= nums[right])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }
    return -1;
}