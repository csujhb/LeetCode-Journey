#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct HashNode {
    char* key;              // 频次数组拼出来的字符串
    int groupIndex;         // 对应分组下标
    struct HashNode* next;
} HashNode;

typedef struct {
    char** words;           // 当前组里的字符串
    int size;               // 当前组元素个数
    int capacity;           // 当前组容量
} Group;

/* 字符串复制 */
static char* strDup(const char* s) {
    int len = (int)strlen(s);
    char* p = (char*)malloc(len + 1);
    strcpy(p, s);
    return p;
}

/* 简单字符串哈希函数（djb2） */
static unsigned int hashString(const char* s) {
    unsigned int hash = 5381;
    while (*s) {
        hash = hash * 33 + (unsigned char)(*s);
        s++;
    }
    return hash;
}

/* 根据字符串构造 key：26个字母频次 */
static void buildKey(const char* s, char* key) {
    int count[26] = { 0 };
    while (*s) {
        count[*s - 'a']++;
        s++;
    }

    char* p = key;
    for (int i = 0; i < 26; i++) {
        p += sprintf(p, "#%d", count[i]);
    }
}

/* 在哈希表中查找 key 对应的 groupIndex，不存在返回 -1 */
static int findGroup(HashNode** table, int tableSize, const char* key) {
    unsigned int idx = hashString(key) % tableSize;
    HashNode* cur = table[idx];
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            return cur->groupIndex;
        }
        cur = cur->next;
    }
    return -1;
}

/* 插入 key -> groupIndex */
static void insertGroup(HashNode** table, int tableSize, const char* key, int groupIndex) {
    unsigned int idx = hashString(key) % tableSize;

    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = strDup(key);
    node->groupIndex = groupIndex;
    node->next = table[idx];
    table[idx] = node;
}

/* 释放哈希表 */
static void freeHashTable(HashNode** table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        HashNode* cur = table[i];
        while (cur) {
            HashNode* tmp = cur;
            cur = cur->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(table);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced.
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    if (strsSize == 0) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    int tableSize = strsSize * 2 + 1;
    HashNode** table = (HashNode**)calloc(tableSize, sizeof(HashNode*));

    /* 最多 strsSize 组 */
    Group* groups = (Group*)malloc(sizeof(Group) * strsSize);
    int groupCount = 0;

    for (int i = 0; i < strsSize; i++) {
        char key[128];
        buildKey(strs[i], key);

        int idx = findGroup(table, tableSize, key);

        if (idx == -1) {
            /* 新建一组 */
            idx = groupCount++;
            groups[idx].size = 0;
            groups[idx].capacity = 4;
            groups[idx].words = (char**)malloc(sizeof(char*) * groups[idx].capacity);

            insertGroup(table, tableSize, key, idx);
        }

        /* 把当前字符串放入对应组 */
        if (groups[idx].size == groups[idx].capacity) {
            groups[idx].capacity *= 2;
            groups[idx].words = (char**)realloc(groups[idx].words,
                sizeof(char*) * groups[idx].capacity);
        }

        groups[idx].words[groups[idx].size++] = strs[i];
    }

    /* 构造返回结果 */
    char*** result = (char***)malloc(sizeof(char**) * groupCount);
    *returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);

    for (int i = 0; i < groupCount; i++) {
        result[i] = groups[i].words;
        (*returnColumnSizes)[i] = groups[i].size;
    }

    *returnSize = groupCount;

    free(groups);
    freeHashTable(table, tableSize);

    return result;
}
