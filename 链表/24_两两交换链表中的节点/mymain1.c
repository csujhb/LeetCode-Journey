// 2026.6.4
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};
struct ListNode *swapNode(struct ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    struct ListNode *next = head->next;
    next->next = head;
    return next;
}

struct ListNode *swapPairs(struct ListNode *head)
{
    struct ListNode dummy = {0, NULL};
    struct ListNode *p = &dummy;
    while (head && head->next)
    {
        struct ListNode *nextHead = head->next->next;
        p->next = swapNode(head);
        p = head;
        head = nextHead;
    }
    p->next = head; // 这一步是必要的，我之前加了head!=NULL的判断，这是不对的，因为这样的话导致最后两个结点互指
    return dummy.next;
}