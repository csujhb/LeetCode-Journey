// 2026.8.12
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};
struct ListNode *removeElements(struct ListNode *head, int val)
{

    while (head && head->val == val)
        head = head->next;
    struct ListNode *cur = head;
    while (cur && cur->next)
    {
        while (cur->next && cur->next->val == val)
        {
            struct ListNode *tmp = cur->next->next;
            cur->next->next = NULL;
            cur->next = tmp;
        }
        cur = cur->next;
    }
    return head;
}

// 最优解
// 循环遍历，对比每一个元素
struct ListNode *removeElements(struct ListNode *head, int val)
{
    // 创建哨兵节点（虚拟头节点）
    struct ListNode *dummy = (struct ListNode *)malloc(sizeof(struct ListNode));
    dummy->next = head;
    struct ListNode *cur = dummy;
    while (cur->next != NULL)
    {
        if (cur->next->val == val)
        {
            cur->next = cur->next->next;
        }
        else
        {
            cur = cur->next;
        }
    }
    head = dummy->next;
    return head;
}