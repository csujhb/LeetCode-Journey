//使用递归法进行链表反转
#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    // 空链表或只有一个节点，直接返回
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 递归反转 head 后面的链表
    struct ListNode* newHead = reverseList(head->next);

    // head->next 目前是原来的下一个节点
    // 让它反过来指向 head
    head->next->next = head;

    // head 变成尾节点，next 置空
    head->next = NULL;

    return newHead;
}
