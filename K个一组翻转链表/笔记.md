

---

# 📚 学习笔记：K 个一组翻转链�?(LeetCode 25)

## 一�?核心心法：分而治之，搭积�?
这道题千万不要试图在一个循环里既找边界又反转指针，那样大脑很容易过载、链表也很容易断裂�?
最稳妥的做法是将其拆分为两个模块：

1. **主函数模�?*：负责“切蛋糕”。每数够 $k$ 个节点，就把它切下来�?
2. **辅助函数模块**：负责“翻转”。写一个最基础的单链表反转函数，把切下来的那一块传进去反转�?
3. **缝合模块**：把反转后的那块“蛋糕”原封不动地拼回主链表中�?

---

## 二�?核心逻辑：掌控全局�?4 个锚点指�?
在处理每一�?$k$ 个节点时，我们需要定�?4 个关键的指针来确保链表不会“失联”：

1. `prev`：当前组**前一个节�?*（初始为 `dummy`）。负责连接反转后的新头节点�?
2. `start`：当前组�?*第一个节�?*。反转后它会变成尾巴�?
3. `end`：当前组�?*最后一个节�?*。反转前，用它来探路；反转后它会变成头�?
4. `next_group`�?*下一组的开�?*（即 `end->next`）。负责在反转后，让当前组的尾巴能接上后面的大部队�?

---

## 三�?标准执行�?(六步�?

1. **探路找尾�?*：`end` �?`prev` 出发，往前走 $k$ 步。如果遇�?`NULL`，说明剩余节点不�?$k$ 个，直接结束算法�?
2. **标记边界**：记�?`start = prev->next`，记�?`next_group = end->next`�?
3. **拔刀断表（极其关键）**：执�?`end->next = NULL`。这一步强行把这一组截断成一个独立的单链表，否则基础的反转函数会一路反转到链表尽头�?
4. **局部反�?*：调用基础�?`reverse(start)` 函数，把这一段反转�?
5. **重新缝合**�?
   * `prev->next = reverse(start)`（把前面的链表接上新头）�?
   * `start->next = next_group`（把新尾巴接上后面的大部队）�?
6. **推进阵线**：把 `prev` �?`end` 都移动到当前�?`start`（即反转后的尾巴）上，准备开启下一组的循环�?

---

## 四�?💻 工业�?C 语言代码模板

```c
// 辅助积木：最基础的反转单链表
struct ListNode* reverse(struct ListNode* head) {
    struct ListNode* pre = NULL;
    struct ListNode* curr = head;
    while (curr != NULL) {
        struct ListNode* next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    return pre;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    // 引入 Dummy Node 应对头节点改变的情况
    struct ListNode dummy;
    dummy.val = -1;
    dummy.next = head;
    
    struct ListNode* prev = &dummy;
    struct ListNode* end = &dummy;

    while (end->next != NULL) {
        // 1. end 探路�?k �?
        for (int i = 0; i < k && end != NULL; i++) {
            end = end->next;
        }
        
        // 节点不够 k 个，提前收工
        if (end == NULL) break;
        
        // 2. 标记锚点
        struct ListNode* start = prev->next;
        struct ListNode* next_group = end->next;
        
        // 3. 断开链表
        end->next = NULL;
        
        // 4 & 5. 反转并缝�?
        prev->next = reverse(start); 
        start->next = next_group;    
        
        // 6. 移动 prev �?end，准备下一�?
        prev = start; 
        end = start;  
    }
    
    return dummy.next;
}
```

---

## 五�?💣 高频踩坑与死亡雷�?
1. **忘记断表（死循环/全表反转�?*：如果没�?`end->next = NULL`，`reverse` 函数遇到当前组的结尾时不会停下，会一直把整个剩下的链表全反转了�?
2. **指针更新错位**：在缝合完之后，很多新手会不知道 `prev` 应该指向谁。记住，反转�?`start` 就变成了这一组的最后一个节点，所�?`prev` 应该更新�?`start`�
