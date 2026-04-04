#include <stdlib.h>
#include <stdio.h>
#define HASH_SIZE 20000
typedef struct{
    int key;//鍏冪礌鍊?
    int value;//鏁扮粍涓嬫爣
    int isused;//1 宸插瓨鍦?0 涓嶅瓨鍦?
}hashmap;

int hash(int value)
{
    return ((value>0)?value:(-value))%HASH_SIZE;
}

int *twosum(int *nums,int target,int numsize,int*returnNum)
{
    *returnNum=2;
    hashmap *hash_table=( hashmap *)calloc(HASH_SIZE,sizeof (hashmap));
    int *result=(int *)malloc(2*sizeof(int));

    for (int i = 0; i < numsize; i++)
    {
        int targetNum=target-nums[i];
        int targetIdx=hash(targetNum);
        while(hash_table[targetIdx].isused)
        {
            if(targetNum==hash_table[targetIdx].key)
            {
                result[1]=i;
                result[0]=hash_table[targetIdx].value;
                free(hash_table);
                return result;
            }
            targetIdx=(targetIdx+1)%HASH_SIZE;
        }
        int temp_idx=hash(nums[i]);
        while(hash_table[temp_idx].isused)
        {
            temp_idx=(temp_idx+1)%HASH_SIZE;
        }
        hash_table[temp_idx].isused=1;
        hash_table[temp_idx].key=nums[i];
        hash_table[temp_idx].value=i;
    }
    *returnNum=0;
    free(hash_table);
    return NULL;
}
/*
int main() {
    // 娴嬭瘯鐢ㄤ緥1锛氬父瑙勬儏鍐?
    int nums[] = {2, 7, 11, 15};
    int target = 22;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    int *result = twosum(nums,  target,numsSize, &returnSize);
    if (result != NULL && returnSize == 2) {
        printf("xiabiao:%d, %d\n", result[0], result[1]);  // 杈撳嚭锛?, 1
        free(result);  // 閲婃斁缁撴灉鏁扮粍锛堣皟鐢ㄨ€呰礋璐ｏ級
    } else {
        printf("鏈壘鍒扮鍚堟潯浠剁殑涓や釜鏁癨n");
    }

    return 0;
}*/
