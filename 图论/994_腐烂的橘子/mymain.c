// 不对
#include <stdlib.h>
int bfs(int **grid, int row, int col, int rowmax, int colmax)
{
    if (row < 0 || row >= rowmax || col < 0 || col >= colmax || grid[row][col] == 0)
    {
        return 0;
    }
    if (grid[row][col] == 2)
    {
        bfs(grid, row + 1, col, rowmax, colmax); // 下
        bfs(grid, row - 1, col, rowmax, colmax); // 上
        bfs(grid, row, col + 1, rowmax, colmax); // 右
        bfs(grid, row, col - 1, rowmax, colmax); // 左
        return 0;
    }
    else if (grid[row][col] == 1)
    {
        grid[row][col] = 2;
        return 1;
    }
    return -1;
}

int orangesRotting(int **grid, int gridSize, int *gridColSize)
{
    int res = 0;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < *gridColSize; j++)
        {
            if (grid[i][j] == 2)
                res += bfs(grid, i, j, gridSize, *gridColSize);
        }
    }
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < *gridColSize; j++)
        {
            if (grid[i][j] == 1)
                return -1;
        }
    }
    return res;
}