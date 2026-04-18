
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int *res=(int*)calloc(temperaturesSize,sizeof(int));
    int *stack=(int*)malloc(temperaturesSize*sizeof(int));
    * returnSize=temperaturesSize;
    int top=-1;
    for(int i=0;i<temperaturesSize;i++){
        while(top!=-1){
            if(temperatures[i]>temperatures[stack[top]]){
                res[stack[top]]=i-stack[top];
                top--;
            }else{
                break;
            }            
        }
         stack[++top]=i;
    }
    free(stack);
    return res;
}