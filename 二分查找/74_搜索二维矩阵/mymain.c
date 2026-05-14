// 可以但复杂
#include <stdbool.h>

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize,
                  int target)
{
    int col = *matrixColSize;
    if (target < matrix[0][0] || target > matrix[matrixSize - 1][col - 1])
        return false;
    int row = 0;
    while (row < matrixSize && matrix[row][0] < target)
    {
        row++;
    }
    if (row < matrixSize && matrix[row][0] == target)
        return true;
    int left = 0;
    int right = col - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (matrix[row - 1][mid] > target)
        {
            right = mid - 1;
        }
        else if (matrix[row - 1][mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            return true;
        }
    }
    return false;
}