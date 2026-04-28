/*
相对我前面的做法主要有一个优化：
结束返回前：恢复原先的链表
*/


#include <stdbool.h>
#include <stdio.h>
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* cur = head;

    while (cur != NULL) {
        struct ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

bool isPalindrome(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }

    struct ListNode* slow = head;
    struct ListNode* fast = head;

    // 找中点
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 奇数长度，跳过中间节点
    if (fast != NULL) {
        slow = slow->next;
    }

    // 反转后半段
    struct ListNode* second = reverseList(slow);
    struct ListNode* secondCopy = second;  // 备份，便于恢复
    struct ListNode* first = head;

    bool ok = true;
    while (second != NULL) {
        if (first->val != second->val) {
            ok = false;
            break;
        }
        first = first->next;
        second = second->next;
    }

    // 恢复链表
    reverseList(secondCopy);

    return ok;
}
