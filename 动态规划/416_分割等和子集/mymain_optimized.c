#include <stdbool.h>
#include <stdlib.h>

bool canPartition(int *nums, int numsSize)
{
    int sum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum += nums[i];
    }

    // 奇数直接剪枝
    if (sum % 2 != 0)
        return false;

    int target = sum / 2;
    bool *dp = (bool *)calloc(target + 1, sizeof(bool));
    if (!dp)
        return false; // 防御性编程：检查内存分配是否成功

    dp[0] = true;

    for (int i = 0; i < numsSize; i++)
    {
        // 内层循环必须逆序，保证 0-1 背包的物品不被重复使用
        for (int j = target; j >= nums[i]; j--)
        {
            // 利用逻辑或更新状态，消除 if 分支指令
            dp[j] = dp[j] || dp[j - nums[i]];
        }

        // 提前剪枝：如果已经能凑出 target，直接结束循环
        if (dp[target])
            break;
    }

    // 暂存结果，释放堆内存防止泄漏
    bool result = dp[target];
    free(dp);

    return result;
}