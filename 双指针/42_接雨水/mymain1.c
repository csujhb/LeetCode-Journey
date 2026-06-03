// 2026.6.3
#include <stdlib.h>
int trap(int *height, int heightSize)
{
    int *stack = (int *)malloc(heightSize * sizeof(int));
    int water = 0;
    int top = -1;
    for (int i = 0; i < heightSize; i++)
    {
        while (top != -1 && height[stack[top]] < height[i])
        {
            int bottom = height[stack[top--]];
            if (top == -1)
                break;
            int h = (height[i] < height[stack[top]] ? height[i] : height[stack[top]]) - bottom;
            int w = i - stack[top] - 1;
            water += w * h;
        }
        stack[++top] = i;
    }
    free(stack);
    return water;
}