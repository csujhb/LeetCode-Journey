#include <stdlib.h>
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
// 辅助函数：反转一条普通的单向链表
// 返回反转后的新头节点
struct ListNode* reverse(struct ListNode* head) {
    struct ListNode* pre = NULL;
    struct ListNode* curr = head;
    while (curr != NULL) {
        struct ListNode* next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    return pre;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    // 1. 创建虚拟头节点，这是处理链表头发生变化时的通用技巧
    struct ListNode dummy;
    dummy.val = -1;
    dummy.next = head;

    struct ListNode* prev = &dummy;
    struct ListNode* end = &dummy;

    // 只要 end 后面还有节点，就继续尝试走
    while (end->next != NULL) {
        // 2. 让 end 走 k 步，寻找这一组的尾巴
        for (int i = 0; i < k && end != NULL; i++) {
            end = end->next;
        }

        // 如果 end 变成 NULL，说明最后这一组不够 k 个，直接跳出循环，保持原状
        if (end == NULL) break;

        // 3. 记录边界，准备切断链表
        struct ListNode* start = prev->next;
        struct ListNode* next_group = end->next;

        // 切断当前组与后面链表的联系
        end->next = NULL;

        // 4. 反转当前组（反转后，原来的 start 变成了尾巴，原来的 end 变成了头）
        prev->next = reverse(start);

        // 5. 将反转后的尾巴接回大部队
        start->next = next_group;

        // 6. 更新指针，准备处理下一组
        prev = start;
        end = start;// 现在的 start 实际上是这一组的最后一个节点了
        
    }

    return dummy.next;
}
