# LeetCode198 打家劫舍算法学习笔记

## 题目核心拆解

面对一排房屋，每个房屋里有特定金额的现金。唯一的限制是不能同时抢劫相邻的房屋。目标是计算在不触动警报的情况下，能够获取的最高总金额。
在遍历房屋时，面临的选择永远只有两个分支：抢当前这间房，或者不抢当前这间房。这构成了重叠子问题和最优子结构，是典型的动态规划应用场景。

## 记忆化搜索算法（自顶向下）

### 算法思路
通过递归的方式从最后一间房屋往前推导。假设当前在第 $i$ 间房屋，做出决定的逻辑如下：
* 如果抢劫当前房屋，那么前一间房屋绝对不能碰。总收益为第 $i-2$ 间房屋的最大收益加上当前房屋的金额。
* 如果不抢劫当前房屋，那么总收益就等于第 $i-1$ 间房屋的最大收益。

取这两种情况的较大值即可。为了避免递归过程中产生大量重复计算（即重叠子问题），我们引入一个备忘录数组，将计算过的结果保存下来，下次遇到相同的状态直接读取即可，这就大幅缩减了时间开销。

### C语言代码实现
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 辅助函数：求两数最大值
int maxVal(int a, int b) {
    return a > b ? a : b;
}

// 递归工作函数
int robHelper(int* nums, int index, int* memo) {
    // 边界条件：如果索引小于零，说明没有房屋了，收益为零
    if (index < 0) {
        return 0;
    }
    // 如果备忘录中已经有记录，直接返回记录的值
    if (memo[index] != -1) {
        return memo[index];
    }
    
    // 核心状态转移：抢当前房屋 vs 不抢当前房屋
    int robCurrent = nums[index] + robHelper(nums, index - 2, memo);
    int skipCurrent = robHelper(nums, index - 1, memo);
    
    // 将结果存入备忘录并返回
    memo[index] = maxVal(robCurrent, skipCurrent);
    return memo[index];
}

int robMemoization(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    // 初始化备忘录，所有值设为-1表示该状态尚未计算
    int* memo = (int*)malloc(numsSize * sizeof(int));
    memset(memo, -1, numsSize * sizeof(int));
    
    // 从最后一间房屋开始推导
    int result = robHelper(nums, numsSize - 1, memo);
    
    // 释放内存
    free(memo);
    return result;
}
```

## 动态规划基础版（自底向上）

### 算法思路
与记忆化搜索的从后往前推导相反，动态规划是利用数组从前往后一步步递推计算结果。
定义一个一维数组 `dp`，其中 $dp[i]$ 表示抢劫到第 $i$ 间房屋时能获取的最大收益。
* 初始状态：对于第一间房屋，只能抢它；对于前两间房屋，抢金额较大的那个。
* 状态转移方程：$dp[i] = \max(dp[i-1], dp[i-2] + nums[i])$

通过遍历所有房屋，逐步填充 `dp` 数组，数组最后一个元素即为最终答案。

### C语言代码实现
```c
#include <stdio.h>
#include <stdlib.h>

int maxValDp(int a, int b) {
    return a > b ? a : b;
}

int robDP(int* nums, int numsSize) {
    // 处理极端边界情况
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];

    // 申请动态规划数组并初始化
    int* dp = (int*)malloc(numsSize * sizeof(int));
    
    // 设定基础状态
    dp[0] = nums[0];
    dp[1] = maxValDp(nums[0], nums[1]);

    // 自底向上递推计算后续所有房屋的状态
    for (int i = 2; i < numsSize; i++) {
        dp[i] = maxValDp(dp[i-1], dp[i-2] + nums[i]);
    }

    // 获取并返回最终结果
    int result = dp[numsSize - 1];
    free(dp);
    return result;
}
```

## 动态规划状态压缩版（空间优化）

### 算法思路
观察上述动态规划的基础版本，每次计算当前房屋的最大收益 $dp[i]$ 时，仅仅依赖于前面的两个相邻状态：$dp[i-1]$ 和 $dp[i-2]$。
因此，完全没有必要在内存中维护一整个数组。只需要定义两个独立的变量，分别代表“上一个房屋的最大收益”和“上上个房屋的最大收益”。在遍历房屋的过程中，如同滑动窗口般不断向前覆盖更新这两个变量，即可将空间复杂度从线性降至常数级别。

### C语言代码实现
```c
#include <stdio.h>

int maxValOpt(int a, int b) {
    return a > b ? a : b;
}

int robOptimized(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];

    // prev2 代表隔一间房屋的最大收益
    int prev2 = 0; 
    // prev1 代表相邻上一间房屋的最大收益
    int prev1 = 0; 
    // 记录当前计算出的最大收益
    int current = 0; 

    // 滚动更新状态
    for (int i = 0; i < numsSize; i++) {
        current = maxValOpt(prev1, prev2 + nums[i]);
        
        // 为下一次循环做准备，变量整体向前移动一位
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}
```

## 全文总结

解决这类求极值的数组遍历问题，思维的演进过程通常是有清晰脉络可循的。

* **关于思维推导**：面对多选择分支问题，最直观的解法往往是递归。当发现递归树中存在大量重复的计算分支时，引入备忘录就成为了水到渠成的一步，由此构成了“记忆化搜索”。
* **关于方向转换**：自顶向下的递归往往伴随系统调用栈的额外开销。将其思维模式翻转为自底向上的迭代，利用数组进行地推，就得到了标准的“动态规划”模型。
* **关于极致优化**：完成基础的动态规划模型后，仔细审视状态转移方程。如果发现当前状态只依赖于固定数量的历史状态，就可以抛弃完整的状态数组，改用有限的几个变量进行滚动更新。这就是“状态压缩”，能让内存占用达到最优。

以上三种方法在时间复杂度上均达到了线性的级别。但在空间消耗上，经过逐步剖析与优化，最终的滚动变量法将空间复杂度压缩到了极限，不仅运行效率最高，也是算法面试与工程实践中最受青睐的解法。