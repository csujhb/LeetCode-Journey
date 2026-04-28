# 📚 学习笔记：排序链表 (LeetCode 148)

## 核心避坑：为什么不能只交换 `val`？

在面试中，绝对不能通过“把节点的值提出来排序，再赋回去”或“冒泡交换相邻的 `val`”来解题：
* **失去链表意义**：链表设计的初衷就是为了通过修改指针实现高效操作。
* **时间复杂度爆炸**：直接在链表上做冒泡/插入排序，时间复杂度为 $O(N^2)$，无法满足题目进阶要求的 $O(N \log N)$。

---

## 核心算法：归并排序 (Merge Sort)

要在链表上实现 $O(N \log N)$ 的时间复杂度，**归并排序是唯一的解法**。归并排序分为两步：


* **分 (Divide)**：把长链表从中间切断，一直切到每个链表只有 1 个节点。
* **治 (Conquer)**：把切碎的有序小链表，两两合并成有序的长链表。

---

## 解法一：自顶向下递归法（面试首选标准答案）

**时间复杂度**：$O(N \log N)$
**空间复杂度**：$O(\log N)$ （因为递归会产生深度为 $\log N$ 层的系统调用栈）

### 💡 核心逻辑
* 用**快慢指针**找到中点并切断（`fast` 走两步，`slow` 走一步）。
* 递归调用 `sortList` 排好左半边和右半边。
* 调用“合并两个有序链表”的基础函数进行缝合。


### 💻 模块化代码模板
```c
// 合并两个有序链表
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) { tail->next = l1; l1 = l1->next; } 
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// 找中点
struct ListNode* getMid(struct ListNode* head) {
    if (!head || !head->next) return head;
    struct ListNode *slow = head, *fast = head->next; // fast先走一步，确保偶数时slow在左半部
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 递归主控
struct ListNode* sortList(struct ListNode* head) {
    if (!head || !head->next) return head;
    
    struct ListNode* mid = getMid(head);
    struct ListNode* rightHead = mid->next;
    mid->next = NULL; // 拔刀断表
    
    struct ListNode* left = sortList(head);
    struct ListNode* right = sortList(rightHead);
    return mergeTwoLists(left, right);
}
```

---

## 解法二：自底向上迭代法（真正的工业级 $O(1)$ 空间）

**时间复杂度**：$O(N \log N)$
**空间复杂度**：$O(1)$ （完全抛弃递归，没有任何系统调用栈的额外开销）

### 💡 核心逻辑
把链表看作一堆长度为 1 的碎片，按步长（`step = 1, 2, 4, 8...`）强行进行配对合并。
* **切断函数 (split)**：数出 `step` 个节点，切一刀，返回后面的部分。
* **合并函数 (merge)**：合并两段，并返回合并后的**尾节点**，方便接下一组。
* **步长翻倍**：外层循环控制步长，内层循环遍历整个链表进行切割和合并。

### 💻 核心操作流代码片段
```c
// 在 step 翻倍的 for 循环中：
for (int step = 1; step < length; step *= 2) {
    struct ListNode* prev = &dummy;
    struct ListNode* cur = dummy.next;
    
    while (cur != NULL) {
        struct ListNode* left = cur;
        struct ListNode* right = split(left, step); // 切下左半段
        cur = split(right, step);                   // 切下右半段，cur 指向剩下的
        
        prev = merge(left, right, prev);            // 合并并接到 prev 后面
    }
}
```

---

## 🎓 面试通关建议

* **先写递归**：面试时，如果不加特殊说明，首选自顶向下的**递归法**。它模块清晰，极其不容易出错。
* **讲透复杂度**：当面试官问到空间复杂度时，清晰地画出递归树，告诉他：“因为二分切断导致最大递归深度为 $\log N$，所以空间复杂度为 $O(\log N)$。” 这一句话就能证明你不是死记硬背的代码机器。
* **亮出底牌**：如果面试官追问能否做到真正的 $O(1)$，你再把“自底向上的迭代归并”思路（按步长 1, 2, 4 截断合并）讲出来。这会给你带来极大的加分。