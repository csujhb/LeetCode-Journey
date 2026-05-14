# 算法学习笔记：LeetCode 994. 腐烂的橘子

## 一、 题目描述

给定一个包含 `m x n` 个单元格的网格 `grid`，每个单元格的值只能是以下三种情况之一：

* `0` 代表空单元格；
* `1` 代表新鲜橘子；
* `2` 代表腐烂的橘子。

每分钟，腐烂的橘子会使其上下左右四个方向上相邻的新鲜橘子腐烂。
**要求：** 返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 `-1`。

## 二、 问题本质与算法选型

本题是经典的**图连通性与最短扩散路径**问题。由于题目要求所有腐烂的橘子**同时**向四周蔓延，并求出全部感染所需的“最短时间”，这严格契合了广度优先搜索（BFS）的物理模型。

* **❌ 为什么不能用 DFS（深度优先搜索）？**
DFS 的特性是“一条路走到黑”，它模拟的是“依次感染”——一个橘子顺着一条线把别人全感染完，再回头走另一条线。这无法体现“同时扩散”的时间流逝。
* **✅ 为什么必须用 BFS？**
BFS 采用的是“波纹式扩散”（层序遍历）。每一次向外扩散一圈，就代表时间过去了一分钟。

## 三、 核心解题思想：多源 BFS (Multi-source BFS)

传统的 BFS（例如迷宫寻宝）通常只有一个起点（单源点）。而本题中，初始状态下可能存在多个腐烂的橘子，它们会**同时**作为源头开始扩散。

**算法步骤：**

1. **全面扫描（第 0 分钟）：** 遍历整个二维网格，统计新鲜橘子（`1`）的总数，并将所有初始的腐烂橘子（`2`）的坐标全部加入队列。
2. **层序扩散：** 当队列不为空且还有新鲜橘子时，按“层”弹出当前队列中的所有橘子。将它们四周的新鲜橘子全部感染（变为 `2`），新鲜橘子总数减 1，并将新感染的橘子加入队列尾部。
3. **时间推进：** 当前“层”的所有橘子处理完毕，总分钟数 `+1`。
4. **终局判定：** 循环结束后，若新鲜橘子数量为 `0`，说明全部感染，返回分钟数；若仍大于 `0`，说明存在被物理隔绝的橘子，返回 `-1`。

## 四、 二维网格 BFS 的三大工程基石

从树的 BFS 拓展到网格图的 BFS，必须牢记以下三个核心处理技巧：

1. **方向数组处理邻接节点：**
在树中通过 `node->left` 找邻居，在网格中通过建立静态数组来优雅地向四个正交方向移动：`int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};`
2. **基于当前队列长度的层序遍历：**
必须使用 `current_level_size = tail - head` 锁死当前这一分钟需要处理的节点数量，利用 `for` 循环切分批次。否则队列会像流水线一样无法区分“哪几个橘子是同一分钟感染的”。
3. **入队即刻标记（防爆内存的生命线）：**
发现新鲜橘子时，**在将其加入队列的同一瞬间**，立刻将其状态修改为 `2`（原地修改）。如果不提前标记，同一个新鲜橘子可能会被多个邻居“重复发现”并多次压入队列，导致内存爆炸。

## 五、 标准 C 语言实现

```c
#include <stdlib.h>
#include <stdbool.h>

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    
    // 队列最多包含网格中所有的元素
    int maxQueueSize = rows * cols;
    // 队列中存储坐标 [row, col]
    int** queue = (int**)malloc(maxQueueSize * sizeof(int*));
    for (int i = 0; i < maxQueueSize; i++) {
        queue[i] = (int*)malloc(2 * sizeof(int));
    }
    
    int head = 0; // 队头
    int tail = 0; // 队尾
    int freshCount = 0; // 新鲜橘子数量
    
    // 1. 初始化：统计新鲜橘子，并将所有初始腐烂的橘子入队
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                freshCount++;
            } else if (grid[i][j] == 2) {
                queue[tail][0] = i;
                queue[tail][1] = j;
                tail++; // 入队
            }
        }
    }
    
    // 如果一开始就没有新鲜橘子，直接返回 0
    if (freshCount == 0) {
        for (int i = 0; i < maxQueueSize; i++) free(queue[i]);
        free(queue);
        return 0;
    }
    
    int minutes = 0;
    // 上下左右四个方向的偏移量
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // 2. 开始 BFS 扩散
    while (head < tail && freshCount > 0) {
        int currentLevelSize = tail - head; // 当前这一分钟扩散的节点数
        
        for (int i = 0; i < currentLevelSize; i++) {
            int r = queue[head][0];
            int c = queue[head][1];
            head++; // 出队
            
            // 向四个方向扩散
            for (int d = 0; d < 4; d++) {
                int newR = r + directions[d][0];
                int newC = c + directions[d][1];
                
                // 判断是否越界，以及是否是新鲜橘子
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && grid[newR][newC] == 1) {
                    grid[newR][newC] = 2; // 状态修改：立刻感染它（入队即标记）
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
    
    // 释放内存，防止内存泄漏
    for (int i = 0; i < maxQueueSize; i++) free(queue[i]);
    free(queue);
    
    // 3. 检查是否还有永远无法被感染的橘子
    if (freshCount > 0) {
        return -1;
    }
    
    return minutes;
}

```

## 六、 复杂度严格推导

* **时间复杂度：** $O(M \times N)$
其中 $M$ 是网格的行数，$N$ 是列数。网格中的每个单元格最多只会被遍历两次（初始化一次，BFS 扩散时一次）。每个节点的操作都是常数时间 $O(1)$，因此整体时间呈严格的线性关系。
* **空间复杂度：** $O(M \times N)$
主要消耗在借助数组模拟的队列（Queue）上。在最坏的情况下（例如整个网格全是腐烂的橘子），队列需要容纳 $M \times N$ 个坐标对，即占用 $O(M \times N)$ 的辅助内存。原地修改网格状态省去了额外的 `visited` 数组开销。