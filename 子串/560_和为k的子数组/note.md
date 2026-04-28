# LeetCode 560. 和为 K 的子数组 学习笔记

---

## 题目描述

给定一个整数数组 `nums` 和一个整数 `k`，请统计并返回该数组中 **和为 `k` 的连续子数组** 的个数。

**注意：**
* 子数组必须是 **连续的**
* 数组中元素可以为正数、负数

---

## 题目示例

### 示例 1
```text
输入: nums = [1,1,1], k = 2
输出: 2
```
解释：`[1,1]`（前两个）和 `[1,1]`（后两个）。

### 示例 2
```text
输入: nums = [1,2,3], k = 3
输出: 2
```
解释：`[1,2]` 和 `[3]`。

---

## 题目本质

这道题的核心是：**统计连续子数组的和等于 k 的个数。**
看到“连续子数组的和”，通常优先想到：
* 前缀和
* 哈希表

---

## 暴力解法

### 思路
枚举所有子数组：
* 固定左端点 `i`
* 向右不断累加到 `j`
* 如果区间和等于 `k`，答案加一

### 代码（C语言）
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

### 复杂度分析
* 时间复杂度：$O(n^2)$
* 空间复杂度：$O(1)$

---

## 为什么不能直接用滑动窗口

这题 **不能直接套用滑动窗口**，原因是：**数组中可能有负数。**

滑动窗口通常依赖单调性：
* 右边扩展，区间和单调增大
* 左边收缩，区间和单调减小

但在有负数的情况下，加一个数和可能变小，去掉一个数和可能变大，窗口不具备单调性。

---

## 最优解：前缀和 + 哈希表

### 前缀和定义


定义前缀和：
$$prefix[i] = nums[0] + nums[1] + \dots + nums[i]$$

设当前遍历到位置 `i`，当前前缀和为 `sum`。如果某一段子数组 `nums[l...i]` 的和等于 `k`，则有：
$$sum - prefix[l-1] = k \implies prefix[l-1] = sum - k$$

这说明：**如果之前出现过前缀和 `sum - k`，那么就存在一个以当前位置结尾的子数组，其和为 `k`。**

### 哈希表记录内容


哈希表中存储：
* **key**：某个前缀和
* **value**：该前缀和出现的次数

同一个前缀和可能出现多次，每出现一次，就对应一种合法的子数组。

---

## 算法流程

1. **初始化**：`sum = 0`, `count = 0`，哈希表中先放入 `(0, 1)`。
2. **遍历数组**：
   * 更新当前前缀和：`sum += nums[i]`
   * 查找哈希表中是否存在 `sum - k`
   * 若存在，将该次数累加到结果中
   * 将当前前缀和 `sum` 存入或更新进哈希表

---

## 为什么一开始要存 (0,1)

这代表“前面什么都没有时”的前缀和为 0，且出现过 1 次。这样当某个 **从下标 0 开始** 的子数组和恰好为 `k` 时（此时 `sum - k = 0`），也能被正确统计。

---

## 最优解代码（C语言）

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
        if (cur->key == key) return cur->count;
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

    insertOrAdd(table, 0); // 重要初始化

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

## 易错点总结

* **公式错误**：正确应为查找 `sum - k`，而不是 `k - sum`。
* **忘记初始化 (0,1)**：漏掉此步会导致无法统计从第一个元素开始的合法子数组。
* **统计内容**：本题求的是 **个数**，因此哈希表存的是“出现次数”，而不是“第一次出现的位置”。
* **数据类型**：虽然 `int` 在本题范围通常足够，但在处理前缀和时使用 `long long` 更稳健。

---

## 面试/笔试答题模板

> 这题要求连续子数组和为 `k` 的个数，由于数组包含负数，滑动窗口不适用，适合用前缀和结合哈希表处理。
> 我们维护一个当前前缀和 `sum`。如果之前存在一个前缀和 `pre` 满足 `sum - pre = k`，则找到一个目标子数组。因此我们需要在哈希表中查找 `sum - k` 出现的次数。
> 遍历过程中，我们实时更新 `sum`，先在哈希表中查找并累加 `sum - k` 的次数，再将当前 `sum` 存入哈希表。通过这种方式，时间复杂度可以从 $O(n^2)$ 优化到平均 $O(n)$。

---

## 一句话总结

**连续子数组和为 k 的个数 = 前缀和 + 哈希表统计 `sum - k` 出现次数。**