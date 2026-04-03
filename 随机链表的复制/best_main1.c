/*
节点交织法 (纯 C 语言实现)核心思想：
不借用任何额外的本子记录，直接把克隆节点插在原节点的背后，形成 原1 -> 克1 -> 原2 -> 克2 的结构。
利用这种“肉身绑定”的物理位置关系，瞬间找到目标。
时间复杂度：O(N)，遍历了三次链表。
空间复杂度：O(1)，没有使用任何额外的数组或哈希表。
*/

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
    if (head == NULL) return NULL;

    struct Node* curr = head;

    // ==========================================
    // 第一步：克隆节点，并交织在一起
    // 变成：A -> A' -> B -> B' -> C -> C'
    // ==========================================
    while (curr != NULL) {
        struct Node* cloneNode = (struct Node*)malloc(sizeof(struct Node));
        cloneNode->val = curr->val;
        // 把新节点插在原节点的后面
        cloneNode->next = curr->next;
        curr->next = cloneNode;
        // 往前推进两步（跳过刚建好的克隆节点，来到下一个原节点）
        curr = cloneNode->next;
    }

    // ==========================================
    // 第二步：连接克隆节点的 random 指针
    // ==========================================
    curr = head;
    while (curr != NULL) {
        struct Node* cloneNode = curr->next;
        // 如果原节点的 random 有指向
        if (curr->random != NULL) {
            // 原节点 random 指向的那个节点的“下一个”，就是我们想要的克隆目标！
            cloneNode->random = curr->random->next;
        }
        else {
            cloneNode->random = NULL;
        }
        // 往前推进两步
        curr = cloneNode->next;
    }

    // ==========================================
    // 第三步：拆分链表（将原链表和克隆链表分离）
    // 必须要把原链表恢复原样，否则力扣评测机会报错
    // ==========================================
    curr = head;
    struct Node* cloneHead = head->next; // 记录克隆链表的头，留着最后返回

    while (curr != NULL) {
        struct Node* cloneNode = curr->next;
        // 记录下一个原节点
        struct Node* nextOriginal = cloneNode->next;

        // 恢复原链表的 next 指针
        curr->next = nextOriginal;

        // 链接克隆链表的 next 指针（注意判断是否到了最后）
        if (nextOriginal != NULL) {
            cloneNode->next = nextOriginal->next;
        }
        else {
            cloneNode->next = NULL;
        }

        // 推进到下一个原节点
        curr = nextOriginal;
    }

    return cloneHead;
}
