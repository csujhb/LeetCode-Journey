#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/*
时间复杂度：O(N)
空间复杂度：O(N)
*/
struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;

    struct ListNode* next = head->next;

    // 先让 head 的 next 指向下一层递归处理好的链表头
    head->next = swapPairs(next->next);
    // 再让 next 的 next 指向 head，完成反转
    next->next = head;

    return next;
}
