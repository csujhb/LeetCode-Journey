// 2026.06.04
#include <stdbool.h>
bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int x = 0;
    int y = cols - 1;
    while (x >= 0 && x < rows && y >= 0 && y < cols)
    {
        if (matrix[x][y] > target)
            y--;
        else if (matrix[x][y] < target)
            x++;
        else
            return true;
    }
    return false;
}