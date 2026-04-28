#include <stdlib.h>
#define MAX_NUM 1000
void bubblesort(int *arr,int length)
{
    int i=0;
    int j=0;
    for(i=0;i<length;i++)
    {
        for(j=i+1;j<length-i+1;j++)
        {
            if(arr[i]>arr[j])
            {
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }

}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    bubblesort(nums,numsSize);
    int i=0;
    int left=0;
    int sum=0;
    int right=numsSize-1;
    *returnColumnSizes = (int*)malloc(MAX_NUM * sizeof(int));
    int** result = (int**)malloc(*returnSize * sizeof(int*));
    for(;i<numsSize-2;i++)
    {

        while(i>0&&nums[i]==nums[i-1]) i++;
        left=i+1;
        right=numsSize-1;
        
        while(left<right)
        {
             sum=nums[i]+nums[left]+nums[right];
            if(sum>0)
            {
                right--;
            }else if(sum<0)
            {
                left++;
            }else{
                *returnColumnSizes[*returnSize]=3;
                result[*returnSize][0]=nums[i];
                result[*returnSize][1]=nums[left];
                result[*returnSize][2]=nums[right];
                (*returnSize)++;
            }
        }
    }
    return result;
}
