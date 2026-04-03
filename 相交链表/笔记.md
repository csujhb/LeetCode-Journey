# LeetCode 160. 相交链表 —�?C 语言学习笔记

## 1. 题目描述

给你两个单链表的头节�?`headA` �?`headB` ，请找出并返回两个单链表相交的起始节点�? 
如果两个链表不存在相交节点，返回 `NULL`�?

题目保证整个链式结构�?**不存在环**，并且函数返回结果后�?*链表必须保持原始结构**�?

---

## 2. 题目本质

这道题的关键点不是“值相等”，而是�?

> 判断两个链表是否在某个节点处开�?**共用同一段后续链�?*

也就是说，判断相交时比较的是�?

```c
节点地址是否相同
````

而不是：

```c
节点值是否相�?
```

### 例子

假设�?

```text
A: a1 -> a2 \
             c1 -> c2 -> c3
B: b1 -> b2 -> b3 /
```

这里两个链表�?`c1` 开始相交，因为�?`c1` 开始，后面的节点是同一批节点�?

---

## 3. 容易误解的地�?

### 3.1 相交不是“值相同�?

错误理解�?

* `nodeA->val == nodeB->val` 就认为相�?

正确理解�?

* `nodeA == nodeB` 才表示相�?

---

### 3.2 返回的是“节点指针”，不是节点�?

函数返回类型一般是�?

```c
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB)
```

所以返回的是相交起点的 **地址**�?

---

## 4. 解题思路总览

这题常见有三种思路�?

1. **暴力�?*
2. **哈希表法**
3. **双指针法 / 长度对齐�?*

其中最推荐的是�?

* 面试经典写法�?*双指针换头法**
* 便于理解和稳定实现：**长度对齐�?*

---

# 5. 方法一：暴力法

## 5.1 思路

遍历链表 A 的每一个节点，对每个节点再去链�?B 中找是否存在同一个节点地址�?

也就是：

* A 的第 1 个节点和 B 所有节点比�?
* A 的第 2 个节点和 B 所有节点比�?
* ...
* 直到找到相同地址的节�?

---

## 5.2 C 代码

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

## 5.3 复杂度分�?

* 时间复杂度：`O(m * n)`
* 空间复杂度：`O(1)`

其中�?

* `m` 是链�?A 长度
* `n` 是链�?B 长度

---

## 5.4 优缺�?

### 优点

* 思路最直接
* 很容易写出来

### 缺点

* 太慢
* 数据规模大时性能�?

---

# 6. 方法二：哈希表法

## 6.1 思路

先把链表 A 的所有节点地址存进哈希表，再遍历链�?B�?

* 如果当前 B 的节点地址已经在哈希表里，说明找到交点
* 如果遍历结束都没找到，说明不相交

---

## 6.2 伪代码思路

```text
遍历 A，所有节点地址存入哈希�?
遍历 B，检查当前节点地址是否在哈希表�?
在：返回该节�?
不在：继�?
都没有：返回 NULL
```

---

## 6.3 复杂度分�?

* 时间复杂度：`O(m + n)`
* 空间复杂度：`O(m)`

---

## 6.4 优缺�?

### 优点

* 时间�?
* 容易理解

### 缺点

* 需要额外空�?
* 这题有更好的 `O(1)` 空间做法

---

# 7. 方法三：长度对齐�?

这是你原来思路的标准化版本，也是非常优秀的解法�?

## 7.1 核心思想

如果两个链表相交，那么从交点到链表末尾的长度一定相同�?

所以我们可以：

1. 分别求出链表 A、B 的长�?
2. 让更长的链表先走几步
3. 这样两个指针就“站在了离尾部同样远的位置�?
4. 然后两个指针一起走
5. 第一次相等的位置就是交点

---

## 7.2 为什么这样能�?

设：

* 链表 A 总长�?= `a + c`
* 链表 B 总长�?= `b + c`
* 其中 `c` 是公共尾部长�?

那么�?

* 只要让长链表先走 `|a - b|` �?
* 两个指针就都距离交点还有相同的步�?

之后同步前进�?

* 如果有交点，就会在交点相�?
* 如果没有交点，就会一起走�?`NULL`

---

## 7.3 C 代码

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
        while (diff--) {
            pA = pA->next;
        }
    } else {
        int diff = lenB - lenA;
        while (diff--) {
            pB = pB->next;
        }
    }

    while (pA != pB) {
        pA = pA->next;
        pB = pB->next;
    }

    return pA;
}
```

---

## 7.4 复杂度分�?

* 时间复杂度：`O(m + n)`
* 空间复杂度：`O(1)`

---

## 7.5 特点

### 优点

* 思路非常清晰
* 容易自己推出�?
* 指针移动过程规整
* 性能已经是最优级�?

### 缺点

* 代码稍微比换头法长一�?
* 需要先写一个求长度函数

---

# 8. 方法四：双指针换头法

这是这题最经典、最常见的写法�?

## 8.1 核心思想

定义两个指针�?

* `pA` �?`headA` 出发
* `pB` �?`headB` 出发

每次走一步：

* `pA` 为空时，改去�?`headB`
* `pB` 为空时，改去�?`headA`

最终：

* 如果有交点，两者会在交点相�?
* 如果没有交点，两者会同时�?`NULL`

---

## 8.2 C 代码

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

## 8.3 为什么成�?

设：

* A 长度�?`a + c`
* B 长度�?`b + c`

则：

* `pA` 走过的路径是：A + B，总长�?`a + c + b`
* `pB` 走过的路径是：B + A，总长�?`b + c + a`

两者总路程一样�?

所以：

* 有交点时，它们会在交点相�?
* 无交点时，它们会同时走到 `NULL`

---

## 8.4 复杂度分�?

* 时间复杂度：`O(m + n)`
* 空间复杂度：`O(1)`

---

## 8.5 特点

### 优点

* 代码非常�?
* 很经�?
* 面试中很受欢�?

### 缺点

* 初学者第一次看不一定立刻能理解
* 在力扣单次提交中，不一定比长度对齐法显示更�?
* 常数项有时会略大一�?

---

# 9. 你的原算法属于哪一�?

你原来的代码本质上就是：

```text
长度差对齐法
```

只是写法不是“先分别求长度”，而是�?

* 先两个指针一起走
* 看谁先到 `NULL`
* 再让长链表补走差�?
* 最后两个指针对齐后一起走

这类思路本身没有问题，复杂度也是最优的�?

* 时间复杂度：`O(m + n)`
* 空间复杂度：`O(1)`

所以你的算法并不差，只是可以写得更清晰一些�?

---

# 10. 为什么“更经典的换头法”不一定提交时间更�?

这一点很重要�?

虽然换头法很经典，但�?LeetCode 上：

* 你的长度对齐法和换头法都�?`O(m + n)`
* 单次运行时间受服务器波动影响很大
* 换头法不一定比长度对齐法更�?
* 有时候长度对齐法的常数项更小，提交结果反而更好看

所以：

> 经典 �?单次提交更快
> 优雅 �?实测毫秒数更�?

---

# 11. 两种最优解对比

| 方法     | 思路               | 时间复杂�? | 空间复杂�?| 特点      |
| ------ | ---------------- | ------ | ----- | ------- |
| 长度对齐�? | 先求长度，再对齐，再同步�?   | O(m+n) | O(1)  | 更容易理�?  |
| 双指针换头法 | 两个指针走完 A+B / B+A | O(m+n) | O(1)  | 更经典、更简�?|

---

# 12. 易错点总结

## 易错�?1：比较的是节点地址，不是�?

错误写法�?

```c
if (pA->val == pB->val)
```

正确写法�?

```c
if (pA == pB)
```

---

## 易错�?2：链表不相交时要返回 `NULL`

不要默认一定会相交�?

---

## 易错�?3：不要修改原链表结构

这题明确要求�?

* 函数结束后链表结构保持原�?

所以不能：

* �?`next`
* 拼接链表
* 断开链表

---

## 易错�?4：本地测试时结构体要完整定义

如果你在本地编译，必须先写：

```c
struct ListNode {
    int val;
    struct ListNode *next;
};
```

否则会出现：

```text
不允许使用指向不完整类型 "struct ListNode" 的指针或引用
```

因为编译器不知道 `next` 成员是什么�?

---

## 易错�?5：空链表情况

例如�?

* `headA == NULL`
* `headB == NULL`

这些情况代码也要能正确处理�?

上述两种最优解都可以自然处理这种情况�?

---

# 13. 推荐背诵版本

## 版本一：更适合自己理解

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

## 版本二：更适合面试背诵

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

# 14. 面试回答模板

可以这样说：

> 这题判断相交不能看节点值，而要看节点地址是否相同�?
> 我会优先考虑 `O(m+n)`、`O(1)` 空间的解法�?
> 一种方法是先分别计算两个链表长度，让长链表先走若干步，再同步前进，第一次相等的位置就是交点�?
> 另一种更经典的方法是双指针换头，让两个指针分别走�?A+B �?B+A，总路程相同，所以如果有交点就会在那里相遇，没有交点则最终同时为 NULL�?

---

# 15. 本题知识点总结

这题重点掌握�?

* 链表相交判断看“地址”，不是“值�?
* 双指针技�?
* 链表长度对齐思想
* 空间复杂度优化到 `O(1)`

---

# 16. 同类题目延伸

学完这题后，可以继续练：

1. **环形链表**

   * 快慢指针经典�?

2. **环形链表 II**

   * 找环入口

3. **链表中倒数�?k 个节�?*

   * 双指针间隔技�?

4. **删除链表倒数�?N 个节�?*

   * 双指针常见应�?

---

# 17. 最终总结

## 最优复杂度

这题最优可以做到：

* 时间复杂度：`O(m + n)`
* 空间复杂度：`O(1)`

---

## 最推荐掌握的两种写�?

### 长度对齐�?

* 更容易理�?
* 更适合自己推导

### 双指针换头法

* 更经�?
* 更适合面试表达

---

## 一句话记忆

> 相交链表看地址，不看值；
> 要么先对齐长度，要么双指针换头�?

---
