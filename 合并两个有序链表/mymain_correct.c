
#include <stdio.h>
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
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // 创建一个虚拟的头节点（哨兵节点），随便给个值比如 -1
    struct ListNode dummy;
    dummy.val = -1;
    dummy.next = NULL;

    // tail 指针永远指向新链表的当前最后一个节点，初始指向 dummy
    struct ListNode* tail = &dummy;

    // 当两个链表都不为空时，比较大小，谁小就把谁接到 tail 后面
    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        }
        else {
            tail->next = list2;
            list2 = list2->next;
        }
        // tail 往后移动一步，准备迎接下一个节点
        tail = tail->next;
    }

    // 循环结束，肯定有一个链表空了。
    // 直接把 tail->next 指向那个还没空的链表即可，无需使用 while 循环逐个拼接
    if (list1 != NULL) {
        tail->next = list1;
    }
    else {
        tail->next = list2;
    }

    // dummy.next 就是合并后真正开始的第一个节点
    return dummy.next;
}
