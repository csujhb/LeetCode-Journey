# 算法学习笔记：LeetCode 200. 岛屿数量

## 一、 问题抽象与理论模型

“岛屿数量”问题在图论（Graph Theory）中属于经典的求解无向图连通分量（Connected Components）问题。二维网格可以被视作一个无向图，其中每个值为 `'1'` 的单元格是一个节点，上下左右相邻的 `'1'` 之间存在边。

**核心解题思想：沉岛模型（Sink the Island）**
在遍历网格的过程中，一旦遇到尚未被发现的陆地（`'1'`），即确认发现了一个新的连通分量（岛屿数量加 1）。为了防止后续遍历时重复统计该岛屿，需要立即启动图遍历算法（DFS 或 BFS），将与该节点连通的所有 `'1'` 状态反转为 `'0'`。

## 二、 算法设计与工程优化

在 C 语言实现中，深度优先搜索（DFS）是最简洁且符合程序调用栈逻辑的选择。

### 1. 状态维护与栈帧优化

在早期的实现版本中，尝试将计数器（`count`）和状态标志（`flag`）作为参数压入 DFS 函数。从底层系统与内存调度的角度来看，存在以下冗余：

* **栈空间消耗**：每次递归调用都会增加参数压栈的开销。对于最大 $300 \times 300$ 的网格，极端情况下的最大递归深度可达 $90,000$，额外的指针和整型变量传递会导致栈帧（Stack Frame）显著膨胀，增加 Stack Overflow 的风险。
* **逻辑解耦**：DFS 的唯一职责应当是“图的遍历与状态抹除”。计数的逻辑完全可以由主控循环接管，实现控制流与业务逻辑的解耦。

### 2. 原地修改（In-place Modification）

不分配额外的 `visited` 布尔型二维数组，而是直接在传入的 `grid` 指针所指向的内存块中进行字符覆写（将 `'1'` 覆写为 `'0'`）。这种原地修改策略将辅助空间复杂度从 $O(M \times N)$ 降至严格的 $O(1)$，是对内存极其友好的实现方式。

## 三、 标准 C 语言参考实现

```c
// 图遍历模块：负责单次连通分量的状态抹除
void dfs(char **grid, int row, int col, int rowmax, int colmax) {
    // 边界检测与递归终止条件
    if (row < 0 || row >= rowmax || col < 0 || col >= colmax || grid[row][col] == '0') {
        return;
    }
    
    // 状态修改：标记当前节点已访问
    grid[row][col] = '0';
    
    // 深度优先向四个正交方向探索
    dfs(grid, row + 1, col, rowmax, colmax); 
    dfs(grid, row - 1, col, rowmax, colmax); 
    dfs(grid, row, col + 1, rowmax, colmax); 
    dfs(grid, row, col - 1, rowmax, colmax); 
}

// 主控模块
int numIslands(char **grid, int gridSize, int *gridColSize) {
    if (grid == NULL || gridSize == 0 || gridColSize == NULL) {
        return 0;
    }

    int count = 0;
    int colSize = gridColSize[0]; 

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (grid[i][j] == '1') {
                count++; // 捕获独立连通分量
                dfs(grid, i, j, gridSize, colSize);
            }
        }
    }
    return count;
}

```

## 四、 复杂度严格推导

* **时间复杂度：** $O(M \times N)$
网格中的每个单元格在双重 `for` 循环中被访问一次。如果单元格的值为 `'1'`，它会触发 DFS 并立即被修改为 `'0'`。这意味着在整个程序生命周期内，每个单元格最多被 DFS 访问并处理一次。总的访问操作次数与网格的总面积成严格的线性关系。
* **空间复杂度：** * 辅助内存：$O(1)$（原地修改）。
* 调用栈内存：最坏情况下（例如网格呈“蛇形”相连的纯陆地），DFS 递归深度达到 $M \times N$，空间消耗为 $O(M \times N)$；在最优情况下（全为水），递归深度为 0，空间消耗为 $O(1)$。



## 五、 性能测评误差分析

在线上评测系统（如 LeetCode）中，高度精简的 C 语言代码常常面临执行时间波动的现象。由于 $O(M \times N)$ 的操作在现代处理器上的执行周期极短（微秒级），其实际测量时间往往会被服务器的进程调度延迟、网络 I/O 波动掩盖。同时，现代编译器（如 GCC `-O2` 级别以上）的尾递归优化和内联展开，会抹平不同代码风格之间的微小指令集差异。因此，工程实践中应以大 O 渐进复杂度和内存占用作为评估算法优劣的核心基准。