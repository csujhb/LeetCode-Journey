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

struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL||head->next == NULL) return head;
    struct ListNode* next = head->next;
    struct ListNode* tmp = next->next;
    next->next = head;
    head->next = swapPairs(tmp);
    return next;
}
