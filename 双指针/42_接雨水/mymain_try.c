int trap(int *height, int heightSize)
{
    if (heightSize == 0)
        return 0;

    int *stack = (int *)malloc(sizeof(int) * heightSize);
    int top = -1;
    int water = 0;

    for (int current = 0; current < heightSize; current++)
    {
        while (top != -1 && height[current] > height[stack[top]])
        {
            int bottom = stack[top--];
            if (top == -1)
                break;

            int left = stack[top];
            int w = current - left - 1;
            int h = (height[left] < height[current] ? height[left] : height[current]) - height[bottom];
            water += w * h;
        }
        stack[++top] = current; // 入栈
    }

    free(stack);
    return water;
}