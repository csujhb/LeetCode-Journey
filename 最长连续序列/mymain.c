#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node* next;
}Node;

unsigned int hash(int key, int arrsize)
{
	return ((unsigned int)key * 2654435761u) % arrsize;
}

int isContain(Node** table, int size, int key)
{
	unsigned int idx = hash(key, size);
	Node* cur = table[idx];
	while (cur) {
		if (cur->key == key) {
			return 1;
		}
		cur=cur->next;
	}
	return 0;
}

void hash_insert(Node** table, int size, int key)
{
	unsigned int idx = hash(key, size);
	Node* cur = table[idx];
	while (cur) {
		if (cur->key == key) {
			return;
		}
		cur = cur->next;
	}
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->next = table[idx];
	tmp->key = key;
	table[idx] = tmp;
}

void hash_free(Node** table, int size)
{
	Node* cur = NULL;
	for (int i = 0; i < size; i++) {
		cur = table[i];
		while (cur) {
			Node* tmp = cur;
			cur = cur->next;
			free(tmp);
		}

	}
	free(table);
}


int longestConsecutive(int* nums, int numsSize) {
	if (numsSize <= 1) return numsSize;
	
	int maxLen = 0;
	int hashtabl_size = 2 * numsSize + 1;
	Node** hash_table = (Node**)calloc(hashtabl_size, sizeof(Node*));
	for (int i = 0; i < numsSize; i++)
	{
		hash_insert(hash_table, hashtabl_size, nums[i]);
	}
	for (int i = 0; i < hashtabl_size; i++)
	{
		Node* cur = hash_table[i];
		while (cur) {
			int x = cur->key;
			if (!isContain(hash_table, hashtabl_size, x - 1))
			{
				int y = x;
				int len = 1;
				while (isContain(hash_table, hashtabl_size, y + 1)) {
					y++;
					len++;
				}
				if (maxLen < len) maxLen = len;
			}
			//这里没指向下一个节点，导致超时
		}
	}
	//这里没释放哈希表
	return maxLen;
}
