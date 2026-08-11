// 2026.8.3
#include <stdlib.h>
#define HASH_SIZE 10001
typedef struct
{
    int key;
    int value;
    int isused;
} HashTbl;

unsigned int hashInt(int key)
{
    return ((unsigned int)key) % HASH_SIZE;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    HashTbl *table = (HashTbl *)calloc(HASH_SIZE, sizeof(HashTbl));
    int *res = (int *)malloc(2 * sizeof(int));
    *returnSize = 2;
    for (int i = 0; i < numsSize; i++)
    {
        int targetNum = target - nums[i];
        unsigned int targetIdx = hashInt(targetNum);
        while (table[targetIdx].isused)
        {
            if (targetNum == table[targetIdx].key)
            {
                res[1] = i;
                res[0] = table[targetIdx].value;
                free(table);
                return res;
            }
            targetIdx = (targetIdx + 1) % HASH_SIZE;
        }
        unsigned int temp_idx = hashInt(nums[i]);
        while (table[temp_idx].isused)
        {
            temp_idx = (temp_idx + 1) % HASH_SIZE;
        }
        table[temp_idx].isused = 1;
        table[temp_idx].key = nums[i];
        table[temp_idx].value = i;
    }
    free(table);
    free(res);
    *returnSize = 0;
    return NULL;
}