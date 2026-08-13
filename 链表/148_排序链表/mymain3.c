// 2026.8.13
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *mergeList(struct ListNode *l1, struct ListNode *l2, struct ListNode *prev)
{
    struct ListNode *cur = prev;

    while (l1 && l2)
    {
        if (l1->val > l2->val)
        {
            cur->next = l2;
            l2 = l2->next;
        }
        else
        {
            cur->next = l1;
            l1 = l1->next;
        }
        cur = cur->next;
    }
    if (l1)
        cur->next = l1;
    else
        cur->next = l2;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    return cur;
}

struct ListNode *spiltList(struct ListNode *head, int k)
{
    if (head == NULL)
        return head;
    struct ListNode *cur = head;
    for (int i = 1; i < k && cur->next != NULL; i++)
    {
        cur = cur->next;
    }
    struct ListNode *res = cur->next;
    cur->next = NULL;
    return res;
}

struct ListNode *sortList(struct ListNode *head)
{
    struct ListNode dummy = {0, head};
    struct ListNode *cur = &dummy;
    int len = 0;
    while (cur->next)
    {
        len++;
        cur = cur->next;
    }
    for (int i = 1; i < len; i *= 2)
    {
        struct ListNode *prev = &dummy;
        cur = dummy.next;
        while (cur)
        {
            struct ListNode *head1 = cur;
            struct ListNode *head2 = spiltList(head1, i);
            cur = spiltList(head2, i);
            prev = mergeList(head1, head2, prev);
        }
    }
    return dummy.next;
}