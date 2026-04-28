# 📚 算法学习笔记：每日温度 (LeetCode 739)

##  题目核心定义

* **目标**：给定一个整数数组 `temperatures` 表示每天的温度，返回一个数组 `answer`，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。
* **本质**：寻找数组中每个元素 **右侧第一个比它大的元素** 的距离。

---

## 标准解法：单调栈 (Monotonic Stack)



寻找“下一个更大元素”是单调栈的绝对统治区。
* **核心思维**：栈里存放的不是温度值，而是**温度的下标（索引）**！这样我们在出栈时，才能通过下标相减算出“等了几天”。
* **维护单调性**：我们要维护一个**从栈底到栈顶，温度单调递减**的栈。
  * 如果今天比栈顶的那天冷（或一样），说明还没找到栈顶那天想要的升温，今天也乖乖入栈等待。
  * 如果今天比栈顶的那天热，**破案了！** 栈顶的那一天终于等到了升温，当前天的下标减去栈顶下标，就是等待的天数。将栈顶出栈，并继续用今天去挑战新的栈顶，直到今天不再比栈顶热为止。

### C 语言代码实现：

```c
#include <stdlib.h>

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    // 使用 calloc，默认全为 0。这样最后那些没出栈的（找不到更高温度的）天然就是 0，省去后续处理
    int* res = (int*)calloc(temperaturesSize, sizeof(int));
    int* stack = (int*)malloc(temperaturesSize * sizeof(int));
    *returnSize = temperaturesSize;
    int top = -1;

    for (int i = 0; i < temperaturesSize; i++) {
        // 只要栈不为空，且今天比栈顶记录的那一天热，就持续出栈并结算天数
        while (top > -1 && temperatures[i] > temperatures[stack[top]]) {
            res[stack[top]] = i - stack[top];
            top--;
        }
        // 今天入栈，继续等待未来的高温
        stack[++top] = i;
    }
    
    free(stack);
    return res;
}
```

---

##  极限优化解法：向右跳跃法 (DP 思维)

如果面试官要求**空间复杂度必须是 O(1)**（不考虑返回数组），我们可以抛弃栈，利用已经计算好的结果向右“跳跃”。

* **核心思维**：从右向左逆向遍历数组。我们要找第 `i` 天之后的更高温度，先看紧挨着的第 `i+1` 天（记为 `j`）。
  1. 如果 `T[j] > T[i]`，直接得到距离 `j - i`。
  2. 如果 `T[j] <= T[i]`，重点来了：既然 `j` 没我高，那 `j` 后面那些还没 `j` 高的日子肯定也比我矮。我们**直接利用 `res[j]` 跳过这些废柴**，让 `j = j + res[j]`，去和比 `j` 更高的那一天比较！
  3. 如果 `res[j] == 0`，说明右边彻底没有更高的了，结束寻找。

### C 语言代码实现：

```c
#include <stdlib.h>
#include <stdbool.h>

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int* res = (int*)calloc(temperaturesSize, sizeof(int));
    *returnSize = temperaturesSize;
    
    // 从倒数第二天开始，从右向左倒推计算
    for (int i = temperaturesSize - 2; i >= 0; i--) {
        int j = i + 1; // 探测指针，先指向紧挨着的右边一天
        
        while (true) {
            if (temperatures[j] > temperatures[i]) {
                res[i] = j - i; // 找到了最近的高温
                break;
            } else if (res[j] == 0) {
                res[i] = 0; // 右边到头了都没有更高的
                break;
            }
            // 核心优化：j 不是自增，而是借助已知结果直接“跳”到下一个可能的高温天
            j += res[j]; 
        }
    }
    return res;
}
```

---

##  复杂度与解法对比总结

| 特性 | 单调栈法 | 跳跃法 (逆向遍历) |
| :--- | :--- | :--- |
| **时间复杂度** | O(N) | O(N) |
| **空间复杂度** | O(N) (额外开辟了栈空间) | O(1) (仅使用返回结果本身的空间) |
| **代码思路** | 从左向右，把没解决的存起来，等未来解决。 | 从右向左，利用未来的已知结果，加速解决当前问题。 |

**💡 避坑小贴士：**
在写 C 语言算法题时，涉及数组初始化的场景，**优先考虑使用 `calloc` 替代 `malloc`**。不仅能避免野指针/脏数据导致的莫名其妙的报错，还能像这道题一样，巧妙利用默认的 `0` 省去收尾逻辑。