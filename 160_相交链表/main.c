/*
这个方法为什么成立？

假设：

链表 A 长度是 a + c
链表 B 长度是 b + c
其中 c 是公共尾部长度

那么：

pA 先走 A，再走 B，总路程是 a + c + b
pB 先走 B，再走 A，总路程是 b + c + a

两个人走的总长度一样。

所以：

如果有交点，它们一定会在交点相遇
如果没有交点，它们最终会一起走到 NULL
*/

#include <stdio.h>
struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    struct ListNode* pA = headA;
    struct ListNode* pB = headB;

    while (pA != pB) {
        pA = ((pA == NULL) ? headB : (pA->next));
        pB = ((pB == NULL) ? headA : (pB->next));
    }

    return pA;
}
