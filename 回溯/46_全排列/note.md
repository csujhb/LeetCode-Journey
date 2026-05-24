## 力扣 46：全排列 (C 语言) 学习笔记

### 1. 算法本质：回溯法 (Backtracking)

全排列问题没有捷径，本质是一场**毫无遗漏的穷举**。我们可以将其想象为一个“填空游戏”或“走迷宫”：

* **路径 (`path`)**：记录当前已经做出的选择。
* **选择列表 (`used`)**：记录哪些数字还能用，防止同一个数字在一个排列中被重复使用。
* **结束条件**：当路径的长度等于原数组的长度时，说明所有的空都填满了，收获一个完整排列。

### 2. 回溯 vs 动态规划 (DP)

初学时极易将两者混淆，记住它们的核心区别：

| 对比维度 | 回溯算法 (Backtracking) | 动态规划 (DP) |
| --- | --- | --- |
| **核心目标** | **穷举**所有具体的解（如所有排列组合） | 求**最优解**（最大/小值）或**方案总数** |
| **状态重叠** | **无**重叠，每条路径都是独一无二的 | **有**重叠子问题，可以通过查表复用结果 |
| **行为模式** | 一路走到黑 $\rightarrow$ 撞墙 $\rightarrow$ 退一步换条路 | 发现曾经计算过这个状态 $\rightarrow$ 直接抄答案 |

### 3. 通用回溯代码模板

掌握这个模板，几乎可以秒杀所有基础的排列、组合、子集问题。核心灵魂在于“做选择”**与**“撤销选择”的对称性。

```c
void backtrack(参数) {
    if (满足结束条件) {
        // 将当前 path 深拷贝并存入结果集
        return;
    }

    for (遍历当前可选的选择) {
        if (该选择已被使用) continue; // 剪枝

        // 1. 做选择
        将选择加入 path;
        标记该选择为已使用;

        // 2. 进入下一层决策树
        backtrack(参数);

        // 3. 撤销选择 (回溯的灵魂)
        从 path 中移除该选择;
        标记该选择为未使用;
    }
}

```

### 4. C 语言特有踩坑点 (避坑指南)

在 C 语言中刷回溯题，算法逻辑往往只占一半，另一半难在**内存与指针管理**：

1. **预分配结果集内存**：题目约定数组长度最大为 6，所以全排列最多有 $6! = 720$ 种。直接 `malloc` 申请 720 个指针数组，避免了繁琐的动态扩容。
2. **指针的“双重解引用”**：
* 结果有多少行：题目传入的是 `int* returnSize`，修改时必须写 `*returnSize = 0` 以及 `(*returnSize)++`。
* 每一行有多长：题目传入的是二级指针 `int returnColumnSizes`，它本质是一个一维数组的地址。你需要为它 `malloc` 内存，并通过 `(*returnColumnSizes)[i] = numsSize` 来赋值。


3. **必须深拷贝 `path**`：当触发结束条件时，**绝对不能**直接 `res[*returnSize] = path`。因为 `path` 是一个全程复用的临时数组，后续的回溯会覆盖掉里面的值。必须新申请一块内存，用 `for` 循环挨个复制过去。
4. **清理现场**：使用 `calloc` 初始化 `used` 数组会自动赋 0 (False)，比 `malloc` + `memset` 更简洁。结束时别忘了 `free(path)` 和 `free(used)`。

### 5. 复杂度分析

* **时间复杂度**：$O(N \times N!)$。一共有 $N!$ 个全排列，每次找到一个完整排列后，需要花费 $O(N)$ 的时间将 `path` 复制到结果集中。
* **空间复杂度**：$O(N)$。主要消耗在于递归调用栈的深度（最大为 $N$），以及辅助数组 `path` 和 `used` 的空间。注意，这里通常不将返回给系统的 `res` 结果集计算在额外空间复杂度内。

### 6. 完整实战代码 (力扣 46 题 AC 代码)

这段代码直接对应了上文提到的“通用回溯模板”和“避坑指南”，可以直接在力扣提交并 AC。

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 回溯核心函数
// pathIndex 相当于当前正在填的“格子编号”
void backtrack(int* nums, int numsSize, bool* used, int* path, int pathIndex, int** res, int* returnSize) {
    // 【终止条件】所有格子都填满了
    if (pathIndex == numsSize) {
        // [必坑点] 深拷贝：千万不能直接写 res[*returnSize] = path;
        res[*returnSize] = (int*)malloc(sizeof(int) * numsSize);
        for (int i = 0; i < numsSize; i++) {
            res[*returnSize][i] = path[i];
        }
        (*returnSize)++; // 记录成功找到一个结果
        return;
    }

    // 遍历所有可能的选择（手头所有的数字）
    for (int i = 0; i < numsSize; i++) {
        // 如果该数字在当前这条路径中已经用过了，直接跳过
        if (used[i]) continue;

        // 1. 做选择：填入数字，标记为已使用
        path[pathIndex] = nums[i];
        used[i] = true;

        // 2. 进入下一层：去填下一个格子 (pathIndex + 1)
        backtrack(nums, numsSize, used, path, pathIndex + 1, res, returnSize);

        // 3. 撤销选择：从下一层退回来后，把刚填的数字拿走，标记为未使用
        used[i] = false;
    }
}

// 主调函数，也是力扣要求的接口
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // 1. 计算全排列的最大数量 (N!)，以便一次性分配足够内存
    int maxPermutations = 1;
    for (int i = 1; i <= numsSize; i++) {
        maxPermutations *= i;
    }

    // 2. 分配结果二维数组和列数一维数组的内存
    int** res = (int**)malloc(sizeof(int*) * maxPermutations);
    *returnColumnSizes = (int*)malloc(sizeof(int) * maxPermutations);
    *returnSize = 0; // 初始化行数为 0

    // 3. 初始化回溯用的辅助数组
    int* path = (int*)malloc(sizeof(int) * numsSize);
    bool* used = (bool*)calloc(numsSize, sizeof(bool)); // calloc 自动初始化为 0 (false)

    // 4. 从第 0 个格子开始回溯
    backtrack(nums, numsSize, used, path, 0, res, returnSize);

    // 5. 按照力扣 C 语言接口要求，告知系统每一行的长度
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = numsSize; 
    }

    // 6. 打扫战场，释放内部辅助数组
    free(path);
    free(used);

    // 返回最终收集好的结果集
    return res;
}

```