# 算法学习笔记：LeetCode 207. 课程表

## 一、 问题本质与理论模型

“课程表”问题的数学本质是：**判断一个有向图（Directed Graph）中是否存在环（Cycle）。**
如果图中没有环，我们称之为**有向无环图（DAG, Directed Acyclic Graph）**。只有 DAG 才能排出一个合理的先后顺序，这个排序的过程在计算机科学中被称为**拓扑排序（Topological Sorting）**。

* **课程** = 图中的**节点（Node/Vertex）**。
* **先修关系** = 图中的**有向边（Directed Edge）**。例如 `[1, 0]` 表示必须先学 `0` 再学 `1`，即存在一条边 `0 -> 1`。

## 二、 核心解题思想：Kahn 算法 (基于 BFS 的拓扑排序)

由于你刚刚掌握了 BFS 队列，这里强烈推荐使用 **BFS（广度优先搜索）的变体——Kahn（卡恩）算法**。它的思想非常符合现实生活：

1. **入度（In-degree）：** 一个节点有几条边指向它，它的入度就是几。在现实中，它代表“**这门课有几门先修课**”。
* 如果一门课入度为 `0`，说明它没有先决条件，**现在就可以马上学！**


2. **BFS 队列流转：**
* **第 1 步：** 把所有入度为 `0` 的课程统统扔进 BFS 队列。
* **第 2 步：** 从队列里弹出一门课（相当于学完了），然后把所有依赖这门课的后续课程的入度减 `1`（相当于满足了它们的一个先决条件）。
* **第 3 步：** 如果某个后续课程的入度减到了 `0`，说明它的所有先决条件都被满足了，立刻把它也扔进队列。


3. **终局判定：** 当队列空了以后，看看我们“学完”（弹出）了多少门课。如果等于总课程数，说明顺利毕业（返回 `true`）；如果小于总课程数，说明剩下的课互相依赖形成了死循环（返回 `false`）。

## 三、 C 语言工程难点：邻接表的构建

在 Java 或 Python 中，我们可以直接用哈希表套数组来表示图的边。但在 C 语言中，题目只给了一个二维数组 `prerequisites`。

为了达到极致的执行效率，我们不使用繁琐的链表（容易内存泄漏且速度慢），而是采用**两次遍历法构建静态二维数组（邻接表）**：

1. **第一次遍历：** 统计每个节点发出了多少条边（出度 outDegree），以此来精确 `malloc` 每一行的内存。
2. **第二次遍历：** 真正把指向的节点填入分配好的数组中。

## 四、 标准 C 语言最优解代码

```c
#include <stdlib.h>
#include <stdbool.h>

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    // 1. 初始化入度数组和出度数组
    int* inDegree = (int*)calloc(numCourses, sizeof(int));
    int* outDegree = (int*)calloc(numCourses, sizeof(int));

    // 第一次遍历：统计每个节点的入度和出度
    for (int i = 0; i < prerequisitesSize; i++) {
        int course = prerequisites[i][0]; // 目标课程
        int pre = prerequisites[i][1];    // 先修课程
        inDegree[course]++;               // 目标课程的入度 +1
        outDegree[pre]++;                 // 先修课程的出度 +1 (它要指向别人)
    }

    // 2. 构建邻接表 (Adjacency List)
    int** graph = (int**)malloc(numCourses * sizeof(int*));
    for (int i = 0; i < numCourses; i++) {
        // 根据出度精确分配内存，杜绝浪费
        graph[i] = (int*)malloc(outDegree[i] * sizeof(int)); 
    }

    // 用一个辅助数组记录当前邻接表填到了哪个位置
    int* outCount = (int*)calloc(numCourses, sizeof(int)); 
    
    // 第二次遍历：真正将边填入邻接表
    for (int i = 0; i < prerequisitesSize; i++) {
        int course = prerequisites[i][0];
        int pre = prerequisites[i][1];
        // 记录 pre 课程指向了 course
        graph[pre][outCount[pre]++] = course; 
    }

    // 3. BFS 核心逻辑
    int* queue = (int*)malloc(numCourses * sizeof(int));
    int head = 0, tail = 0;

    // 把所有入度为 0 的课（可以直接学的课）入队
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) {
            queue[tail++] = i;
        }
    }

    int takenCourses = 0; // 记录已经学完的课程数

    while (head < tail) {
        int current = queue[head++]; // 出队：修完当前课程
        takenCourses++;

        // 遍历所有依赖这门课的后续课程
        for (int i = 0; i < outDegree[current]; i++) {
            int nextCourse = graph[current][i];
            inDegree[nextCourse]--; // 后续课程的依赖减 1

            // 如果后续课程的所有依赖都被解除了，入队
            if (inDegree[nextCourse] == 0) {
                queue[tail++] = nextCourse;
            }
        }
    }

    // 4. 释放所有动态分配的内存 (C语言工程师的基本素养)
    for (int i = 0; i < numCourses; i++) free(graph[i]);
    free(graph);
    free(inDegree);
    free(outDegree);
    free(outCount);
    free(queue);

    // 如果学完的课等于总课程数，说明没有环；否则存在死锁
    return takenCourses == numCourses;
}

```

## 五、 复杂度严格推导

设 $V$ 为节点数（课程总数 `numCourses`），$E$ 为边的数量（先修关系的对数 `prerequisitesSize`）。

* **时间复杂度：$O(V + E)$**
* 统计入度和构建邻接表：需要遍历所有的先修关系，耗时 $O(E)$。
* BFS 遍历：每个入度为 `0` 的节点最多入队、出队一次，处理时会遍历其所有射出的边。所有节点的入队出队操作总共耗时 $O(V)$，遍历所有边的总操作次数为 $O(E)$。因此 BFS 部分耗时 $O(V + E)$。
* 总时间复杂度为线性的 $O(V + E)$。


* **空间复杂度：$O(V + E)$**
* `inDegree`、`outDegree`、`outCount` 和 `queue` 数组各占 $O(V)$ 的空间。
* `graph` 邻接表结构中，所有一维数组的长度总和恰好等于边的数量 $E$，即占用 $O(E)$ 的空间。
* 总体内存消耗为 $O(V + E)$。