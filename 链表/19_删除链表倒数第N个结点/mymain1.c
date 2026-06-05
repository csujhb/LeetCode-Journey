// 初次报错，修改后可运行
// 2026.6.4
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    int len = 0;
    struct ListNode *cur = head;
    while (cur)
    {
        len++;
        cur = cur->next;
    }
    // if (len == 1)
    //     return NULL;
    if (len < n)
        return head;
    if (len == n)
    {
        struct ListNode *tmp = head->next;
        head->next = NULL;
        return tmp;
    }
    cur = head;
    for (int i = 1; i < len - n; i++)
    {
        cur = cur->next;
    }
    struct ListNode *next = cur->next;
    cur->next = cur->next->next;
    next->next = NULL;
    return head;
}