// 2026.8.5
#include <stdbool.h>
bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
    int len = matrixSize * matrixColSize[0];
    int left = 0;
    int right = len - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int row = mid / matrixColSize[0];
        int col = mid % matrixColSize[0];
        if (matrix[row][col] > target)
            right = mid - 1;
        else if (matrix[row][col] < target)
            left = mid + 1;
        else
            return true;
    }
    return false;
}