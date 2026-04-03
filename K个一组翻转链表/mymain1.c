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
struct ListNode* reverseList(struct ListNode* head) {
    if(head == NULL || head->next == NULL)  return head;
    struct ListNode* prev = NULL;
    struct ListNode* cur = head;
    while (cur) {
        struct ListNode* tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;        
    }
    return prev;
}


struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode dummy = { -1,head };
    struct ListNode* prev = &dummy;
    struct ListNode* end = &dummy;
    while (prev->next) {
        for (int i = 0; i < k && end != NULL; i++) {
            end = end->next;
        }
        if (end == NULL) break;
        struct ListNode* start = prev->next;
        struct ListNode* next_group = end->next;
        end->next = NULL;
        prev->next = reverseList(start);
        start->next = next_group;
        prev = start;
        end = start;
    }
    return dummy.next;
}
