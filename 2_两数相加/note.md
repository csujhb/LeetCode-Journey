# 📚 学习笔记：两数相加 (LeetCode 2)

## 核心思想：模拟竖式加法

这道题本质上是要求我们像做小学算术一样，从个位（链表头）开始，逐位相加并处理进位。由于链表已经是**逆序**存储的（个位在最前面），这恰好完美契合了我们从低位到高位依次进位的运算直觉。

### 💡 核心逻辑与技巧

1. **统一的循环条件**：使用 `while (l1 || l2 || carry)`。这种写法极其优雅，一次性处理了三种情况：
   - 两个链表等长。
   - 两个链表不等长（短的链表走到头后视为 0）。
   - 最高位产生进位（例如 $99 + 1 = 100$，循环会在 `l1`, `l2` 都为空后，因为 `carry == 1` 再执行最后一次，创建最高位）。
2. **虚拟头节点 (Dummy Node)**：使用一个不存储实际有效数据的 `temp` 节点作为起始点，统一 `cur->next` 的操作逻辑，避免繁琐的头节点判空。
3. **进位状态机**：
   - 当前位总和：`sum = val1 + val2 + carry;`
   - 当前位留下的数字：`sum % 10`
   - 传递给下一位的进位：`sum / 10`

------

## 解法一：工业级标准解法（新建链表）

这是最通用、最安全的写法。它不破坏原有的输入数据（纯函数），通过不断 `malloc` 新节点来构建结果链表。时间复杂度和空间复杂度均为 $O(\max(M, N))$。

### 💻 C 语言代码模板：

C

```
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0; // 进位
    struct ListNode temp = { -1, NULL }; // 在栈上分配虚拟头节点，避免后续 free
    struct ListNode* cur = &temp;
    
    // 只要 l1、l2 没走完，或者还有进位没处理，就继续循环
    while (l1 || l2 || carry) {
        int sum = carry; // 直接把进位作为初始和
        
        if (l1) { 
            sum += l1->val; 
            l1 = l1->next; 
        }
        if (l2) { 
            sum += l2->val; 
            l2 = l2->next; 
        }
        
        carry = sum / 10; // 计算新的进位
        
        // 创建新节点并挂载
        struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = sum % 10;
        node->next = NULL;
        
        cur->next = node;
        cur = cur->next;
    }
    
    return temp.next;
}
```

------

## 解法二：极致优化解法（原地修改 In-place）

这是追求极致性能的“极客写法”。直接复用 `l1` 或 `l2` 已有的节点内存，将相加结果覆盖写入 `l1` 中。只有在最后产生额外进位时才分配极少量的内存。时间复杂度 $O(\max(M, N))$，空间复杂度降为 **$O(1)$**。

### 💻 C 语言代码模板：

C

```
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* p1 = l1;
    struct ListNode* p2 = l2;
    struct ListNode* tail = NULL; // 记录尾节点，方便后续拼接和追加进位
    int carry = 0;

    // 1. 重叠部分：直接覆盖写入 p1 (即 l1)
    while (p1 != NULL && p2 != NULL) {
        int sum = p1->val + p2->val + carry;
        p1->val = sum % 10;       
        carry = sum / 10;
        
        tail = p1;                
        p1 = p1->next;
        p2 = p2->next;
    }

    // 2. 如果 l2 更长，将 l2 剩下的部分接到 l1 尾部
    if (p2 != NULL) {
        tail->next = p2;
        p1 = p2; // 让 p1 指向接力过来的 l2 节点
    }

    // 3. 消化剩余的进位（无论剩下的是 l1 还是 l2）
    while (p1 != NULL) {
        int sum = p1->val + carry;
        p1->val = sum % 10;       
        carry = sum / 10;
        
        tail = p1;                
        p1 = p1->next;
    }

    // 4. 所有节点走完，如果最后还有进位，开辟唯一一个新节点
    if (carry > 0) {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = carry;
        newNode->next = NULL;
        tail->next = newNode;
    }

    return l1; // 因为全程在修改 l1，直接返回 l1 的头指针
}
```

------

## 两种解法的权衡对比

| **比较维度**   | **解法一 (新建链表)**   | **解法二 (原地修改)**              |
| -------------- | ----------------------- | ---------------------------------- |
| **空间复杂度** | $O(\max(M, N))$         | **$O(1)$**                         |
| **代码可读性** | 逻辑直观，代码整洁      | 较复杂，涉及链表拼接与接力         |
| **数据安全性** | **高** (不破坏输入数据) | **低** (破坏了原链表，有副作用)    |
| **适用场景**   | 通用软件开发、业务系统  | 算法竞赛、嵌入式等内存极其受限场景 |

------

## 💣 新手高频“踩坑”点

- **忘记移动指针**：在 `while` 循环末尾，经常有人忘了写 `cur = cur->next;`，导致所有新节点都覆盖在了同一个位置。
- **内存泄漏风险**：在标准解法中，如果自己 `malloc` 了一个 `dummy` 头节点，返回前一定要 `free` 掉它。像这篇笔记中**在栈上声明** `struct ListNode temp = { -1, NULL };` 是最聪明且安全的做法。
