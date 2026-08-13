// 2026.8.12
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *cur = head;
    struct ListNode *prev = NULL;
    while (cur != NULL)
    {
        struct ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}