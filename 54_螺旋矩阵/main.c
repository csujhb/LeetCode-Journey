/*
方法1：边界收缩法
把矩阵看成一层一层的“圈”。

每一圈按下面顺序遍历：

从左到右遍历上边界
从上到下遍历右边界
从右到左遍历下边界
从下到上遍历左边界

遍历完一圈后，边界收缩：

top++
bottom--
left++
right--

直到边界交错为止。


时间复杂度：O(m * n)
空间复杂度：O(1)
*/
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    // 判空
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int total = rows * cols;

    int* ans = (int*)malloc(sizeof(int) * total);
    *returnSize = total;

    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int k = 0;

    while (top <= bottom && left <= right) {
        // 1. 从左到右
        for (int j = left; j <= right; j++) {
            ans[k++] = matrix[top][j];
        }
        top++;

        // 2. 从上到下
        for (int i = top; i <= bottom; i++) {
            ans[k++] = matrix[i][right];
        }
        right--;

        // 3. 从右到左
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                ans[k++] = matrix[bottom][j];
            }
            bottom--;
        }

        // 4. 从下到上
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                ans[k++] = matrix[i][left];
            }
            left++;
        }
    }

    return ans;
}
