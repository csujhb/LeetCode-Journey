
#include <stdio.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode* next;
};
/*
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    struct ListNode* node1 = headA;
    struct ListNode* node2 = headB;
    int flag = -1;
    int count = 0;
    while (node1 != NULL || node2 != NULL) {
        if (node1) {
            node1 = node1->next;
        }
        else {
            if (flag != 2) {
                flag = 2;
            }
            count++;
        }
        if (node2) {
            node2 = node2->next;
        }
        else {
            if (flag != 1) {
                flag = 1;
            }
            count++;
        }
    }
    node1 = headA;
    node2 = headB;
    if (flag == 1) {
        while (count--) {
            node1 = node1->next;
    }
    } 
    else if (flag == 2) {
        while (count--) {
            node2 = node2->next;
        }
    }
    while (node1 != node2) {
        node2 = node2->next;
        node1 = node1->next;
    }
    return node1;
}


struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    struct ListNode* node1 = headA;
    struct ListNode* node2 = headB;
    struct ListNode* node3=NULL;
    while (node1 != NULL && node2 != NULL) {
        node2 = node2->next;
        node1 = node1->next;
    }
    if (node1 == NULL) {
        node3 = headB;
        node1 = headA;
        while (node2 != NULL) {
            node2 = node2->next;
            node3 = node3->next;
        }

    }
    else {
        node3 = headA;
        while (node1 != NULL) {
            node1 = node1->next;
            node3 = node3->next;
        }
        node1 = headB;
    } 
    while (node3 != node1) {
        node3 = node3->next;
        node1 = node1->next;
    }
    return node3;
}*/
