#include <stdlib.h>
/*
typedef struct ListNode {
    int val;
    struct ListNode* next;
}ListNode;
*/

typedef struct ListNode {
    int val;
    struct ListNode* next;
}ListNode;
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* p1 = l1;
    struct ListNode* p2 = l2;
    struct ListNode* tail = NULL; // 记录当前链表的尾节点，方便最后追加进位
    int carry = 0;

    // 第一阶段：两个链表都有节点的部分，结果直接覆盖写回 p1
    while (p1 != NULL && p2 != NULL) {
        int sum = p1->val + p2->val + carry;
        p1->val = sum % 10;       // 原地修改 l1 的值
        carry = sum / 10;

        tail = p1;                // 更新尾节点
        p1 = p1->next;
        p2 = p2->next;
    }

    // 第二阶段：如果 l2 比 l1 长，把 l2 剩下的部分接在 l1 尾部
    if (p2 != NULL) {
        tail->next = p2;
        p1 = p2; // 让 p1 指向接力过来的 l2 节点，继续处理
    }

    // 第三阶段：处理接力后的剩余节点（不管是 l1 本身剩下的，还是接力 l2 剩下的）
    // 顺着往下消化进位 (carry)
    while (p1 != NULL) {
        int sum = p1->val + carry;
        p1->val = sum % 10;       // 依然是原地修改
        carry = sum / 10;

        tail = p1;                // 更新尾节点
        p1 = p1->next;
    }

    // 第四阶段：所有节点都走完了，如果还有进位，这是唯一需要开辟新内存的地方
    if (carry > 0) {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = carry;
        newNode->next = NULL;
        tail->next = newNode;
    }

    // 我们全程都是以 l1 为基础框架进行魔改的，所以直接返回 l1
    return l1;
}
