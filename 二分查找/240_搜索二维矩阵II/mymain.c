// 2026.8.10
#include <stdbool.h>
bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
    int i = 0, j = *matrixColSize - 1;
    while (i < matrixSize && j >= 0)
    {
        if (matrix[i][j] > target)
        {
            j--;
        }
        else if (matrix[i][j] < target)
        {
            i++;
        }
        else
        {
            return true;
        }
    }
    return false;
}