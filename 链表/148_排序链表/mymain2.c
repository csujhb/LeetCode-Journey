// 2026.6.5
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *spilt(struct ListNode *head, int k)
{
    if (head == NULL)
        return NULL;
    for (int i = 1; i < k; i++)
    {
        head = head->next;
        if (head == NULL)
            return NULL;
    }
    struct ListNode *res = head->next;
    head->next = NULL;
    return res;
}

struct ListNode *mergeTwoLists(struct ListNode *l1, struct ListNode *l2, struct ListNode *prev)
{
    struct ListNode *p = prev;
    while (l1 && l2)
    {
        if (l1->val > l2->val)
        {
            p->next = l2;
            l2 = l2->next;
        }
        else
        {
            p->next = l1;
            l1 = l1->next;
        }
        p = p->next;
    }

    if (l1)
    {
        p->next = l1;
    }
    else if (l2)
    {
        p->next = l2;
    }
    while (p->next)
        p = p->next;
    return p;
}

struct ListNode *sortList(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    int len = 0;
    struct ListNode *cur = head;
    while (cur != NULL)
    {
        len++;
        cur = cur->next;
    }

    struct ListNode dummy = {0, head};
    for (int i = 1; i < len; i *= 2)
    {
        struct ListNode *prev = &dummy;
        head = dummy.next; // 第一次写时没加
        while (head != NULL)
        {
            struct ListNode *newHead = spilt(head, i);
            struct ListNode *nextHead = spilt(newHead, i);
            prev = mergeTwoLists(head, newHead, prev);
            head = nextHead;
        }
    }
    return dummy.next;
}