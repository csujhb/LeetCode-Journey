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
    struct ListNode* fast = head;
    
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    if (fast == NULL) return head->next;
    struct ListNode* slow = head;
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    fast = slow->next->next;
    slow->next->next = NULL;
    slow->next = fast;
    return head;
}
