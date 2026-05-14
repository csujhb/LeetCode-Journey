void island(char **grid, int row, int col, int rowmax, int colmax, int *count, int flag)
{
    if (row < 0 || row >= rowmax || col < 0 || col >= colmax || grid[row][col] == '0')
        return;
    grid[row][col] = '0';
    if (flag == 0)
    {
        flag = 1;
        (*count)++;
    }
    island(grid, row + 1, col, rowmax, colmax, count, flag);
    island(grid, row - 1, col, rowmax, colmax, count, flag);
    island(grid, row, col + 1, rowmax, colmax, count, flag);
    island(grid, row, col - 1, rowmax, colmax, count, flag);
}

int numIslands(char **grid, int gridSize, int *gridColSize)
{
    int count = 0;
    int flag = 0;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < *gridColSize; j++)
        {
            if (grid[i][j] == '1')
                island(grid, i, j, gridSize, *gridColSize, &count, flag);
        }
    }
    return count;
}