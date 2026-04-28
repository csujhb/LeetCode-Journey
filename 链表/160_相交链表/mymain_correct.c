
#include <stdio.h>
struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    int lenA = 0, lenB = 0;
    struct ListNode* pA = headA;
    struct ListNode* pB = headB;

    while (pA) {
        lenA++;
        pA = pA->next;
    }
    while (pB) {
        lenB++;
        pB = pB->next;
    }

    pA = headA;
    pB = headB;

    if (lenA > lenB) {
        int diff = lenA - lenB;
        while (diff--) pA = pA->next;
    }
    else {
        int diff = lenB - lenA;
        while (diff--) pB = pB->next;
    }

    while (pA != pB) {
        pA = pA->next;
        pB = pB->next;
    }

    return pA;
}
