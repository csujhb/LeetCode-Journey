// 2026.6.4
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode dummy = {0, NULL};
    struct ListNode *p = &dummy;
    while (list1 && list2)
    {
        if (list1->val > list2->val)
        {
            p->next = list2;
            list2 = list2->next;
        }
        else
        {
            p->next = list1;
            list1 = list1->next;
        }
        p = p->next;
    }
    if (list1)
        p->next = list1;
    if (list2)
        p->next = list2;
    return dummy.next;
}