
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *dailyTemperatures(int *temperatures, int temperaturesSize, int *returnSize)
{
    int *res = (int *)calloc(temperaturesSize, sizeof(int));
    int *stack = (int *)malloc(temperaturesSize * sizeof(int));
    *returnSize = temperaturesSize;
    int top = -1;
    for (int i = 0; i < temperaturesSize; i++)
    {
        // 直接把判断条件融合，代码更精简、更符合 C 语言习惯
        while (top > -1 && temperatures[i] > temperatures[stack[top]])
        {
            res[stack[top]] = i - stack[top];
            top--;
        }
        stack[++top] = i;
    }
    free(stack);
    return res;
}