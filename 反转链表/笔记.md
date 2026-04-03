

------

# LeetCode 206. 反转链表 学习笔记

## 1. 题目描述

给你单链表的头结�?`head`，请你反转链表，并返回反转后的链表头结点�?

------

## 2. 示例

### 示例 1

```text
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```

原链表：

```text
1 -> 2 -> 3 -> 4 -> 5 -> NULL
```

反转后：

```text
5 -> 4 -> 3 -> 2 -> 1 -> NULL
```

------

### 示例 2

```text
输入：head = [1,2]
输出：[2,1]
```

------

### 示例 3

```text
输入：head = []
输出：[]
```

------

## 3. 题目本质

这题本质上是在做一件事�?

> 把链表中每个节点�?`next` 指针方向全部反过�?

例如原来是：

```text
1 -> 2 -> 3 -> NULL
```

反转后要变成�?

```text
3 -> 2 -> 1 -> NULL
```

难点不在“值”，而在于：

> 单链表只能顺着 `next` 往后走，一旦你改了某个 `next`，原来的后继节点就可能找不到�?

所以关键就是：

> **改指针之前，先把后继保存下来**

------

## 4. 常见做法

这题最经典的有两种方法�?

1. **迭代�?*
2. **递归�?*

------

## 5. 方法一：迭代法

------

## 5.1 思路

用三个指针：

- `prev`：当前节点反转后要指向的前一个节�?
- `cur`：当前正在处理的节点
- `next`：提前保�?`cur->next`，防止链断掉

每轮循环做三件事�?

1. 先保�?`cur->next`
2. �?`cur->next = prev`
3. 再整体向后推�?

------

## 5.2 代码

```c
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* cur = head;

    while (cur != NULL) {
        struct ListNode* next = cur->next; // 先保存后�?
        cur->next = prev;                  // 反转指针
        prev = cur;                        // prev 前进
        cur = next;                        // cur 前进
    }

    return prev;
}
```

------

## 5.3 执行过程示例

以：

```text
1 -> 2 -> 3 -> NULL
```

为例�?

### 初始状�?

```text
prev = NULL
cur  = 1
链表�? -> 2 -> 3 -> NULL
```

------

### 第一次循�?

先保存：

```text
next = 2
```

反转�?

```text
1 -> NULL
```

再移动：

```text
prev = 1
cur  = 2
```

当前状态：

```text
已反转部分：1 -> NULL
未处理部分：2 -> 3 -> NULL
```

------

### 第二次循�?

保存�?

```text
next = 3
```

反转�?

```text
2 -> 1 -> NULL
```

移动�?

```text
prev = 2
cur  = 3
```

当前状态：

```text
已反转部分：2 -> 1 -> NULL
未处理部分：3 -> NULL
```

------

### 第三次循�?

保存�?

```text
next = NULL
```

反转�?

```text
3 -> 2 -> 1 -> NULL
```

移动�?

```text
prev = 3
cur  = NULL
```

循环结束，返�?`prev`

------

## 5.4 复杂度分�?

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`

这是最优的�?

------

## 5.5 优缺�?

### 优点

- 代码高效
- 空间复杂度最�?
- 面试中最常用

### 缺点

- 需要自己维护多个指�?
- 对刚学链表的人来说容易绕

------

## 6. 方法二：递归�?

------

## 6.1 思路

递归法的核心思想是：

> 先把后面的链表反转好，再把当前节点接到最�?

例如�?

```text
1 -> 2 -> 3 -> 4 -> NULL
```

假设递归已经把：

```text
2 -> 3 -> 4 -> NULL
```

反转成：

```text
4 -> 3 -> 2 -> NULL
```

那么现在只需要再�?`1` 接到 `2` 后面即可�?

------

## 6.2 代码

```c
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* newHead = reverseList(head->next);

    head->next->next = head;
    head->next = NULL;

    return newHead;
}
```

------

## 6.3 为什么这两句是关�?

```c
head->next->next = head;
head->next = NULL;
```

假设当前�?`head = 1`，并且递归已经把后面变成：

```text
3 -> 2
```

而原本还有：

```text
1 -> 2
```

那么�?

### 第一�?

```c
head->next->next = head;
```

就是�?

```c
2->next = 1;
```

把指针反过来�?

### 第二�?

```c
head->next = NULL;
```

�?`1` 变成尾节点，否则会形成环�?

------

## 6.4 执行过程示例

以：

```text
1 -> 2 -> 3 -> NULL
```

为例�?

------

### 调用 1

```c
reverseList(1)
```

它会递归调用�?

```c
reverseList(2)
```

------

### 调用 2

```c
reverseList(2)
```

它又递归调用�?

```c
reverseList(3)
```

------

### 调用 3

```c
reverseList(3)
```

因为 `3->next == NULL`，命中递归出口，直接返�?`3`

------

### 开始回�?

#### 回到节点 2

执行�?

```c
2->next->next = 2;   // 3->next = 2
2->next = NULL;
```

链表变成�?

```text
3 -> 2 -> NULL
```

------

#### 回到节点 1

执行�?

```c
1->next->next = 1;   // 2->next = 1
1->next = NULL;
```

链表变成�?

```text
3 -> 2 -> 1 -> NULL
```

最后返回新头结�?`3`

------

## 6.5 复杂度分�?

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`

注意：递归会消耗调用栈空间，所以额外空间不�?`O(1)`�?

------

## 6.6 优缺�?

### 优点

- 代码�?
- 思路优美
- 递归逻辑清晰

### 缺点

- 有递归栈开销
- 链表过长时可能不如迭代稳

------

## 7. 两种方法对比

| 方法   | 时间复杂�?| 空间复杂�?| 特点                 |
| ------ | ---------- | ---------- | -------------------- |
| 迭代�?| `O(n)`     | `O(1)`     | 最常用，空间最�?    |
| 递归�?| `O(n)`     | `O(n)`     | 写法优美，但有栈开销 |

------

## 8. 为什么迭代法更推�?

因为这题并不复杂，迭代法已经能做到：

- 时间最�?`O(n)`
- 空间最�?`O(1)`

所以在实际刷题和面试中，一般优先写迭代法�?

递归法更多是为了�?

- 展示你理解递归
- 补充第二种写�?
- 训练链表递归思维

------

## 9. 你的代码分析

你写的是�?

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

这就是标准的 **迭代�?*，而且写得很简洁�?

### 优点

- 逻辑完整
- 写法标准
- 没有多余步骤
- 可以直接作为模板记忆

这个版本已经很好了�?

------

## 10. 易错点总结

### 10.1 改指针前一定要先保�?`next`

错误写法如果直接�?

```c
cur->next = prev;
cur = cur->next;
```

那么原来后继节点就丢了�?

一定要先写�?

```c
struct ListNode* next = cur->next;
```

------

### 10.2 最后返回的�?`prev`，不�?`head`

循环结束后：

- `cur == NULL`
- `prev` 才是新的头结�?

所以要�?

```c
return prev;
```

------

### 10.3 递归法中别忘了把 `head->next = NULL`

如果不写这句，链表可能形成环�?

------

### 10.4 空链表和单节点链表都要能处理

例如�?

- `head == NULL`
- `head->next == NULL`

这两种情况本身就是反转后的结果�?

------

## 11. 模板总结

### 11.1 迭代模板

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

------

### 11.2 递归模板

```c
struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;

    return newHead;
}
```

------

## 12. 面试答题模板

如果面试官让你讲思路，可以这样说�?

> 反转链表可以用迭代和递归两种方式实现�?
> 迭代法中，用 `prev`、`cur`、`next` 三个指针，遍历链表时先保存当前节点的后继，再把当前节点的 `next` 指向前一个节点，然后整体向后推进，直到遍历结束，最�?`prev` 就是新的头结点�?
> 这种方法时间复杂度是 `O(n)`，额外空间复杂度�?`O(1)`�?
>
> 递归法中，先递归反转后面的链表，再让当前节点的下一个节点反过来指向当前节点，并把当前节点的 `next` 置空。递归结束后返回新的头结点即可�?
> 时间复杂度同样是 `O(n)`，但由于递归栈，空间复杂度是 `O(n)`�?

------

## 13. 一句话总结

> **反转链表的核心就是：改当前节点指针前，先保存后继节点�?*

------

## 14. 适合记住的结�?

### 结论 1

反转链表最经典的写法是 **迭代三指�?*�?

### 结论 2

迭代法时�?`O(n)`、空�?`O(1)`，是最推荐的方法�?

### 结论 3

递归法也能做，但空间复杂度是 `O(n)`�?

### 结论 4

链表反转类题目经常作为很多复杂链表题的基础模板，一定要熟练�?

------

