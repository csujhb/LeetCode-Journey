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
    while (cur)
    {
        struct ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

struct ListNode *spiltList(struct ListNode *head, int k, struct ListNode **nextHead)
{
    if (head == NULL)
        return NULL;
    struct ListNode *cur = head;
    for (int i = 1; i < k; i++)
    {
        cur = cur->next;
        if (cur == NULL)
        {
            *nextHead = NULL; // 第一次时没加这个，显示超时
            return head;
        }
    }
    *nextHead = cur->next;
    cur->next = NULL;
    return reverseList(head);
}

struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    struct ListNode dummy = {0, NULL};
    struct ListNode *prev = &dummy;
    struct ListNode *tmp = NULL;

    while (head != NULL)
    {
        prev->next = spiltList(head, k, &tmp);
        prev = head;
        head = tmp;
    }
    return dummy.next;
}