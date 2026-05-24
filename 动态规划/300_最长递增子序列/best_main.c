// 贪心算法+二分查找
#include <stdlib.h>

int lengthOfLIS(int *nums, int numsSize)
{
    if (numsSize == 0)
        return 0;

    // tails 数组用于存储每个牌堆顶的值
    int *tails = (int *)malloc(numsSize * sizeof(int));
    int len = 0; // len 记录当前牌堆的总数（即最长递增子序列的长度）

    for (int i = 0; i < numsSize; i++)
    {
        int x = nums[i];

        // 核心：在 tails 数组的 [0, len) 范围内二分查找第一个 >= x 的位置
        int left = 0, right = len;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (tails[mid] < x)
            {
                left = mid + 1; // 目标在右半区
            }
            else
            {
                right = mid; // 目标在左半区（包含 mid）
            }
        }

        // 此时 left 就是 x 应该放置的“牌堆”索引
        tails[left] = x;

        // 如果 left 等于 len，说明 x 比所有现有堆顶都大，必须新建一个牌堆
        if (left == len)
        {
            len++;
        }
    }

    free(tails);
    return len; // 牌堆的总数就是最终答案
}