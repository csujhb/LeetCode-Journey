#include <stdlib.h>
// 深度优先搜索：负责把当前相连的陆地全部"沉没"（置为 '0'）
void dfs(char **grid, int row, int col, int rowmax, int colmax)
{
    // 边界条件判断：越界或者是水（'0'），直接返回
    if (row < 0 || row >= rowmax || col < 0 || col >= colmax || grid[row][col] == '0')
    {
        return;
    }

    // 核心：将当前陆地标记为水（'0'），避免后续重复遍历
    grid[row][col] = '0';

    // 向上下左右四个方向继续搜索
    dfs(grid, row + 1, col, rowmax, colmax); // 下
    dfs(grid, row - 1, col, rowmax, colmax); // 上
    dfs(grid, row, col + 1, rowmax, colmax); // 右
    dfs(grid, row, col - 1, rowmax, colmax); // 左
}

int numIslands(char **grid, int gridSize, int *gridColSize)
{
    // 异常输入处理
    if (grid == NULL || gridSize == 0 || gridColSize == NULL)
    {
        return 0;
    }

    int count = 0;
    int colSize = gridColSize[0]; // 假设每一行的列数相同

    // 遍历整个网格
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            // 如果遇到 '1'，说明发现了一个新岛屿
            if (grid[i][j] == '1')
            {
                count++; // 岛屿数量加 1
                // 启动 DFS，把这片岛屿全部变成 '0'
                dfs(grid, i, j, gridSize, colSize);
            }
        }
    }

    return count;
}