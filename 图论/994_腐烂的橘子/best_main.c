#include <stdlib.h>
#include <stdbool.h>

int orangesRotting(int **grid, int gridSize, int *gridColSize)
{
    int rows = gridSize;
    int cols = gridColSize[0];

    // 队列最多包含网格中所有的元素
    int maxQueueSize = rows * cols;
    // 队列中存储坐标 [row, col]
    int **queue = (int **)malloc(maxQueueSize * sizeof(int *));
    for (int i = 0; i < maxQueueSize; i++)
    {
        queue[i] = (int *)malloc(2 * sizeof(int));
    }

    int head = 0;       // 队头
    int tail = 0;       // 队尾
    int freshCount = 0; // 新鲜橘子数量

    // 1. 初始化：统计新鲜橘子，并将所有初始腐烂的橘子入队
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1)
            {
                freshCount++;
            }
            else if (grid[i][j] == 2)
            {
                queue[tail][0] = i;
                queue[tail][1] = j;
                tail++; // 入队
            }
        }
    }

    // 如果一开始就没有新鲜橘子，直接返回 0
    if (freshCount == 0)
    {
        // 释放内存（良好的 C 语言习惯）
        for (int i = 0; i < maxQueueSize; i++)
            free(queue[i]);
        free(queue);
        return 0;
    }

    int minutes = 0;
    // 上下左右四个方向的偏移量
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // 2. 开始 BFS 扩散
    while (head < tail && freshCount > 0)
    {
        int currentLevelSize = tail - head; // 当前这一分钟有多少个橘子要向外扩散

        for (int i = 0; i < currentLevelSize; i++)
        {
            int r = queue[head][0];
            int c = queue[head][1];
            head++; // 出队

            // 向四个方向扩散
            for (int d = 0; d < 4; d++)
            {
                int newR = r + directions[d][0];
                int newC = c + directions[d][1];

                // 判断是否越界，以及是否是新鲜橘子
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && grid[newR][newC] == 1)
                {
                    grid[newR][newC] = 2; // 感染它
                    freshCount--;         // 新鲜橘子减少

                    // 把新感染的橘子入队，留到下一分钟扩散
                    queue[tail][0] = newR;
                    queue[tail][1] = newC;
                    tail++;
                }
            }
        }
        minutes++; // 这一批次全部扩散完毕，时间过去了一分钟
    }

    // 释放内存
    for (int i = 0; i < maxQueueSize; i++)
        free(queue[i]);
    free(queue);

    // 3. 检查是否还有永远无法被感染的橘子
    if (freshCount > 0)
    {
        return -1;
    }

    return minutes;
}