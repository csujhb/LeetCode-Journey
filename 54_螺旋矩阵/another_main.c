/*
方法2：方向模拟 + visited 标记

按照固定方向顺序走：

右
下
左
上

每走一步前判断：

下一个位置是否越界
是否已经访问过

如果不能走，就换方向。

为了知道某个位置是否访问过，需要一个 visited 数组。

时间复杂度：O(m * n)
空间复杂度：O(m * n)
因为用了 visited
*/

#include <stdlib.h>
#include <stdbool.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int total = rows * cols;

    int* ans = (int*)malloc(sizeof(int) * total);
    *returnSize = total;

    // visited 数组，开成一维更方便
    bool* visited = (bool*)calloc(total, sizeof(bool));

    // 方向数组：右、下、左、上
    int dr[4] = { 0, 1, 0, -1 };
    int dc[4] = { 1, 0, -1, 0 };

    int row = 0, col = 0, dir = 0;

    for (int k = 0; k < total; k++) {
        ans[k] = matrix[row][col];
        visited[row * cols + col] = true;

        int nextRow = row + dr[dir];
        int nextCol = col + dc[dir];

        // 越界或已访问，则转向
        if (nextRow < 0 || nextRow >= rows ||
            nextCol < 0 || nextCol >= cols ||
            visited[nextRow * cols + nextCol]) {
            dir = (dir + 1) % 4;
            nextRow = row + dr[dir];
            nextCol = col + dc[dir];
        }

        row = nextRow;
        col = nextCol;
    }

    free(visited);
    return ans;
}
