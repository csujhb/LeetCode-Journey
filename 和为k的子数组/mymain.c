
#include <stdlib.h>

typedef struct HashEntry{
	int key;
	int count;
}HashEntry;

typedef struct HashTable {
	HashEntry* entry;
	unsigned int tablesize;
}HashTable;


HashTable* createHash(int tablesize) {
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	table->tablesize = tablesize;
	table->entry = (HashEntry*)calloc(table->tablesize, sizeof(HashEntry));
	return table;
}

unsigned int buildkey(int key, unsigned int size) {
	unsigned int tmp = (unsigned int)key;
	return  tmp % size;
}

void insertHash(HashTable* table, int key) {
	unsigned int idx = buildkey(key, table->tablesize);
	if (table->entry[idx].count == 0) {
		table->entry[idx].count = 1;
		table->entry[idx].key = key;
	}else if(table->entry[idx].count > 0) {
		while (table->entry[idx].key != key && table->entry[idx].count > 0) {
			idx = (idx + 1) % table->tablesize;
		}
		if (table->entry[idx].count == 0) {
			table->entry[idx].count = 1;
			table->entry[idx].key = key;
		}
		else if (table->entry[idx].key == key) {
			table->entry[idx].count++;
		}
	}
}

int getCount(HashTable* table, int key) {
	unsigned int idx = buildkey(key, table->tablesize);
	if (table->entry[idx].count == 0) {
		return 0;
	}
	while (table->entry[idx].key != key && table->entry[idx].count > 0) {
		idx = (idx + 1) % table->tablesize;
	}
	if (table->entry[idx].count == 0) {
		return 0;
	}
	else if (table->entry[idx].key == key) {
		return table->entry[idx].count;
	}
	//添加return -1;
}

void freeHash(HashTable* table) {
	free(table->entry);
	free(table);
}
int subarraySum(int* nums, int numsSize, int k) {
	if (numsSize == 1) {
		if (nums[0] == k) {
			return 1;
		}
		else {
			return 0;
		}
	}
	int arrcount = 0;
	int sum = 0;
	HashTable* table = (HashTable*)createHash(2 * numsSize + 1);
	insertHash(table, sum);
	for (int i = 0; i < numsSize; i++) {
		sum += nums[i];
		int target = k - sum;//应该是sum-k
		arrcount += getCount(table, target);
		insertHash(table, sum);
	}
	freeHash(table);
	return arrcount;
}
