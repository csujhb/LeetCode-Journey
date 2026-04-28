------

# 力扣 76. 最小覆盖子串 学习笔记

## 题目描述

给定两个字符串 `s` 和 `t`，返回 `s` 中的 **最短子串**，使得该子串包含 `t` 中的所有字符。

要求注意两点：

- 子串必须是 **连续的**。
- `t` 中如果某个字符出现了多次，那么窗口中也必须至少出现相同次数。

如果不存在这样的子串，返回空字符串 `""`。

------

## 示例

**输入：** `s = "ADOBECODEBANC"`, `t = "ABC"`

**输出：** `"BANC"`

**解释：** `"BANC"` 是包含 `A`、`B`、`C` 的最短子串。

------

## 题目本质

这题本质上是在字符串 `s` 中，找一个 **最短的连续区间**，使它能够“覆盖”字符串 `t` 的所有字符需求。这里的“覆盖”不仅看字符是否出现过，还要看 **数量是否足够**。

------

## 为什么用滑动窗口

这题满足滑动窗口的典型特征：

- 求的是 **连续子串**。
- 想找的是 **最短满足条件的区间**。
- 可以通过移动左右边界来维护一个候选窗口。

核心方法：**滑动窗口 + 计数数组 / 哈希表**。

------

## 核心思路：两个计数数组

定义两个数组：

- `need[c]`：字符 `c` 在 `t` 中需要多少个。
- `window[c]`：字符 `c` 在当前窗口中有多少个。

------

## 双指针维护窗口

使用 `left`（左边界）和 `right`（右边界）表示窗口 `[left, right]`：

1. 右指针不断右移，扩大窗口。
2. 当窗口已经满足条件时，尝试移动左指针缩小窗口。
3. 在缩小过程中更新最短答案。

------

## 如何判断窗口是否满足条件

**更高效的方法：维护 `formed` 和 `required`**

- `required`：`t` 中有多少种不同字符需要满足。
- `formed`：当前窗口中，已经满足要求的字符种类数。

当某个字符 `c` 满足 `window[c] == need[c]` 时，说明该字符种类达标，`formed++`。当 `formed == required` 时，说明当前窗口已完全覆盖 `t`。

------

## 标准算法流程

1. 统计 `t` 中每个字符的需求频次填入 `need`。
2. 初始化滑动窗口为空。
3. 移动 `right` 扩大窗口，将新字符加入 `window`。
4. 如果某个字符频次达到要求，更新 `formed`。
5. 当 `formed == required` 时：
   - 更新最短答案。
   - 移动 `left` 缩小窗口。
   - 如果缩小后某个必要字符数量不足，则 `formed--`。
6. 重复直到遍历结束。

------

## C 语言代码实现

C

```
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char* minWindow(char* s, char* t) {
    int lenS = strlen(s);
    int lenT = strlen(t);

    if (lenS == 0 || lenT == 0 || lenS < lenT) {
        char* ans = (char*)malloc(1);
        ans[0] = '\0';
        return ans;
    }

    int need[128] = {0};
    int window[128] = {0};

    int required = 0;
    for (int i = 0; i < lenT; i++) {
        if (need[(unsigned char)t[i]] == 0) {
            required++;
        }
        need[(unsigned char)t[i]]++;
    }

    int formed = 0;
    int left = 0;
    int minLen = INT_MAX;
    int start = 0;

    for (int right = 0; right < lenS; right++) {
        unsigned char c = (unsigned char)s[right];
        window[c]++;

        if (need[c] > 0 && window[c] == need[c]) {
            formed++;
        }

        while (left <= right && formed == required) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                start = left;
            }

            unsigned char d = (unsigned char)s[left];
            window[d]--;

            if (need[d] > 0 && window[d] < need[d]) {
                formed--;
            }

            left++;
        }
    }

    if (minLen == INT_MAX) {
        char* ans = (char*)malloc(1);
        ans[0] = '\0';
        return ans;
    }

    char* ans = (char*)malloc(minLen + 1);
    strncpy(ans, s + start, minLen);
    ans[minLen] = '\0';
    return ans;
}
```

------

## 复杂度分析

- **时间复杂度：** $O(|s| + |t|)$。`left` 和 `right` 指针均只向右移动，整体呈线性。
- **空间复杂度：** $O(1)$。使用固定大小的 ASCII 计数数组。

------

## 易错点总结

- **重复字符必须按数量满足**：不能只看字符是否出现过。
- **`formed` 统计种类数**：只有 `window[c] == need[c]` 时，该种类才算满足。
- **更新答案的时机**：进入收缩循环后，先更新答案，再删除左边字符。
- **避免反复调用 `strlen`**：应提前保存长度，防止循环中 $O(n)$ 复杂度的重复计算。

------

## 面试答题表述模板

> “这题要求在 `s` 中找到包含 `t` 所有字符及频次的最短子串，适合使用滑动窗口。
>
> 我们用 `need` 数组统计需求，`window` 数组记录当前窗口频次。
>
> 右指针扩张直到窗口满足条件（通过 `formed == required` 判断），随后左指针收缩以寻找最短长度。
>
> 由于每个字符仅被访问两次，时间复杂度为 $O(m+n)$。”

------

## 一句话总结

**最小覆盖子串 = 滑动窗口 + 字符频次统计 + 窗口合法后不断收缩左边界。**
