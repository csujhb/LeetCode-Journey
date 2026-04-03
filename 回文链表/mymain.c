#include <stdio.h>
#include <stdbool.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode {
    int val;
    struct ListNode* next;
}ListNode;

void reverseList(struct ListNode** head) {
    struct ListNode* prev = NULL;
    struct ListNode* cur= *head;
    while (cur != NULL) {
        struct ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *head = prev;
}

bool isPalindrome(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    reverseList(&slow);
    fast = head;
    while (fast != NULL && slow != NULL) {
        if (fast->val != slow->val) return false;
        slow = slow->next;
        fast = fast->next;
    }
    return true;
}
