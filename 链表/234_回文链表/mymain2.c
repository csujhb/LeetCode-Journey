
// 2026.8.13
#include <stdbool.h>
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *cur = head, *prev = NULL;
    while (cur)
    {
        struct ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

bool isPalindrome(struct ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return true;
    }
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast != NULL)
    {
        slow = slow->next;
    }
    struct ListNode *newHead = reverseList(slow);
    while (head != NULL && newHead != NULL)
    {
        if (head->val != newHead->val)
            return false;
        head = head->next;
        newHead = newHead->next;
    }
    return true;
}