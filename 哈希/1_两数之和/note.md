---

# 哈希冲突-链地址法（拉链法）学习文档（附两数之和实现）

# 一、前言

链地址法（又称拉链法）是解决哈希冲突的主流方案。其核心思路是「哈希表数组 + 链表」结合：将哈希到同一个桶（Bucket）的冲突元素挂载到对应的单链表上。相比线性探测法，它彻底解决了「聚集问题」，效率更稳定。

本文将通过以下四个环节完整讲解链地址法的 C 语言实现，并对比线性探测法：
1. **结构体设计**
2. **辅助函数封装**
3. **核心实现（两数之和）**
4. **测试用例与总结**

---

# 二、核心概念回顾

##  哈希冲突
当两个不同的 `key` 通过哈希函数计算后，得到相同的哈希索引，即为哈希冲突。
* **示例**：哈希函数为 `abs(key) % 10`，则 `key = 2` 和 `key = 12` 均映射到索引 **2**。

##  链地址法核心思想
哈希表的每个位置存储一个链表头指针。所有冲突元素作为链表节点通过头插法或尾插法连接。查找时仅需遍历对应索引的链表。

##  线性探测法核心思想
属于「开放地址法」。冲突时从当前位置开始，按固定步长（通常为 1）向后查找空位。
* **缺点**：易产生「聚集问题」，即连续的哈希位置被占用，导致探测距离过长，效率下降。

---

# 三、线性探测法基础实现

##  结构体设计

```c
#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 20000  // 哈希表容量

// 线性探测法节点
typedef struct {
    int key;        // 存储数组元素值
    int value;      // 存储数组元素下标
    int isused;     // 标记位：1=已占用，0=未占用
} LinearHashNode;

// 初始化全局哈希表
LinearHashNode linear_hash_table[HASH_SIZE] = {0};
```

## 核心逻辑（以两数之和为例）

```c
int linear_hash(int value) {
    return abs(value) % HASH_SIZE;
}

int* linear_twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int *result = (int *)malloc(2 * sizeof(int));
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int idx = linear_hash(complement);
        
        // 线性探测查找补数
        while (linear_hash_table[idx].isused) {
            if (linear_hash_table[idx].key == complement) {
                result[0] = linear_hash_table[idx].value;
                result[1] = i;
                return result;
            }
            idx = (idx + 1) % HASH_SIZE;
        }

        // 补数不存在，插入当前元素
        int temp_idx = linear_hash(nums[i]);
        while (linear_hash_table[temp_idx].isused) {
            temp_idx = (temp_idx + 1) % HASH_SIZE;
        }
        linear_hash_table[temp_idx].isused = 1;
        linear_hash_table[temp_idx].key = nums[i];
        linear_hash_table[temp_idx].value = i;
    }
    free(result);
    return NULL;
}
```

---

# 四、链地址法结构体设计（重点）

链地址法需要定义链表节点以及存储头指针的数组。

```c
#include <stdbool.h>

// 1. 链表节点：存储键值对 + 下一节点指针
typedef struct ListNode {
    int key;                // 哈希键（元素值）
    int value;              // 哈希值（元素下标）
    struct ListNode *next;  // 指向下一个冲突节点
} ListNode;

// 2. 哈希表：数组存储链表头指针
ListNode *hash_table[HASH_SIZE] = {NULL};
```

---

# 五、辅助函数（链表操作封装）

##  创建节点与查找

```c
ListNode* createNode(int key, int value) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (node) {
        node->key = key;
        node->value = value;
        node->next = NULL;
    }
    return node;
}

ListNode* findNode(int key) {
    int idx = abs(key) % HASH_SIZE;
    ListNode *cur = hash_table[idx];
    while (cur) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return NULL;
}
```

## 插入与释放

```c
bool insertNode(int key, int value) {
    int idx = abs(key) % HASH_SIZE;
    if (findNode(key)) return false; // 避免重复插入

    ListNode *newNode = createNode(key, value);
    if (!newNode) return false;

    // 头插法：时间复杂度 O(1)
    newNode->next = hash_table[idx];
    hash_table[idx] = newNode;
    return true;
}

void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        ListNode *cur = hash_table[i];
        while (cur) {
            ListNode *temp = cur;
            cur = cur->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}
```

---

# 六、完整实现：基于链地址法的“两数之和”

```c
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int *result = (int*)malloc(2 * sizeof(int));
    
    // 清空哈希表（重要：防止多次调用污染数据）
    freeHashTable();

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        ListNode *node = findNode(complement);
        
        if (node != NULL) {
            result[0] = node->value;
            result[1] = i;
            return result; // 注意：实际应用中可在此或外部释放哈希表
        }
        insertNode(nums[i], i);
    }
    
    *returnSize = 0;
    free(result);
    return NULL;
}
```

---

# 七、关键要点总结

##  方法对比

| 对比维度 | 线性探测法 | 链地址法 |
| :--- | :--- | :--- |
| **冲突处理** | 开放地址，向后探测空位 | 链表挂载，存入对应桶中 |
| **聚集问题** | 易出现连续聚集，效率随载荷增加下降 | 无聚集问题，效率稳定 |
| **内存效率** | 高（无需指针，仅结构体数组） | 较低（需额外存储指针空间） |
| **平均复杂度** | $O(1)$（冲突多时退化） | $O(1)$（链表过长时退化） |
| **适用场景** | 数据量小、内存紧张 | 通用场景（工业界首选） |

##  新手注意事项

1.  **内存管理**：所有使用 `malloc` 分配的节点在程序结束或函数退出前必须 `free`，否则会导致内存泄漏。
2.  **头插法效率**：插入节点时推荐使用头插法，复杂度为 $O(1)$；尾插法需遍历链表，复杂度为 $O(n)$。
3.  **负数处理**：计算哈希索引时必须对 `key` 取绝对值 `abs()`，防止数组下标越界导致崩溃。
4.  **哈希容量**：`HASH_SIZE` 应根据数据量合理选择，通常选择质数或较大的常数以减少冲突。

---
