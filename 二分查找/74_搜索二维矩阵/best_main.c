#include <stdbool.h>

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
    // 基础边界检查（LeetCode 多数情况不需要，但写上是好习惯）
    if (matrixSize == 0 || matrixColSize[0] == 0)
    {
        return false;
    }

    int m = matrixSize;
    int n = matrixColSize[0]; // 获取列数

    // 逻辑上一维数组的左右边界
    int left = 0;
    int right = m * n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        // 将一维索引 mid 转换为二维矩阵的具体坐标
        int midValue = matrix[mid / n][mid % n];

        if (midValue == target)
        {
            return true; // 找到了
        }
        else if (midValue < target)
        {
            left = mid + 1; // 目标在右半边
        }
        else
        {
            right = mid - 1; // 目标在左半边
        }
    }

    return false; // 遍历完都没找到
}