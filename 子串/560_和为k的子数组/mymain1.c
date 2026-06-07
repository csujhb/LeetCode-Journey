// 2026.6.6

// #include <stdlib.h>

// #define HASH_SIZE 20001
// typedef struct
// {
//     int key;
//     int count;
// } HashTbl;

// unsigned int hash(int value)
// {
//     return ((unsigned int)value % HASH_SIZE);
// }

// void hashInsert(HashTbl *tbl, int key)
// {
//     unsigned int idx = hash(key);
//     while (tbl[idx].count > 0)
//     {
//         if (tbl[idx].key == key)
//         {
//             tbl[idx].count++;
//             return;
//         }

//         idx = (idx + 1) % HASH_SIZE;
//     }
//     tbl[idx].count = 1;
//     tbl[idx].key = key;
// }

// unsigned int getCount(HashTbl *tbl, int key)
// {
//     unsigned int idx = hash(key);
//     while (tbl[idx].count > 0)
//     {
//         if (tbl[idx].key == key)
//             return tbl[idx].count;
//         idx = (idx + 1) % HASH_SIZE;
//     }
//     return 0;
// }

// int subarraySum(int *nums, int numsSize, int k)
// {
//     HashTbl *tbl = (HashTbl *)malloc(HASH_SIZE * sizeof(HashTbl));
//     int sum = 0;
//     int res = 0;
//     hashInsert(tbl, sum);
//     for (int i = 0; i < numsSize; i++)
//     {
//         sum += nums[i];
//         res += getCount(tbl, sum - k);
//         hashInsert(tbl, sum);
//     }
//     free(tbl);
//     return res;
// }

#include <stdlib.h>

typedef struct
{
    int key;
    int count;
} HashTbl;

unsigned int hash(int value, int size)
{
    return ((unsigned int)value % size);
}

void hashInsert(HashTbl *tbl, int key, int size)
{
    unsigned int idx = hash(key, size);
    while (tbl[idx].count > 0)
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

unsigned int getCount(HashTbl *tbl, int key, int size)
{
    unsigned int idx = hash(key, size);
    while (tbl[idx].count > 0)
    {
        if (tbl[idx].key == key)
            return tbl[idx].count;
        idx = (idx + 1) % size;
    }
    return 0;
}

int subarraySum(int *nums, int numsSize, int k)
{

    int hashsize = 2 * numsSize + 1;
    HashTbl *tbl = (HashTbl *)malloc(hashsize * sizeof(HashTbl));
    int sum = 0;
    int res = 0;
    hashInsert(tbl, sum, hashsize);
    for (int i = 0; i < numsSize; i++)
    {
        sum += nums[i];
        res += getCount(tbl, sum - k, hashsize);
        hashInsert(tbl, sum, hashsize);
    }
    free(tbl);
    return res;
}