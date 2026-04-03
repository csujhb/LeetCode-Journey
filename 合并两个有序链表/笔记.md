

---

# 📚 学习笔记：合并两个有序链�?(LeetCode 21)

## 核心思想：双指针比大�?
因为两个链表本身已经是有序的（升序），我们只需要准备两个指针分别指向两个链表的头部，每次挑出一�?*较小**的节点，把它挂到我们新链表的尾部，然后让被挑走节点的那个链表指针往后走一步即可�?

---

## 一�?工业级最优解：迭代法 + 虚拟头节�?(Dummy Node)

### 💡 核心逻辑与技�?
在新建链表时，最大的痛点�?*“我不知道第一个节点该选谁�?*（如果直接选，需要写一�?`if-else` 去处理空指针和比大小）�?
为了优雅地解决这个问题，我们引入**虚拟头节点（Dummy Node�?*�?
1. 凭空创造一个假节点 `dummy` 作为“桩子”�?
2. 用一�?`tail` 指针永远指向新链表的末尾（初始指�?`dummy`）�?
3. 循环比较 `list1` �?`list2`，谁小就�?`tail->next` 指向谁，然后 `tail` 往前挪�?
4. 循环结束后，把还没遍历完的那个链�?*一撸到�?*直接挂在 `tail` 后面�?
5. 返回真实的数据头节点：`dummy.next`�?

* **时间复杂�?*�?O(N + M)$，其�?$N$ �?$M$ 分别是两个链表的长度�?
* **空间复杂�?*�?O(1)$，只需要常数级别的额外指针变量�?

### 💻 标准代码模板
```c
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;      // 创建虚拟头节�?
    dummy.val = -1;
    struct ListNode* tail = &dummy; // tail 指针用于拼接后续节点
    
    // 当两个链表都有节点时，进行比大小拼接
    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next; // tail 永远要移动到当前最新挂载的节点�?
    }
    
    // 扫尾工作：谁还没空，就直接把剩下的整串接�?tail 后面
    tail->next = (list1 != NULL) ? list1 : list2;
    
    return dummy.next; // 返回真正的头节点
}
```

---

## 二�?降维打击解法：递归�?(Recursion)

### 💡 核心逻辑

不借助任何外部�?`dummy` 节点，直接利用函数调用栈来“从后往前”拼接链表�?
宏观上我们只考虑一件事�?*当前这两个头节点，谁该做新链表的头？**
* 如果 `list1->val < list2->val`，那�?`list1` 就是头。�?`list1` 后面的节点，应该接上 **`list1` 剩下的部分和 `list2` 整体合并后的结果**�?

* **时间复杂�?*�?O(N + M)$�?
* **空间复杂�?*�?O(N + M)$，递归调用会消耗系统栈空间，如果链表极长可能会导致栈溢出（Stack Overflow）�?

### 💻 极简代码模板
```c
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // 递归终止条件
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    
    // 比较头节点，小的作为当前层的头，并递归处理后续节点
    if (list1->val < list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}
```

---

## 三�?💣 新手高频“踩坑”指�?

1. **链表操作最忌讳“自环”：**
   如果在代码中写了类似 `NodeA->next = NodeA` 的逻辑，链表就会在当前节点无限打转（死循环），后面的所有节点全部丢失。操作指针前一定要想清楚当前指针指在哪个内存地址�?
2. **数组思维的残留：**
   在合并数组的尾部时，我们需要写 `while` 循环把剩下的元素一个一�?`push` 进去。但**链表不需�?*！链表只要把头接上，后面的元素自然就跟着连过来了。所以扫尾工作只需要一�?`tail->next = remaining_list;` 即可�
