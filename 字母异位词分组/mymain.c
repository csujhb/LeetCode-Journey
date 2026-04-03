#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int key;
	struct Node* next;
}Node;

int hash(int key,int size)
{
	return (key - 97)%size;
}

void hash_insert(Node** table, int size, int key) {
	int idx = hash(key,size);
	Node* cur = table[idx];
	while (cur) {
		if (cur->key == key) {
			return;
		}
		cur = cur->next;
	}
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->key = key;
	tmp->next = table[idx];
	table[idx] = tmp;
}

void hash_free(Node** table, int size) {
	for (int i = 0; i < size; i++) {
		Node* cur = table[i];
		while (cur)
		{
			Node* tmp = cur;
			cur = cur->next;
			free(tmp);
		}
	}
	free(table);
}

int isContain(Node** table, int size, int key) {
	int idx = hash(key, size);
	Node* cur = table[idx];
	while (cur) {
		if (cur->key == key) {
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
/*
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
	int max_num = strsSize;
	int** returnColumnSizes = (int**)calloc(max_num, sizeof(int*));
	char*** result= (char***)calloc(max_num, sizeof(char**));
	if (strsSize == 1)
	{
		*returnSize = 1;
		(*returnColumnSizes)[0] = strlen(strs[0]);
		(*result)[0] = strs[0];
		return result;
	}
	for (int i = 0; i < strsSize; i++)
	{

	}

}
*/