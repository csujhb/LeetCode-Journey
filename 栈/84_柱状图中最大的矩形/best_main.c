#include <stdlib.h>
int largestRectangleArea(int *heights, int n) {
    int *stack = malloc((n+1)*sizeof(int));
    int top = -1, maxArea = 0;
    for (int i = 0; i <= n; i++) {
        int curH = (i == n) ? 0 : heights[i];
        while (top != -1 && curH < heights[stack[top]]) {
            int h = heights[stack[top--]];
            int left = (top == -1) ? 0 : stack[top] + 1;
            int area = h * (i - left);
            if (area > maxArea) maxArea = area;
        }
        stack[++top] = i;
    }
    free(stack);
    return maxArea;
}