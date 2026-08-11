// 2026.8.10
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
typedef uint16_t Key[26];
typedef struct
{
    Key key;
    int groupIndex;
    int isused;
} HashEntry;

typedef struct
{
    HashEntry *entry;
    int size;
    int capacity;
} HashTbl;

typedef struct
{
    char **str;
    int capacity;
    int size;
} Group;

unsigned int hashInt(Key key, int capacity)
{
    unsigned int hash = 5381;
    const unsigned char *p = (const unsigned char *)key;
    for (int i = 0; i < 26 * sizeof(uint16_t); i++)
    {
        hash = ((hash << 5) + hash) ^ p[i];
    }
    return hash % capacity;
}

void buildKey(Key key, char *s)
{
    int count[26] = {0};
    while (*s)
    {
        count[*s - 'a']++;
        s++;
    }
    for (int i = 0; i < 26; i++)
    {
        key[i] = (uint16_t)count[i];
    }
}

void hashInsert(HashTbl *tbl, Key key, int groupIndex)
{
    unsigned int idx = hashInt(key, tbl->capacity);
    while (tbl->entry[idx].isused)
        idx = (idx + 1) % tbl->capacity;
    tbl->entry[idx].isused = 1;
    tbl->entry[idx].groupIndex = groupIndex;
    memcpy(tbl->entry[idx].key, key, sizeof(Key));
    tbl->size++;
}

HashTbl *createHash(int capacity)
{
    HashTbl *table = (HashTbl *)malloc(sizeof(HashTbl));
    table->capacity = capacity;
    table->size = 0;
    table->entry = (HashEntry *)calloc(table->capacity, sizeof(HashEntry));
    return table;
}

int getGroup(HashTbl *table, Key key)
{
    unsigned int idx = hashInt(key, table->capacity);
    while (table->entry[idx].isused)
    {
        if (memcmp(table->entry[idx].key, key, sizeof(Key)) == 0)
        {
            return table->entry[idx].groupIndex;
        }
        idx = (idx + 1) % table->capacity;
    }
    return -1;
}

static void freeHashTable(HashTbl *table)
{
    free(table->entry);
    free(table);
}

void expandHashtable(HashTbl **table, int newCapacity)
{
    HashTbl *old = *table;
    HashTbl *new = createHash(newCapacity);
    for (int i = 0; i < old->capacity; i++)
    {
        if (old->entry[i].isused)
        {
            hashInsert(new, old->entry[i].key, old->entry[i].groupIndex);
        }
    }
    freeHashTable(old);
    *table = new;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 0;
    if (strsSize == 0)
    {
        *returnColumnSizes = NULL;
        return NULL;
    }
    Group *group = (Group *)malloc(sizeof(Group) * strsSize);
    int capacity = 2 * strsSize + 1;
    int groupCount = 0;
    HashTbl *table = createHash(capacity);
    for (int i = 0; i < strsSize; i++)
    {
        Key key;
        buildKey(key, strs[i]);
        int groupIdx = getGroup(table, key);
        if (groupIdx == -1)
        {
            groupIdx = groupCount++;
            group[groupIdx].capacity = 4;
            group[groupIdx].size = 0;
            group[groupIdx].str = (char **)malloc(group[groupIdx].capacity * sizeof(char *));
            if (table->capacity * 3 < table->size * 4)
            {
                table->capacity = table->capacity * 2 + 1;
                expandHashtable(&table, table->capacity);
            }
            hashInsert(table, key, groupIdx);
        }
        Group *tmp = &group[groupIdx];
        if (tmp->capacity == tmp->size)
        {
            tmp->capacity = tmp->capacity * 2;
            tmp->str = (char **)realloc(tmp->str, sizeof(char *) * tmp->capacity);
        }
        tmp->str[tmp->size++] = strs[i];
    }
    char ***result = (char ***)malloc(sizeof(char **) * groupCount);
    *returnColumnSizes = (int *)malloc(sizeof(int) * groupCount);
    for (int i = 0; i < groupCount; i++)
    {
        (*returnColumnSizes)[i] = group[i].size;
        result[i] = group[i].str;
    }
    *returnSize = groupCount;
    freeHashTable(table);
    free(group);
    return result;
}