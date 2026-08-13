#include <stdlib.h>

typedef struct
{
    int key;
    int count;
} HashTbl;

unsigned int hash(int key, int size)
{
    return (unsigned int)(key % size);
}

void hashInsert(HashTbl *tbl, int key, int size)
{
    unsigned idx = hash(key, size);
    while (tbl[idx].count)
    {
        if (tbl[idx].key == key)
        {
            tbl[idx].count++;
            return;
        }
        idx = (idx + 1) % size;
    }
    tbl[idx].count = 1;
    tbl[idx].key = key;
}

int getCount(HashTbl *tbl, int key, int size)
{
    unsigned idx = hash(key, size);
    while (tbl[idx].count)
    {
        if (tbl[idx].key == key)
            return tbl[idx].count;
        idx = (idx + 1) % size;
    }
    return 0;
}

int subarraySum(int *nums, int numsSize, int k)
{
    int size = 2 * numsSize + 1;
    HashTbl *tbl = (HashTbl *)calloc(size, sizeof(HashTbl));

    hashInsert(tbl, 0, size);
    int prefix = 0;
    int res = 0;
    for (int i = 0; i < numsSize; i++)
    {
        prefix += nums[i];
        int target = prefix - k;
        res += getCount(tbl, target, size);
        hashInsert(tbl, prefix, size);
    }

    free(tbl);
    return res;
}
// 优化版本

#include <stdlib.h>

typedef struct
{
    int key;
    int count;
} HashTbl;

unsigned int hash(int key, int size)
{
    // 负数key兼容：保证哈希下标非负
    return (unsigned int)((key % size + size) % size);
}

void hashInsert(HashTbl *tbl, int key, int size)
{
    unsigned idx = hash(key, size);
    while (tbl[idx].count)
    {
        if (tbl[idx].key == key)
        {
            tbl[idx].count++;
            return;
        }
        idx = (idx + 1) % size;
    }
    tbl[idx].count = 1;
    tbl[idx].key = key;
}

int getCount(HashTbl *tbl, int key, int size)
{
    unsigned idx = hash(key, size);
    while (tbl[idx].count)
    {
        if (tbl[idx].key == key)
            return tbl[idx].count;
        idx = (idx + 1) % size;
    }
    return 0;
}

int subarraySum(int *nums, int numsSize, int k)
{
    int size = 2 * numsSize + 1;
    HashTbl *tbl = (HashTbl *)calloc(size, sizeof(HashTbl));

    hashInsert(tbl, 0, size);
    int prefix = 0;
    int res = 0;
    for (int i = 0; i < numsSize; i++)
    {
        prefix += nums[i];
        int target = prefix - k;
        res += getCount(tbl, target, size);
        hashInsert(tbl, prefix, size);
    }
    free(tbl);
    return res;
}