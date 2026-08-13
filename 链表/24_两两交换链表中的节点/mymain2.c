
// 2026.8.13
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};
struct ListNode *swapPairs(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    struct ListNode dummy = {0, head};
    struct ListNode *cur = &dummy;
    while (cur->next && cur->next->next)
    {
        struct ListNode *next = cur->next;
        struct ListNode *temp = next->next->next;
        next->next->next = next;

        cur->next = next->next;
        next->next = temp;
        cur = next;
    }
    return dummy.next;
}