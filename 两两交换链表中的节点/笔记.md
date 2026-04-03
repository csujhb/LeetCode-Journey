

---

# 📚 学习笔记：两两交换链表中的节�?(LeetCode 24)

## 一�?核心任务
给定一个链表，要求两两交换相邻的节点（�?$1\to2\to3\to4$ 变成 $2\to1\to4\to3$），且不能只改变节点内部的值，必须进行真实�?*节点交换**�?

---

## 二�?解法一：递归�?(Recursion) —�?逻辑最优雅

### 💡 核心逻辑
递归的思想是“化整为零”。我们将链表看作：`head` + `next` + `其余部分`�?
1. **终止条件**：如果链表为空或只有一个节点，无法交换，直接返回�?
2. **本层操作**：交�?`head` �?`next`�?
3. **递归连接**：`head` 的下一个节点应该是“其余部分”两两交换后的结果�?
4. **返回结果**：交换后，原本的第二个节�?`next` 变成了新的头�?

### 💻 代码实现�?
```c
struct ListNode* swapPairs(struct ListNode* head) {
    // 1. 终止条件
    if (head == NULL || head->next == NULL) return head;
    
    // 2. 记录第二个节�?
    struct ListNode* next = head->next;
    
    // 3. 递归：head 连上后面处理好的部分
    head->next = swapPairs(next->next);
    
    // 4. 交换：next 指向 head
    next->next = head;
    
    return next;
}
```

---

## 三�?解法二：迭代�?+ 虚拟头节�?(Dummy Node) —�?空间最优化

### 💡 核心逻辑
递归会消�?$O(N)$ 的栈空间，而迭代法仅需 $O(1)$。为了方便处理头节点的交换，我们引入 `dummy` 节点�?
* **关键指针**：使�?`prev` 指针指向每一对交换节点的前驱�?
* **交换三步�?*（假设当前处�?$node1$ �?$node2$）：
    1.  `prev->next = node2`（让前驱指向第二个）
    2.  `node1->next = node2->next`（第一个指向第三个�?
    3.  `node2->next = node1`（第二个指向第一个）

### 💻 代码实现�?
```c
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;

    while (prev->next && prev->next->next) {
        struct ListNode* node1 = prev->next;
        struct ListNode* node2 = node1->next;

        // 执行交换
        prev->next = node2;
        node1->next = node2->next;
        node2->next = node1;

        // 移动 prev，准备处理下一�?
        prev = node1;
    }
    return dummy.next;
}
```

---

## 四�?两种解法对比

| 维度 | 递归�?| 迭代�?(虚拟头节�? |
| :--- | :--- | :--- |
| **时间复杂�?* | $O(N)$ | $O(N)$ |
| **空间复杂�?* | $O(N)$ (系统调用�? | **$O(1)$** (常数级变�? |
| **代码美感** | 极简、逻辑顺畅 | 略显繁琐，需理清顺序 |
| **生产环境** | 适用于小规模数据 | **推荐用于大规模数�?* (防溢�? |

---

## 五�?🛠�?避坑指南

1.  **指针丢失**：在迭代交换时，如果没有先找�?$node2$，一旦断开 $node1->next$，你就再也找不到 $node2$ 了�?
2.  **死循�?*：确保交换后 `node1`（新的末尾）指向的是原本的第三个节点，而不是回指�?
3.  **循环终止条件**：必须同时检�?`prev->next` �?`prev->next->next`，否则在处理奇数个节点时会发生空指针解引用�?
