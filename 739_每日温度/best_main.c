// 利用了结果数组自带的动态规划（DP）属性，把空间压到了极致
#include <stdlib.h>
#include <stdbool.h>

int *dailyTemperatures(int *temperatures, int temperaturesSize, int *returnSize)
{
    int *res = (int *)calloc(temperaturesSize, sizeof(int));
    *returnSize = temperaturesSize;

    // 从倒数第二天开始，从右向左遍历（最后一天肯定是 0，calloc 已经处理了）
    for (int i = temperaturesSize - 2; i >= 0; i--)
    {
        int j = i + 1; // 先看紧挨着右边的那一天

        while (true)
        {
            if (temperatures[j] > temperatures[i])
            {
                res[i] = j - i; // 找到了，记录天数差
                break;
            }
            else if (res[j] == 0)
            {
                res[i] = 0; // 右边再也没有更高的温度了
                break;
            }

            // 核心优化：利用已知结果，直接跳过那些肯定不满足条件的温度！
            j += res[j];
        }
    }

    return res;
}