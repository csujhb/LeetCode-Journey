#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint16_t Key[26];

typedef struct HashEntry {
	Key key;
	int groupIndex;
	int isused;
}HashEntry;

typedef struct HashTable {
	HashEntry* entry;
	int capacity;
	int size;
}HashTable;

typedef struct Group {
	char** str;
	int capacity;
	int size;
}Group;



unsigned int hashInt(Key key, int capacity) {
	unsigned int hash = 5381;
	const unsigned char* p = (const unsigned char*)key;
	for (int i = 0; i < 26 * sizeof(uint16_t); i++) {
		hash = ((hash << 5) + hash) ^ p[i];
	}
	return hash%capacity;
}

void buildKey(const char* s, Key key) {
	int count[26] = { 0 };
	while (*s) {
		count[*s - 'a']++;
		s++;
	}
	for (int i = 0; i < 26; i++)
		key[i] = count[i];//应强制转换uint16_t
}

HashTable* createHashtable(int capacity)
{
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	table->capacity = capacity;
	table->size = 0;
	table->entry = (HashEntry*)calloc(table->capacity, sizeof(HashEntry));
	return table;
}

int getGroup(HashTable* table, Key key) {
	unsigned int idx = hashInt(key, table->capacity);
	while (table->entry[idx].isused) {
		if (memcmp(table->entry[idx].key, key, sizeof(key))) {//应为sizeof(Key)
			return table->entry[idx].groupIndex;
		}
		idx = (idx + 1) % table->capacity;
	}
	return -1;
}

void insertHash(HashTable* table, Key key, int groupIndex) {
	unsigned int idx = hashInt(key, table->capacity);
	while (table->entry[idx].isused) idx = (idx + 1) % table->capacity;
	table->entry[idx].isused = 1;
	table->entry[idx].groupIndex = groupIndex;
	memcpy(table->entry[idx].key, key, sizeof(key));//应为sizeof(Key)
	table->size++;
}

static void freeHashTable(HashTable* table) {
	free(table->entry);
	free(table);
}
void expandHashtable(HashTable** table, int newCapacity) {
	HashTable* old = *table;
	HashTable* new = createHashtable(newCapacity);
	for (int i = 0; i < old->capacity; i++) {
		if (old->entry[i].isused) {
			insertHash(new, old->entry[i].key, old->entry[i].groupIndex);
		}		
	}
	freeHashTable(old);
	*table = new;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
	*returnSize = 0;
	if (strsSize == 0) {
		*returnColumnSizes = NULL;
		return NULL;
	}
	//char*** result = (char***)calloc(strsSize, sizeof(char**));
	int groupCount = 0;
	Group*group= (Group*)calloc(strsSize, sizeof(Group));
	//*returnColumnSizes= (int*)calloc(strsSize, sizeof(int));//result和*returnColumnSizes应在确定组数后用groupCount定义数量
	int capacity = 2 * strsSize + 1;
	HashTable* table = createHashtable(capacity);
	for (int i = 0; i < strsSize; i++) {
		Key key;
		buildKey(strs[i], key);
		int groupIndex = getGroup(table, key);
		if (groupIndex == -1)
		{
			groupIndex = groupCount++;
			group[groupIndex].capacity = 4;
			group[groupIndex].size = 0;
			group[groupIndex].str = (char**)malloc(group[groupIndex].capacity * sizeof(char*));
			if (table->capacity * 3 < table->size * 4) {
				table->capacity = table->capacity * 2 + 1;
				expandHashtable(&table, table->capacity);
			}
			insertHash(table, key, groupIndex);
		}
		Group* tmp = &group[groupIndex];
		if (tmp->capacity == tmp->size) {
			tmp->capacity = tmp->capacity * 2;
			tmp->str = (char**)realloc(tmp->str, sizeof(char*) * tmp->capacity);
		}
		tmp->str[tmp->size++] = strs[i];
	}
	char*** result = (char***)malloc(sizeof(char**) * groupCount);
	*returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);
	for (int i = 0; i < groupCount; i++) {
		(*returnColumnSizes)[i] = group[i].size;
		result[i] = group[i].str;
	}
	//没加上*returnSize = groupCount;
	freeHashTable(table);
	free(group);
	return result;
}
