# 📚 学习笔记：两两交换链表中的节点 (LeetCode 24)

## 核心任务

给定一个链表，要求两两交换相邻的节点（如 $1\to 2\to 3\to 4$ 变成 $2\to 1\to 4\to 3$），且不能只改变节点内部的值，必须进行真实的 **节点交换**。

------

##解法一：递归法 (Recursion) —— 逻辑最优雅

### 💡 核心逻辑

递归的思想是“化整为零”。我们将链表看作：`head` + `next` + `其余部分`：

1. **终止条件**：如果链表为空或只有一个节点，无法交换，直接返回。
2. **本层操作**：交换 `head` 与 `next`。
3. **递归连接**：`head` 的下一个节点应该是“其余部分”两两交换后的结果。
4. **返回结果**：交换后，原本的第二个节点 `next` 变成了新的头。

### 💻 代码实现：

C

```
struct ListNode* swapPairs(struct ListNode* head) {
    // 1. 终止条件
    if (head == NULL || head->next == NULL) return head;
    
    // 2. 记录第二个节点
    struct ListNode* next = head->next;
    
    // 3. 递归：head 连上后面处理好的部分
    head->next = swapPairs(next->next);
    
    // 4. 交换：next 指向 head
    next->next = head;
    
    return next;
}
```

------

## 解法二：迭代法 + 虚拟头节点 (Dummy Node) —— 空间最优化

### 💡 核心逻辑

递归会消耗 $O(n)$ 的栈空间，而迭代法仅需 $O(1)$。为了方便处理头节点的交换，我们引入 `dummy` 节点：

- **关键指针**：使用 `prev` 指针指向每一对交换节点的前驱。
- **交换三步走**（假设当前处理 $node1$ 与 $node2$）：
  1. `prev->next = node2`（让前驱指向第二个）
  2. `node1->next = node2->next`（第一个指向第三个）
  3. `node2->next = node1`（第二个指向第一个）

### 💻 代码实现：

C

```
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

        // 移动 prev，准备处理下一对
        prev = node1;
    }
    return dummy.next;
}
```

------

## 两种解法对比

| **维度**       | **递归法**          | **迭代法 (虚拟头节点)**         |
| -------------- | ------------------- | ------------------------------- |
| **时间复杂度** | $O(n)$              | $O(n)$                          |
| **空间复杂度** | $O(n)$ (系统调用栈) | **$O(1)$** (常数级变量)         |
| **代码美感**   | 极简、逻辑顺畅      | 略显繁琐，需理清顺序            |
| **生产环境**   | 适用于小规模数据    | **推荐用于大规模数据** (防溢出) |

------

## 🛠️ 避坑指南

1. **指针丢失**：在迭代交换时，如果没有先找到 $node2$，一旦断开 `node1->next`，你就再也找不到 $node2$ 了。
2. **死循环**：确保交换后 `node1`（新的末尾）指向的是原本的第三个节点，而不是回指。
3. **循环终止条件**：必须同时检查 `prev->next` 与 `prev->next->next`，否则在处理奇数个节点时会发生空指针解引用。
