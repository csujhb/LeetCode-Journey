#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    // 1. 创建虚拟头节点，统一所有删除逻辑（包括删除真正的 head）
    struct ListNode dummy;
    dummy.val = -1;
    dummy.next = head;

    struct ListNode* fast = &dummy;
    struct ListNode* slow = &dummy;

    // 2. fast 指针先走 n 步
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }

    // 3. fast 和 slow 同时走，直到 fast 走到链表的最后一个节点
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    // 4. 此时 slow 恰好停在待删除节点的前驱节点
    struct ListNode* targetNode = slow->next; // 暂存要被删除的节点，用于 free

    // 5. 核心删除逻辑：越过待删除节点
    slow->next = slow->next->next;

    // 6. 释放堆内存，防止内存泄漏 (C/C++ 工程必备素质)
    free(targetNode);

    // 7. 返回真正的头节点
    return dummy.next;
}
