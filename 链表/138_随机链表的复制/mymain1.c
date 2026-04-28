#include <stdlib.h>
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Node {
    int val;
    struct Node* next;
    struct Node* random;
};

struct Node* copyRandomList(struct Node* head) {

    /*
    没加条件判断：if (head == NULL) return NULL;
    */
    struct Node* cur = head;
    while (cur) {
        struct Node* copyNode = (struct Node*)malloc(sizeof(struct Node));
        copyNode->val = cur->val;
        copyNode->next = cur->next;
        //copyNode->random = cur->random;
        cur->next = copyNode; 
        cur = copyNode->next;
    }
    cur = head;
    while (cur) {
        struct Node* copyNode = cur->next;
        if (cur->random != NULL) {
            copyNode->random = cur->random->next;
        }
        else {
            copyNode->random = NULL;
        }
        cur = copyNode->next;
    }
    cur = head;
    struct Node* res = head->next;
    while (cur) {
        struct Node* copyNode = cur->next;
        cur->next = copyNode->next;
        if (copyNode->next)copyNode->next = copyNode->next->next;
        else copyNode->next = NULL;
        cur = cur->next;
    }
    return res;
}
