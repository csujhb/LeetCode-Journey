# 算法研读笔记：最大乘积子数组 (LeetCode 152)

## 一、 原题描述

**题目：乘积最大子数组 (Maximum Product Subarray)**

给你一个整数数组 `nums` ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

*测试用例的答案保证是一个 32 位有符号整数。*
*子数组是数组的连续子序列。*

**示例 1:**

* 输入: `nums = [2,3,-2,4]`
* 输出: `6`
* 解释: 子数组 `[2,3]` 有最大乘积 `6`。

**示例 2:**

* 输入: `nums = [-2,0,-1]`
* 输出: `0`
* 解释: 结果不能为 `2`, 因为 `[-2,-1]` 不是连续子数组。

---

## 二、 问题定义与解析

本问题的核心难点在于数组内可能包含负数与零，导致乘积的单调性被破坏（即局部最优无法直接推导全局最优）。一个极小的负数在遇到另一个负数后，可能发生阶跃式的反转，瞬间成为极大的正数。因此，传统的单向极值维护策略在此失效。

## 三、 算法机理与状态空间设计

本问题隶属于典型的动态规划（Dynamic Programming）范畴。为应对负数引发的符号反转效应，状态空间必须同时维护“最大值”与“最小值”两个维度。

设 $dp_{max}[i]$ 为以第 $i$ 个元素结尾的连续子数组的最大乘积，设 $dp_{min}[i]$ 为以第 $i$ 个元素结尾的连续子数组的最小乘积。

### 状态转移方程

对于任意 $i \in [1, n-1]$，状态转移需考虑当前元素自身、当前元素与前驱最大值之积、当前元素与前驱最小值之积三者的极值：

$$dp_{max}[i] = \max(nums[i], \max(dp_{max}[i-1] \times nums[i], dp_{min}[i-1] \times nums[i]))$$

$$dp_{min}[i] = \min(nums[i], \min(dp_{max}[i-1] \times nums[i], dp_{min}[i-1] \times nums[i]))$$

**特判逻辑优化**：当 $nums[i] < 0$ 时，$dp_{max}[i-1] \times nums[i]$ 必然缩减，$dp_{min}[i-1] \times nums[i]$ 必然放大。为简化代码逻辑，可在处理负数前直接交换当前记录的最大值与最小值，从而统一运算表达式，消除复杂的条件分支。

## 四、 边界条件与溢出防御

在 C/C++ 语言标准中，有符号整数的溢出（Signed Integer Overflow）属于未定义行为（Undefined Behavior, UB）。

* **零的处理**：当遇到 `0` 时，累积乘积归零，相当于逻辑上的分段隔离，算法自动从下一元素重新开始寻找最优解。
* **类型安全**：在极端测试用例（如大量负数连续相乘）下，中间状态 $dp_{min}$ 极易向下击穿 `INT_MIN`，甚至 `LLONG_MIN`。采用双精度浮点数 `double` 存储中间状态可有效规避 UB 报错，且由于答案保证在 32 位整型范围内，浮点数在求取最终结果时不会引入精度损失。

## 五、 复杂度论证

* **时间复杂度**：$O(n)$。仅需对长度为 $n$ 的数组进行一次线性扫描。
* **空间复杂度**：$O(1)$。利用滚动变量（状态压缩）技术，由于 $dp[i]$ 的计算仅依赖于 $dp[i-1]$，无需开辟 $O(n)$ 的状态数组，仅维护三个常数级变量（当前最大、当前最小、全局最优）即可完成推导。

## 六、 C/C++ 标准实现

```c
#include <stdio.h>

#define MAX_VAL(a, b) ((a) > (b) ? (a) : (b))
#define MIN_VAL(a, b) ((a) < (b) ? (a) : (b))

int maxProduct(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    // 采用 double 防御中间态乘法导致的整数溢出 (UB)
    double current_max = nums[0];
    double current_min = nums[0];
    double global_max = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        // 负数将反转最值，预先交换状态
        if (nums[i] < 0) {
            double temp = current_max;
            current_max = current_min;
            current_min = temp;
        }
        
        // 状态转移计算
        current_max = MAX_VAL((double)nums[i], current_max * nums[i]);
        current_min = MIN_VAL((double)nums[i], current_min * nums[i]);
        
        // 更新全局最优解
        global_max = MAX_VAL(global_max, current_max);
    }
    
    return (int)global_max;
}

```