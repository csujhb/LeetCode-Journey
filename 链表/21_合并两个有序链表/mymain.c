
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

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 == NULL)  return list2;
    if (list2 == NULL)  return list1;
    struct ListNode* resList = list1;
    struct ListNode* saveList = resList;
    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            resList->next = list1;
            list1 = list1->next;
        }
        else {
            resList->next = list2;
            list2 = list2->next;
        }
        resList = resList->next;
    }
    while (list1 != NULL) {
        resList->next = list1;
        list1 = list1->next;
        resList = resList->next;
    }
    while (list2 != NULL) {
        resList->next = list2;
        list2 = list2->next;
        resList = resList->next;
    }
    resList->next = NULL;
    return saveList->next;
}
