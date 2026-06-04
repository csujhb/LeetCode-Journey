// 2026.06.04算法错误
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize)
{
    int *res = (int *)malloc(matrixSize * (*matrixColSize) * sizeof(int));
    *returnSize = 0;
    int top = 0;
    int bottom = matrixSize - 1;
    int left = 0;
    int right = *matrixColSize - 1;

    while (top <= bottom && left <= right)
    {
        int x = top, y = left;
        while (y <= right)
        {
            res[(*returnSize)++] = matrix[top][y];
            y++;
        }
        top++;
        x = top;
        while (x <= bottom)
        {
            res[(*returnSize)++] = matrix[x][right];
            x++;
        }
        right--;
        y = right;
        if (top <= bottom)
        {
            while (y >= left)
            {
                res[(*returnSize)++] = matrix[bottom][y];
                y--;
            }
            bottom--;
        }
        x = bottom;
        if (left <= right)
        {
            while (x >= top)
            {
                res[(*returnSize)++] = matrix[x][left];
                x--;
            }
            left++;
        }
        return res;
    }