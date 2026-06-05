// 2026.6.4
#include <stdbool.h>
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *prev = NULL;
    struct ListNode *cur = head;
    while (cur != NULL)
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
    struct ListNode *slow = head;
    struct ListNode *fast = head->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct ListNode *NextList = slow->next;
    slow->next = NULL;
    struct ListNode *newhead = reverseList(NextList);
    while (newhead != NULL && head != NULL)
    {
        if (newhead->val != head->val)
            return false;
        newhead = newhead->next;
        head = head->next;
    }
    return true;
}