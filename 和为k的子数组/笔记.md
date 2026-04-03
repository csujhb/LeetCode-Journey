---

# LeetCode 560. 和为 K 的子数组 学习笔记

## 1. 题目描述

给定一个整数数�?`nums` 和一个整�?`k`，请统计并返回该数组�?**和为 `k` 的连续子数组** 的个数�?

**注意�?*

* 子数组必须是 **连续�?*
* 数组中元素可以为正数、负数�?

---

## 2. 题目示例

### 示例 1

```text
输入: nums = [1,1,1], k = 2
输出: 2
```

解释�?

* `[1,1]`（前两个�?
* `[1,1]`（后两个�?

---

### 示例 2

```text
输入: nums = [1,2,3], k = 3
输出: 2
```

解释�?

* `[1,2]`
* `[3]`

---

## 3. 题目本质

这道题的核心是：

> **统计连续子数组的和等�?k 的个�?*

看到“连续子数组的和”，通常优先想到�?

* 前缀�?
* 哈希�?

---

## 4. 暴力解法

## 4.1 思路

枚举所有子数组�?

* 固定左端�?`i`
* 向右不断累加�?`j`
* 如果区间和等�?`k`，答案加一

---

## 4.2 代码（C语言�?

```c
int subarraySum(int* nums, int numsSize, int k) {
    int count = 0;

    for (int i = 0; i < numsSize; i++) {
        int sum = 0;
        for (int j = i; j < numsSize; j++) {
            sum += nums[j];
            if (sum == k) {
                count++;
            }
        }
    }

    return count;
}
```

---

## 4.3 复杂度分�?

* 时间复杂度：`O(n^2)`
* 空间复杂度：`O(1)`

---

## 4.4 优缺�?

### 优点

* 容易理解
* 容易写对

### 缺点

* 数据量大时效率较�?
* 不是最优解

---

## 5. 为什么不能直接用滑动窗口

很多“连续子数组求和”问题会想到滑动窗口，但这题 **不能直接套滑动窗�?*�?

原因是：

> 数组中可能有负数

滑动窗口通常依赖一个性质�?

* 右边扩展，区间和单调增大
* 左边收缩，区间和单调减小

但这题中有负数时�?

* 加一个数，和可能变小
* 去掉一个数，和可能变大

所以窗口不具备单调性，滑动窗口不适用�?

---

## 6. 最优解：前缀�?+ 哈希�?

---

## 6.1 前缀和定�?

定义前缀和：

[
prefix[i] = nums[0] + nums[1] + ... + nums[i]
]

设当前遍历到位置 `i`，当前前缀和为 `sum`�?

如果某一段子数组 `nums[l...i]` 的和等于 `k`，那么有�?

[
sum - prefix[l-1] = k
]

移项得：

[
prefix[l-1] = sum - k
]

这说明：

> 如果之前出现过前缀�?`sum - k`，那么就存在一个以当前位置结尾的子数组，其和为 `k`

---

## 6.2 哈希表记录什�?

哈希表中存：

* `key`：某个前缀�?
* `value`：这个前缀和出现的次数

为什么要记录次数�?

因为同一个前缀和可能出现多次，每出现一次，就对应一种合法子数组�?

---

## 6.3 算法流程

1. 初始化：

   * `sum = 0`
   * `count = 0`
   * 哈希表中先放�?`(0, 1)`

2. 遍历数组中每个元素：

   * 更新当前前缀�?`sum += nums[i]`
   * 查找哈希表中是否存在 `sum - k`
   * 若存在，说明有若干个以前的前缀和可以和当前组成和为 `k` 的子数组
   * 把当前前缀�?`sum` 加入哈希�?

---

## 6.4 为什么一开始要�?`(0,1)`

因为这代表：

> “前面什么都没有时”的前缀和为 0，出现过 1 �?

这样当某一�?**从下�?0 开�?* 的子数组和恰好为 `k` 时，也能被统计到�?

例如�?

```text
nums = [2], k = 2
```

遍历到第一个元素后�?

* `sum = 2`
* 需要找 `sum - k = 0`
* 哈希表中已有 `0:1`
* 所以答案加 1

---

## 7. 最优解代码（C语言�?

下面给出一个较稳妥的链地址法哈希表实现�?

```c
#include <stdlib.h>

#define HASH_SIZE 100003

typedef struct Node {
    long long key;
    int count;
    struct Node* next;
} Node;

static int hash(long long key) {
    long long h = key % HASH_SIZE;
    if (h < 0) h += HASH_SIZE;
    return (int)h;
}

static int findCount(Node** table, long long key) {
    int idx = hash(key);
    Node* cur = table[idx];

    while (cur) {
        if (cur->key == key) {
            return cur->count;
        }
        cur = cur->next;
    }
    return 0;
}

static void insertOrAdd(Node** table, long long key) {
    int idx = hash(key);
    Node* cur = table[idx];

    while (cur) {
        if (cur->key == key) {
            cur->count++;
            return;
        }
        cur = cur->next;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->count = 1;
    node->next = table[idx];
    table[idx] = node;
}

static void freeTable(Node** table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* cur = table[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

int subarraySum(int* nums, int numsSize, int k) {
    Node** table = (Node**)calloc(HASH_SIZE, sizeof(Node*));

    long long prefixSum = 0;
    int ans = 0;

    insertOrAdd(table, 0);

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        ans += findCount(table, prefixSum - k);
        insertOrAdd(table, prefixSum);
    }

    freeTable(table);
    free(table);

    return ans;
}
```

---

## 8. 结合例子理解过程

以：

```text
nums = [1,1,1], k = 2
```

为例�?

### 初始状�?

```text
sum = 0
哈希�?= {0:1}
ans = 0
```

---

### 遍历�?1 个元�?`1`

```text
sum = 1
查找 sum - k = 1 - 2 = -1
不存�?
�?1 加入哈希�?
```

当前�?

```text
哈希�?= {0:1, 1:1}
ans = 0
```

---

### 遍历�?2 个元�?`1`

```text
sum = 2
查找 sum - k = 2 - 2 = 0
存在 1 �?
ans += 1
�?2 加入哈希�?
```

当前�?

```text
哈希�?= {0:1, 1:1, 2:1}
ans = 1
```

---

### 遍历�?3 个元�?`1`

```text
sum = 3
查找 sum - k = 3 - 2 = 1
存在 1 �?
ans += 1
�?3 加入哈希�?
```

最终：

```text
ans = 2
```

---

## 9. 复杂度分�?

### 暴力解法

* 时间复杂度：`O(n^2)`
* 空间复杂度：`O(1)`

### 前缀�?+ 哈希�?

* 时间复杂度：平均 `O(n)`
* 空间复杂度：`O(n)`

---

## 10. 易错点总结

## 10.1 最容易写错的公�?

正确写法是：

```c
target = sum - k;
```

不是�?

```c
target = k - sum;
```

因为我们要找的是�?

[
pre = sum - k
]

而不�?`k - sum`�?

---

## 10.2 哈希表要先插�?`0`

一定要先执行：

```c
insert(0, 1);
```

否则漏掉从下�?`0` 开始的合法子数组�?

---

## 10.3 这题不是“最长子数组”，而是“个数�?

有些前缀和题是求最长长度，这题是求�?

> 一共有多少个连续子数组满足条件

所以哈希表中要记录的是�?

* 出现次数

而不是：

* 最早位�?
* 最晚位�?

---

## 10.4 数组中有负数，不能用普通滑动窗�?

这一点很关键，也是这题和“和为某值的正数子数组”类题目的区别�?

---

## 10.5 前缀和可以考虑�?`long long`

这题数据范围�?`int` 其实够用，但写模板时，前缀和用 `long long` 更稳健�?

---

## 11. 这道题的核心模板

以后看到下面这种题型�?

* 连续子数�?
* 和等于某个�?
* 统计个数
* 数组中可能有负数

优先联想到这个模板：

```c
sum = 0
hash[0] = 1

for each num:
    sum += num
    ans += hash[sum - k]
    hash[sum]++
```

---

## 12. 和相关题目的联系

### 这题和“两数之和”的相似�?

两数之和是：

> `a + b = target`

这题是：

> `当前前缀�?- 之前前缀�?= k`

本质都是�?

> 一边遍历，一边在哈希表里找“目标值�?

---

### 这题和“最长子数组和为 k”类题的区别

* 本题：哈希表存“前缀和出现次数�?
* 最长长度题：哈希表存“前缀和第一次出现的位置�?

---

## 13. 面试/笔试答题模板

如果面试官问你思路，可以这样答�?

> 这题要求连续子数组和�?k 的个数，适合用前缀和处理区间和问题�?
> 设当前前缀和为 sum，如果某个以前的前缀�?pre 满足 sum - pre = k，那么以当前位置结尾的某个子数组和就等于 k，所以需要在之前出现过的前缀和中查找 sum - k�?
> 因此可以用哈希表记录每个前缀和出现的次数，遍历数组时累计当前前缀�?sum，然后把哈希表中 sum - k 的出现次数加到答案里，再把当�?sum 记录进哈希表�?
> 这样时间复杂度可以从 O(n^2) 优化到平�?O(n)�?

---

## 14. 一句话总结

> **连续子数组和�?k 的个�?= 前缀�?+ 哈希表统�?`sum - k` 出现次数**

---

## 15. 适合背下来的结论

### 结论 1

“连续子数组和”问题优先考虑前缀和�?

### 结论 2

“统计个数”时，哈希表通常存“出现次数”�?

### 结论 3

本题查找的是�?

```c
sum - k
```

不是�?

```c
k - sum
```

### 结论 4

初始化必须有�?

```c
hash[0] = 1;
```

---

