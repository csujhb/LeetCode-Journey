
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
struct ListNode* detectCycle(struct ListNode* head) {
    //if (!head) return NULL;
    struct ListNode* slow = head;
    struct ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        // 如果快慢指针相遇，说明有环
        if (slow == fast) {
            //struct ListNode* ptr = head; // 重新定义一个指针从头开始走
            // 两个指针每次走一步，相遇点即为环的入口
            while (head != slow) {
                head = head->next;
                slow = slow->next;
            }
            return slow; // 找到入口，直接返回
        }
    }

    // 如果循环能自然结束，说明 fast 走到了链表尽头，必定无环
    return NULL;
}
