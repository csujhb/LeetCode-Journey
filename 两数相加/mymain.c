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

struct ListNode* createNode(int val) {
	struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
	node->next = NULL;
	node->val = val;
	return node;
}
/*
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	int plus = 0;
	struct ListNode temp = { -1,NULL };
	struct ListNode* head = &temp;
	struct ListNode* cur = head;
	while (l1 || l2 || plus) {
		int sum = 0;
		if (l1) {
			sum += l1->val;
			l1 = l1->next;
		}
		if (l2) {
			sum += l2->val;
			l2 = l2->next;
		}
		sum += plus;
		plus = sum / 10;
		struct ListNode* node = createNode(sum % 10);
		cur->next = node;
		cur = cur->next;
	}
	return head->next;
}
*/
//更精简版本的
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	int plus = 0;
	struct ListNode temp = { -1, NULL };
	struct ListNode* cur = &temp;

	while (l1 || l2 || plus) {
		// 直接把进位作为初始值
		int sum = plus;

		if (l1) { sum += l1->val; l1 = l1->next; }
		if (l2) { sum += l2->val; l2 = l2->next; }

		plus = sum / 10;
		// 直接内联函数调用，省去定义临时指针 node
		cur->next = createNode(sum % 10);
		cur = cur->next;
	}

	return temp.next;
}
