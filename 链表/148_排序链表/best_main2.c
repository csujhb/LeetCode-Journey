/*
时间复杂度是 O(N log N)
空间复杂度是 O(1)

使用迭代法
*/

#include <stdio.h>
#include <stdlib.h>

// 辅助结构体定义 (假设已存在)

struct ListNode {
    int val;
    struct ListNode *next;
};


// --- 模块 1：切断链表 ---
// 作用：从 head 开始，保留 step 个节点，把后面的切断，并返回后面部分的头节点
struct ListNode* split(struct ListNode* head, int step) {
    if (head == NULL) return NULL;

    // 往前走 step - 1 步，停在边界节点上
    for (int i = 1; head->next != NULL && i < step; i++) {
        head = head->next;
    }

    // 拔刀断表
    struct ListNode* right = head->next;
    head->next = NULL;

    return right;
}

// --- 模块 2：合并两个有序链表 ---
// 作用：合并 l1 和 l2，将其挂载到 prev 后面，并返回合并后的【最后一个节点】
struct ListNode* merge(struct ListNode* l1, struct ListNode* l2, struct ListNode* prev) {
    struct ListNode* cur = prev;

    // 标准的合并逻辑
    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        }
        else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }

    // 扫尾工作
    cur->next = (l1 != NULL) ? l1 : l2;

    // 一路走到合并后链表的【最末尾】并返回，作为下一组合并的 prev
    while (cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}

// --- 模块 3：主函数 (迭代主控) ---
struct ListNode* sortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;

    // 1. 统计链表总长度
    int length = 0;
    struct ListNode* cur = head;
    while (cur != NULL) {
        length++;
        cur = cur->next;
    }

    // 2. 引入虚拟头节点，这是应对头节点动态变化的万能法宝
    struct ListNode dummy;
    dummy.val = -1;
    dummy.next = head;

    // 3. 开始自底向上归并，步长依次为 1, 2, 4, 8...
    for (int step = 1; step < length; step *= 2) {
        // 每次循环前，prev 指向 dummy，cur 指向真正的起点
        struct ListNode* prev = &dummy;
        cur = dummy.next;

        // 遍历整个链表，按当前的 step 进行成对合并
        while (cur != NULL) {
            // 切下第一段 (长度最多为 step)
            struct ListNode* left = cur;
            struct ListNode* right = split(left, step);

            // 切下第二段 (长度最多为 step)，cur 更新为剩下的开头，留给下一次 while 循环
            cur = split(right, step);

            // 合并 left 和 right，接在 prev 后面。同时 prev 自动移动到合并后的尾部
            prev = merge(left, right, prev);
        }
    }

    return dummy.next;
}
