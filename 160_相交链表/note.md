---

# 力扣 160. 相交链表 —— C 语言学习笔记

## 题目描述

给你两个单链表的头节点 `headA` 和 `headB`，请找出并返回两个单链表相交的起始节点。 如果两个链表不存在相交节点，返回 `NULL`。

题目保证整个链式结构中 **不存在环**，并且函数返回结果后，**链表必须保持原始结构**。

---

## 题目本质

这道题的关键点不是“值相等”，而是：判断两个链表是否在某个节点处开始 **共用同一段后续链表**。

也就是说，判断相交时比较的是 **节点地址是否相同**，而不是节点值是否相等。


---

## 容易误解的地方

### 相交不是“值相同”
* **错误理解**：`nodeA->val == nodeB->val` 就认为相交。
* **正确理解**：`nodeA == nodeB` 才表示相交。

### 返回的是“节点指针”，不是节点值
函数返回类型是 `struct ListNode*`，所以返回的是相交起点的 **地址**。

---

## 解题思路总览

这题常见有三种思路：
1.  **暴力法**
2.  **哈希表法**
3.  **双指针法 / 长度对齐法**（最推荐）

---

## 方法：暴力法

### 思路
遍历链表 A 的每一个节点，对每个节点再去链表 B 中找是否存在同一个节点地址。
* 时间复杂度：$O(m \times n)$
* 空间复杂度：$O(1)$

### C 代码
```c
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    struct ListNode* pA = headA;
    while (pA != NULL) {
        struct ListNode* pB = headB;
        while (pB != NULL) {
            if (pA == pB) {
                return pA;
            }
            pB = pB->next;
        }
        pA = pA->next;
    }
    return NULL;
}
```

---

## 方法：哈希表法

### 思路
先把链表 A 的所有节点地址存进哈希表，再遍历链表 B。如果当前 B 的节点地址已经在哈希表里，说明找到交点。
* 时间复杂度：$O(m + n)$
* 空间复杂度：$O(m)$

---

## 方法：长度对齐法

这是你原来思路的标准化版本，也是非常优秀的解法。


### 核心思想
如果两个链表相交，那么从交点到链表末尾的长度一定相同。
1.  分别求出链表 A、B 的长度。
2.  让更长的链表先走几步（步数为长度差）。
3.  这样两个指针就“站在了离尾部同样远的位置”。
4.  然后两个指针一起走，第一次相等的位置就是交点。

### C 代码
```c
int getLength(struct ListNode* head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    int lenA = getLength(headA);
    int lenB = getLength(headB);

    struct ListNode* pA = headA;
    struct ListNode* pB = headB;

    if (lenA > lenB) {
        int diff = lenA - lenB;
        while (diff--) pA = pA->next;
    } else {
        int diff = lenB - lenA;
        while (diff--) pB = pB->next;
    }

    while (pA != pB) {
        pA = pA->next;
        pB = pB->next;
    }
    return pA;
}
```

---

## 方法：双指针换头法

这是本题最经典、面试中最受欢迎的写法。


### 核心思想
定义两个指针：`pA` 从 `headA` 出发，`pB` 从 `headB` 出发。
每次走一步：
* `pA` 为空时，改去走 `headB`。
* `pB` 为空时，改去走 `headA`。

### 为什么成功？
设 A 长度为 $a+c$，B 长度为 $b+c$（$c$ 为公共部分）。`pA` 走的路径是 $A+B$（长 $a+c+b$），`pB` 走的路径是 $B+A$（长 $b+c+a$）。总路程一样，所以有交点必相遇，无交点必同时指向 `NULL`。

### C 代码
```c
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    struct ListNode* pA = headA;
    struct ListNode* pB = headB;

    while (pA != pB) {
        pA = (pA == NULL) ? headB : pA->next;
        pB = (pB == NULL) ? headA : pB->next;
    }
    return pA;
}
```

---

## 你的原算法分析

你原来的算法本质上就是 **长度差对齐法**。只是写法上是通过两个指针先同步走、再根据剩余路程补差额。复杂度同样是 $O(m+n)$ 时间和 $O(1)$ 空间，性能已经是最优级别。

---

## 易错点总结

* **比较的是地址**：不要写成 `pA->val == pB->val`。
* **不相交返回 NULL**：代码必须能自然处理不相交的情况。
* **保持原链表结构**：不能修改 `next` 或断开链表。
* **本地测试**：必须完整定义 `struct ListNode` 结构体，否则编译器会报错“指向不完整类型”。

---

## 面试回答模板

> “这题判断相交不能看节点值，而要看节点地址是否相同。
> 我会考虑 $O(m+n)$ 时间、$O(1)$ 空间的空间解法。
> 一种方法是 **长度对齐法**：先求长度差并让长链表先走，再同步前进寻找交点。
> 另一种更经典的写法是 **双指针换头法**：让两个指针分别遍历 $A+B$ 和 $B+A$ 的路径。如果有交点，它们会在第二轮遍历时相遇；如果没有，则最终会同时指向 `NULL`。”

---

## 一句话总结

**相交链表看地址不看值；要么先求长度差对齐，要么双指针交换头节点走全长。**