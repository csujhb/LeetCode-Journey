// 2026.8.13
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *createNode(int val)
{
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->next = NULL;
    node->val = val;
    return node;
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int carry = 0;
    struct ListNode dummy = {0, NULL};
    struct ListNode *cur = &dummy;
    while (carry || l1 || l2)
    {
        int sum = 0;
        if (l1)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2)
        {
            sum += l2->val;
            l2 = l2->next;
        }
        sum += carry;
        carry = sum / 10;

        cur->next = createNode(sum % 10);
        cur = cur->next;
    }

    return dummy.next;
}