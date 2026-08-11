#include <stdlib.h>
int largestRectangleArea(int *heights, int heightsSize)
{
    int *stack = (int *)malloc(sizeof(int) * (heightsSize + 1));
    int top = -1;
    int max = 0;
    for (int i = 0; i <= heightsSize; i++)
    {
        int curH = (i == heightsSize) ? 0 : heights[i];
        while (top != -1 && curH < heights[stack[top]])
        {
            int h = heights[stack[top--]];
            int left = (top == -1) ? -1 : stack[top];
            int area = h * (i - left - 1);
            if (area > max)
                max = area;
        }
        stack[++top] = i;
    }
    free(stack);
    return max;
}