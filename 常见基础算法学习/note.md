# BFS 与 DFS 算法笔记

## 一、概述

| 算法 | 全称 | 核心思想 | 数据结构 |
|------|------|----------|----------|
| BFS | 广度优先搜索 | 按层遍历，先近后远 | 队列 |
| DFS | 深度优先搜索 | 一条路走到黑，回溯 | 栈（或递归） |

## 二、广度优先搜索（BFS）

### 原理
从起点出发，先访问所有距离为 1 的节点，再访问距离为 2 的节点，…，直到找到目标或遍历完毕。  
**特点**：在无权图中首次到达目标时的步数即为最短路径。

### 实现方式（C语言）
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

// 邻接表结构
typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* graph[MAX_NODES];
bool visited[MAX_NODES];

// 添加边（无向图）
void addEdge(int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = v;
    node->next = graph[u];
    graph[u] = node;
    
    node = (Node*)malloc(sizeof(Node));
    node->val = u;
    node->next = graph[v];
    graph[v] = node;
}

// BFS 遍历（从 start 开始）
void BFS(int start) {
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = true;
    
    while (front < rear) {
        int cur = queue[front++];
        printf("%d ", cur);
        
        Node* neighbor = graph[cur];
        while (neighbor) {
            int next = neighbor->val;
            if (!visited[next]) {
                visited[next] = true;
                queue[rear++] = next;
            }
            neighbor = neighbor->next;
        }
    }
}
```

### 举例：零钱兑换（最少硬币数）
```c
int coinChangeBFS(int* coins, int coinsSize, int amount) {
    if (amount == 0) return 0;
    int* queue = (int*)malloc(sizeof(int) * (amount + 1));
    bool* visited = (bool*)calloc(amount + 1, sizeof(bool));
    int front = 0, rear = 0;
    queue[rear++] = amount;
    visited[amount] = true;
    int steps = 0;
    
    while (front < rear) {
        int size = rear - front;
        steps++;
        for (int i = 0; i < size; i++) {
            int cur = queue[front++];
            for (int j = 0; j < coinsSize; j++) {
                int next = cur - coins[j];
                if (next == 0) {
                    free(queue); free(visited);
                    return steps;
                }
                if (next > 0 && !visited[next]) {
                    visited[next] = true;
                    queue[rear++] = next;
                }
            }
        }
    }
    free(queue); free(visited);
    return -1;
}
```

### 常见用途
- 无权图最短路径
- 迷宫最少步数
- 树的层序遍历
- 社交网络“几度好友”
- 单词接龙

## 三、深度优先搜索（DFS）

### 原理
从起点出发，沿着一条路径一直走到无法继续，然后回溯到上一个节点，继续尝试其他分支。  
**特点**：不保证最短路径，但空间开销通常较小（递归深度）。

### 实现方式

#### 递归实现（最简洁）
```c
bool visited[MAX_NODES];

void DFS_recursive(int cur) {
    visited[cur] = true;
    printf("%d ", cur);
    
    Node* neighbor = graph[cur];
    while (neighbor) {
        int next = neighbor->val;
        if (!visited[next]) {
            DFS_recursive(next);
        }
        neighbor = neighbor->next;
    }
}
```

#### 非递归实现（显式栈）
```c
void DFS_stack(int start) {
    int stack[MAX_NODES];
    int top = -1;
    stack[++top] = start;
    
    while (top >= 0) {
        int cur = stack[top--];
        if (!visited[cur]) {
            visited[cur] = true;
            printf("%d ", cur);
            
            // 邻居逆序入栈保证顺序（可选）
            Node* neighbor = graph[cur];
            // 收集所有邻居
            int neighbors[MAX_NODES], cnt = 0;
            while (neighbor) {
                neighbors[cnt++] = neighbor->val;
                neighbor = neighbor->next;
            }
            for (int i = cnt - 1; i >= 0; i--) {
                if (!visited[neighbors[i]]) {
                    stack[++top] = neighbors[i];
                }
            }
        }
    }
}
```

### 举例：岛屿数量（LeetCode 200）
```c
void dfs(char** grid, int gridSize, int* gridColSize, int r, int c) {
    if (r < 0 || r >= gridSize || c < 0 || c >= gridColSize[0]) return;
    if (grid[r][c] == '0') return;
    grid[r][c] = '0'; // 标记已访问
    dfs(grid, gridSize, gridColSize, r + 1, c);
    dfs(grid, gridSize, gridColSize, r - 1, c);
    dfs(grid, gridSize, gridColSize, r, c + 1);
    dfs(grid, gridSize, gridColSize, r, c - 1);
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int count = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == '1') {
                dfs(grid, gridSize, gridColSize, i, j);
                count++;
            }
        }
    }
    return count;
}
```

### 常见用途
- 图的连通分量
- 拓扑排序
- 回溯问题（全排列、N皇后、子集）
- 树的前/中/后序遍历
- 检测环
- 记忆化搜索（DFS + DP）

## 四、BFS 与 DFS 对比

| 维度 | BFS | DFS |
|------|-----|-----|
| 数据结构 | 队列 | 栈（递归或显式栈） |
| 空间复杂度 | O(宽度) | O(深度) |
| 最短路径 | 保证（无权图） | 不保证 |
| 实现复杂度 | 较简单（迭代） | 递归简洁，非递归稍复杂 |
| 适用场景 | 最短步数、层级遍历 | 连通性、回溯、穷举 |

## 五、选择建议

- **需要最短路径**（如迷宫最少步数） → BFS  
- **空间紧张**且深度不大 → DFS 递归  
- **防止递归栈溢出**（深度很大） → BFS 或 DFS 显式栈  
- **穷举所有解**（如组合、排列） → DFS 回溯  
- **树的遍历**：层序用 BFS，前/中/后序用 DFS  

## 六、总结

- BFS 按层扩散，队列实现，保证最短路径。  
- DFS 纵深搜索，栈/递归实现，擅长穷举和连通性问题。  
- 掌握两种基础算法是解决图论、搜索类题目的关键。