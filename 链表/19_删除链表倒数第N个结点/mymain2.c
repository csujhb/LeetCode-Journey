// 2026.8.13
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    struct ListNode dummy = {0, head};
    struct ListNode *cur = &dummy;
    struct ListNode *prev = &dummy;
    for (int i = 0; i < n && cur != NULL; i++)
    {
        cur = cur->next;
    }
    if (cur == NULL)
        return NULL;
    while (cur->next != NULL)
    {
        cur = cur->next;
        prev = prev->next;
    }
    struct ListNode *target = prev->next;
    prev->next = prev->next->next;
    target->next = NULL;
    return dummy.next;
}