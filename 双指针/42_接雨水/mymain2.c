// 2026.8.3
#include <stdlib.h>
#define MIN(a, b) ((a) > (b) ? (b) : (a))
int trap(int *height, int heightSize)
{
    int *stack = (int *)malloc(heightSize * sizeof(int));
    int top = -1;
    int water = 0;
    for (int i = 0; i < heightSize; i++)
    {
        while (top != -1 && height[stack[top]] < height[i])
        {
            int bottom = height[stack[top--]];
            if (top == -1)
                break;
            int wid = i - stack[top] - 1;
            int h = MIN(height[i], height[stack[top]]) - bottom;
            water += wid * h;
        }
        stack[++top] = i;
    }
    free(stack);
    return water;
}