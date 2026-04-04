/*
鏃堕棿澶嶆潅搴︽槸 O(N log N)
绌洪棿澶嶆潅搴︽槸 O(log N)

浣跨敤閫掑綊娉?
*/

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

// 妯″潡 1锛氬悎骞朵袱涓湁搴忛摼琛?(绗?21 棰樺師棰?
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    dummy.val = -1;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        }
        else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    // 璋佽繕娌＄┖锛屽氨鎺ヨ皝
    tail->next = (l1 != NULL) ? l1 : l2;
    return dummy.next;
}

// 妯″潡 2锛氬鎵鹃摼琛ㄤ腑鐐瑰苟杩斿洖
struct ListNode* getMid(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;

    struct ListNode* slow = head;
    // 娉ㄦ剰锛氫负浜嗚鍋舵暟涓妭鐐规椂 slow 鍋滃湪宸﹀崐閮ㄥ垎锛宖ast 瑕佸厛璧颁竴姝?
    struct ListNode* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 妯″潡 3锛氫富鍑芥暟锛堥€掑綊鎷嗗垎 + 鍚堝苟锛?
struct ListNode* sortList(struct ListNode* head) {
    // 閫掑綊缁堟鏉′欢锛氶摼琛ㄤ负绌猴紝鎴栬€呭彧鍓?1 涓妭鐐癸紙1涓妭鐐瑰ぉ鐒舵槸鏈夊簭鐨勶級
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 1. 鎵句腑鐐?
    struct ListNode* mid = getMid(head);

    // 2. 鎷斿垁鏂〃锛佹媶鍒嗘垚 left 鍜?right 涓や釜鐙珛鐨勯摼琛?
    struct ListNode* rightHead = mid->next;
    mid->next = NULL; // 鏍稿績鏂紑鍔ㄤ綔

    // 3. 閫掑綊鎺掑ソ宸﹀崐杈?
    struct ListNode* left = sortList(head);
    // 4. 閫掑綊鎺掑ソ鍙冲崐杈?
    struct ListNode* right = sortList(rightHead);

    // 5. 灏嗘帓濂藉簭鐨勫乏杈瑰拰鍙宠竟鍚堝苟
    return mergeTwoLists(left, right);
}
