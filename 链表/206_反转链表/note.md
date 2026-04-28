# LeetCode 206. 反转链表 学习笔记

---

## 题目描述

给你单链表的头节点 `head`，请你反转链表，并返回反转后的链表头节点。

---

## 示例

### 示例 1

```text
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```

原链表：
`1 -> 2 -> 3 -> 4 -> 5 -> NULL`

反转后：
`5 -> 4 -> 3 -> 2 -> 1 -> NULL`

---

### 示例 2

```text
输入：head = [1,2]
输出：[2,1]
```

---

### 示例 3

```text
输入：head = []
输出：[]
```

---

## 题目本质

这题本质上是在做一件事：把链表中每个节点的 `next` 指针方向全部反过来。

例如原来是：
`1 -> 2 -> 3 -> NULL`

反转后要变成：
`3 -> 2 -> 1 -> NULL`


**难点不在“值”，而在于：**
单链表只能顺着 `next` 往后走，一旦你改了某个 `next`，原来的后继节点就可能找不到。

所以关键就是：**改指针之前，先把后继保存下来。**

---

## 常见做法

这题最经典的有两种方法：
1.  **迭代法**
2.  **递归法**

---

## 方法一：迭代法

### 思路

用三个指针：
* `prev`：当前节点反转后要指向的前一个节点。
* `cur`：当前正在处理的节点。
* `next`：提前保存 `cur->next`，防止链断掉。


每轮循环做三件事：
1.  先保存 `cur->next`。
2.  令 `cur->next = prev`。
3.  再整体向后推进。

### 代码

```c
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* cur = head;

    while (cur != NULL) {
        struct ListNode* next = cur->next; // 先保存后继
        cur->next = prev;                  // 反转指针
        prev = cur;                        // prev 前进
        cur = next;                        // cur 前进
    }

    return prev;
}
```

### 执行过程示例

以 `1 -> 2 -> 3 -> NULL` 为例：

#### 初始状态
* `prev = NULL`
* `cur = 1`
* 链表：`1 -> 2 -> 3 -> NULL`

#### 第一次循环
1.  保存：`next = 2`
2.  反转：`1 -> NULL`
3.  移动：`prev = 1`, `cur = 2`
* 当前状态：
    * 已反转部分：`1 -> NULL`
    * 未处理部分：`2 -> 3 -> NULL`

#### 第二次循环
1.  保存：`next = 3`
2.  反转：`2 -> 1 -> NULL`
3.  移动：`prev = 2`, `cur = 3`
* 当前状态：
    * 已反转部分：`2 -> 1 -> NULL`
    * 未处理部分：`3 -> NULL`

#### 第三次循环
1.  保存：`next = NULL`
2.  反转：`3 -> 2 -> 1 -> NULL`
3.  移动：`prev = 3`, `cur = NULL`

循环结束，返回 `prev`。

### 复杂度分析

* 时间复杂度：`O(n)`
* 空间复杂度：`O(1)`

### 优缺点

* **优点**：代码高效，空间复杂度最低，面试中最常用。
* **缺点**：需要自己维护多个指针，对初学者来说容易绕。

---

## 方法二：递归法

### 思路

递归法的核心思想是：**先把后面的链表反转好，再把当前节点接到最后。**


例如：`1 -> 2 -> 3 -> 4 -> NULL`
假设递归已经把 `2 -> 3 -> 4 -> NULL` 反转成 `4 -> 3 -> 2 -> NULL`，那么现在只需要再把 `1` 接到 `2` 后面即可。

### 代码

```c
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    // 递归出口
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* newHead = reverseList(head->next);

    head->next->next = head; // 让后继节点指向自己
    head->next = NULL;      // 打断原有指向

    return newHead;
}
```

### 为什么这两句是关键？

```c
head->next->next = head;
head->next = NULL;
```

假设当前 `head = 1`，并且递归已经把后面变成 `3 -> 2`，而原本还有 `1 -> 2`：
1.  `head->next->next = head;` 就是说 `2->next = 1;`，把指针反过来。
2.  `head->next = NULL;` 令 `1` 变成尾节点，否则会形成环。

### 执行过程示例

以 `1 -> 2 -> 3 -> NULL` 为例：

#### 调用栈
1.  `reverseList(1)`：递归调用 `reverseList(2)`。
2.  `reverseList(2)`：递归调用 `reverseList(3)`。
3.  `reverseList(3)`：因为 `3->next == NULL`，命中递归出口，直接返回 `3`。

#### 开始回溯
* **回到节点 2**：执行 `2->next->next = 2;` (即 `3->next = 2`)，`2->next = NULL;`。链表变为 `3 -> 2 -> NULL`。
* **回到节点 1**：执行 `1->next->next = 1;` (即 `2->next = 1`)，`1->next = NULL;`。链表变为 `3 -> 2 -> 1 -> NULL`。

最后返回新头节点 `3`。

### 复杂度分析

* 时间复杂度：`O(n)`
* 空间复杂度：`O(n)`（递归消耗调用栈空间）。

### 优缺点

* **优点**：代码简洁，思路优美，逻辑清晰。
* **缺点**：有递归栈开销，链表过长时可能导致溢出。

---

## 两种方法对比

| 方法 | 时间复杂度 | 空间复杂度 | 特点 |
| :--- | :--- | :--- | :--- |
| 迭代法 | `O(n)` | `O(1)` | 最常用，空间最省 |
| 递归法 | `O(n)` | `O(n)` | 写法优美，但有栈开销 |

---

## 为什么迭代法更推荐？

因为迭代法已经能做到时间 `O(n)` 和空间 `O(1)` 的最优解。在实际刷题和面试中，一般优先写迭代法。递归法更多是为了展示深度理解、训练递归思维。

---

## 你的代码分析

你写的是标准的 **迭代法**：

```c
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* cur = head;
    while (cur) {
        struct ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}
```

**优点：** 逻辑完整，写法标准，没有多余步骤，非常适合作为模板记忆。

---

## 易错点总结

* **改指针前一定要先保存 `next`**：如果直接写 `cur->next = prev; cur = cur->next;`，后继节点就丢了。
* **最后返回的是 `prev` 而不是 `head`**：循环结束后 `cur` 是 `NULL`，`prev` 才是新的头。
* **递归法中别忘了 `head->next = NULL`**：否则链表会形成环。
* **处理特殊情况**：空链表（`head == NULL`）和单节点链表（`head->next == NULL`）都要能正常运行。

---

## 模板总结

### 迭代模板

```c
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* cur = head;
    while (cur != NULL) {
        struct ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}
```

### 递归模板

```c
struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
```

---

## 面试答题模板

> “反转链表可以用迭代和递归实现。迭代法通过 `prev`、`cur`、`next` 三个指针，在遍历时先存后继，再改指向，最后整体推进。这种方法时间 $O(n)$，空间 $O(1)$，最为高效。
> 递归法则是先反转后面的部分，再处理当前节点的指向。时间同样 $O(n)$，但由于递归栈，空间复杂度为 $O(n)$。”

---

## 一句话总结

**反转链表的核心就是：改当前节点指针前，先保存后继节点。**