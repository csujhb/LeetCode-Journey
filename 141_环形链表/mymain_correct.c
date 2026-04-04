/*
相对我之前写的代码主要减少了多余的判断
*/
#include <stdbool.h>
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
bool hasCycle(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;

    // 只要 fast 还没走到尽头，且 fast 的下一个节点也不为空，就继续跑
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // 慢指针走一步
        fast = fast->next->next;    // 快指针走两步

        if (slow == fast) {         // 如果套圈相遇，说明有环
            return true;
        }
    }

    return false; // 快指针走到链表尽头，说明无环
}
