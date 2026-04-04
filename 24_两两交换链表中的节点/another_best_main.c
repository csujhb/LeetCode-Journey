
/*
时间复杂度：O(N)
空间复杂度：O(1)
*/

#include <stdlib.h>
struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode dummy;      // 创建虚拟头节点
    dummy.next = head;
    struct ListNode* prev = &dummy; // prev 永远指向准备交换的两个节点的前驱节点

    // 只要还有成对的节点，就继续交换
    while (prev->next != NULL && prev->next->next != NULL) {
        struct ListNode* node1 = prev->next;
        struct ListNode* node2 = prev->next->next;

        // 执行交换的三步曲（核心指针操作）
        prev->next = node2;          // 步骤 1：前驱节点指向第二个节点
        node1->next = node2->next;   // 步骤 2：第一个节点指向第三个节点
        node2->next = node1;         // 步骤 3：第二个节点指向第一个节点

        // prev 往后移动两位，准备处理下一对
        prev = node1;
    }

    return dummy.next;
}
