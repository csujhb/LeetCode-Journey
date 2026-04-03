#include <stdlib.h>

typedef struct {
    int key;
    int count;
} HashEntry;

typedef struct {
    HashEntry* entry;
    unsigned int tableSize;
} HashTable;

static unsigned int hashFunc(int key, unsigned int size) {
    int idx = key % (int)size;
    if (idx < 0) idx += size;
    return (unsigned int)idx;
}

static HashTable* createHash(unsigned int tableSize) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) return NULL;

    table->tableSize = tableSize;
    table->entry = (HashEntry*)calloc(tableSize, sizeof(HashEntry));
    if (table->entry == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

static void insertHash(HashTable* table, int key) {
    unsigned int idx = hashFunc(key, table->tableSize);

    while (table->entry[idx].count > 0 && table->entry[idx].key != key) {
        idx = (idx + 1) % table->tableSize;
    }

    if (table->entry[idx].count == 0) {
        table->entry[idx].key = key;
        table->entry[idx].count = 1;
    }
    else {
        table->entry[idx].count++;
    }
}

static int getCount(HashTable* table, int key) {
    unsigned int idx = hashFunc(key, table->tableSize);

    while (table->entry[idx].count > 0) {
        if (table->entry[idx].key == key) {
            return table->entry[idx].count;
        }
        idx = (idx + 1) % table->tableSize;
    }

    return 0;
}

static void freeHash(HashTable* table) {
    if (table) {
        free(table->entry);
        free(table);
    }
}

int subarraySum(int* nums, int numsSize, int k) {
    int count = 0;
    int prefixSum = 0;

    HashTable* table = createHash(2 * numsSize + 1);
    if (table == NULL) return 0;

    insertHash(table, 0);

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        count += getCount(table, prefixSum - k);
        insertHash(table, prefixSum);
    }

    freeHash(table);
    return count;
}
