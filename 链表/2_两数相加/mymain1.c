// 2026.6.4
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
    struct ListNode dummy = {0, NULL};
    struct ListNode *p = &dummy;
    int plus = 0;

    while (l1 || l2 || plus)
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

        sum += plus;
        p->next = createNode(sum % 10);
        plus = sum / 10;
        p = p->next;
    }
    return dummy.next;
}