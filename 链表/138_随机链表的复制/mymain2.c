// 2026.6.4
#include <stdlib.h>
struct Node
{
    int val;
    struct Node *next;
    struct Node *random;
};

struct Node *copyRandomList(struct Node *head)
{
    if (head == NULL)
        return NULL; // 第一次写时没添加
    struct Node *cur = head;
    while (cur != NULL)
    {
        struct Node *copyNode = (struct Node *)malloc(sizeof(struct Node));
        copyNode->next = cur->next;
        copyNode->val = cur->val;
        cur->next = copyNode;
        cur = copyNode->next;
    }
    cur = head;
    while (cur != NULL)
    {
        if (cur->random != NULL)
            cur->next->random = cur->random->next;
        else
            cur->next->random = NULL;
        cur = cur->next->next;
    }
    cur = head;
    struct Node *res = head->next;
    while (cur != NULL)
    {
        struct Node *copyNode = cur->next;
        struct Node *nextNode = copyNode->next;
        cur->next = nextNode;
        if (nextNode)
        {
            copyNode->next = nextNode->next;
        }
        else
        {
            copyNode->next = NULL;
        }

        cur = nextNode;
    }

    return res;
}
