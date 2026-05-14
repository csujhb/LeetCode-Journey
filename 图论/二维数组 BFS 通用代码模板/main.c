#include <stdlib.h>
#include <stdbool.h>

// 返回走到目标需要的最短步数，或者遍历所有节点
int bfs_template(int** grid, int rows, int cols) {
    // 1. 定义方向数组：上、下、左、右
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // 2. 初始化队列 (大小通常为 rows * cols 就足够了)
    int max_size = rows * cols;
    int** queue = (int**)malloc(max_size * sizeof(int*));
    for (int i = 0; i < max_size; i++) {
        queue[i] = (int*)malloc(2 * sizeof(int));
    }
    int head = 0, tail = 0;

    // 3. 寻找起始点并入队（单源就是 1 个点，多源就是多个点）
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == /* 起点条件，例如 2 */) {
                queue[tail][0] = i;
                queue[tail][1] = j;
                tail++;
                // 【关键】：入队时立刻标记为已访问！
                // 可以是原地修改 grid[i][j] = VISITED，也可以用额外的 visited 数组
            }
        }
    }

    int step = 0; // 记录走过的层数/步数/时间

    // 4. 核心 BFS 循环
    while (head < tail) {
        // 【核心技巧】：记录当前队列里的节点数量，这代表了“当前这一层”有多少个节点
        int current_level_size = tail - head; 

        // 5. 遍历当前这一层的所有节点
        for (int i = 0; i < current_level_size; i++) {
            // 出队
            int r = queue[head][0];
            int c = queue[head][1];
            head++; 

            // 如果题目要求走到某个终点，在这里判断：
            // if (grid[r][c] == /* 终点条件 */) return step;

            // 6. 向四个方向扩散
            for (int d = 0; d < 4; d++) {
                int next_r = r + dirs[d][0];
                int next_c = c + dirs[d][1];

                // 7. 防守判断：不越界 && 是有效路径 && 没被访问过
                if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && 
                    grid[next_r][next_c] == /* 可以走的条件，比如 1 */) {
                    
                    // 【关键】：标记为已访问，防止后面重复把它加入队列！
                    grid[next_r][next_c] = /* 改变状态，比如变成 2 */ ;
                    
                    // 新节点入队，作为下一层的扩散源
                    queue[tail][0] = next_r;
                    queue[tail][1] = next_c;
                    tail++;
                }
            }
        }
        // 当前这一层全部走完了，步数/分钟数 + 1
        step++; 
    }

    // 记得释放队列内存，防止内存泄漏
    for (int i = 0; i < max_size; i++) free(queue[i]);
    free(queue);

    return step; // 或者根据题意返回其他值
}