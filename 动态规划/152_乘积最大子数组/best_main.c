#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maxProduct(int *nums, int numsSize)
{
    if (numsSize == 0)
        return 0;

    // 使用 double 防止中间运算过程溢出
    double max_prod = nums[0];
    double min_prod = nums[0];
    double ans = nums[0];

    for (int i = 1; i < numsSize; i++)
    {
        // 遇到负数时，最大的会变最小，最小的会变最大，直接交换
        if (nums[i] < 0)
        {
            double temp = max_prod;
            max_prod = min_prod;
            min_prod = temp;
        }

        // 判断是重新开始，还是乘上之前的积累值
        max_prod = MAX((double)nums[i], max_prod * nums[i]);
        min_prod = MIN((double)nums[i], min_prod * nums[i]);

        // 随时更新全局最大值
        ans = MAX(ans, max_prod);
    }

    return (int)ans;
}