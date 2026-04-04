/*
第一次做时我做不出来，思路不对
*/
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

struct ListNode* getTail(struct ListNode* head, struct ListNode* prev ,int k) {
    struct ListNode* cur = head;
    struct ListNode* tmp = NULL;
    for (int i = 0; i < k - 1; i++) {
        tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    return tmp;
}

int getLen(struct ListNode* head) {
    int k = 0;
    while (head) {
        k++;
        head = head->next;
    }
    return k;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (k == 1) return head;
    int num = getLen(head) / k;
    struct ListNode* node = NULL;
    struct ListNode* cur = head;
    for (int i = 0; i < num; i++) {
        node = getTail(cur, node,k);
        cur->next = node;
        node = cur;
        cur = cur->next;
    }
}
