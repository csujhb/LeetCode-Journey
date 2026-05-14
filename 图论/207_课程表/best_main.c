#include <stdlib.h>
#include <stdbool.h>

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize)
{
    // 1. 初始化入度数组和出度数组
    int *inDegree = (int *)calloc(numCourses, sizeof(int));
    int *outDegree = (int *)calloc(numCourses, sizeof(int));

    // 第一次遍历：统计每个节点的入度和出度
    for (int i = 0; i < prerequisitesSize; i++)
    {
        int course = prerequisites[i][0]; // 目标课程
        int pre = prerequisites[i][1];    // 先修课程
        inDegree[course]++;               // 目标课程的入度 +1
        outDegree[pre]++;                 // 先修课程的出度 +1 (它要指向别人)
    }

    // 2. 构建邻接表 (Adjacency List)
    int **graph = (int **)malloc(numCourses * sizeof(int *));
    for (int i = 0; i < numCourses; i++)
    {
        // 根据出度精确分配内存，杜绝浪费
        graph[i] = (int *)malloc(outDegree[i] * sizeof(int));
    }

    // 用一个辅助数组记录当前邻接表填到了哪个位置
    int *outCount = (int *)calloc(numCourses, sizeof(int));

    // 第二次遍历：真正将边填入邻接表
    for (int i = 0; i < prerequisitesSize; i++)
    {
        int course = prerequisites[i][0];
        int pre = prerequisites[i][1];
        // 记录 pre 课程指向了 course
        graph[pre][outCount[pre]++] = course;
    }

    // 3. BFS 核心逻辑
    int *queue = (int *)malloc(numCourses * sizeof(int));
    int head = 0, tail = 0;

    // 把所有入度为 0 的课（可以直接学的课）入队
    for (int i = 0; i < numCourses; i++)
    {
        if (inDegree[i] == 0)
        {
            queue[tail++] = i;
        }
    }

    int takenCourses = 0; // 记录已经学完的课程数

    while (head < tail)
    {
        int current = queue[head++]; // 出队：修完当前课程
        takenCourses++;

        // 遍历所有依赖这门课的后续课程
        for (int i = 0; i < outDegree[current]; i++)
        {
            int nextCourse = graph[current][i];
            inDegree[nextCourse]--; // 后续课程的依赖减 1

            // 如果后续课程的所有依赖都被解除了，入队
            if (inDegree[nextCourse] == 0)
            {
                queue[tail++] = nextCourse;
            }
        }
    }

    // 4. 释放所有动态分配的内存 (C语言工程师的基本素养)
    for (int i = 0; i < numCourses; i++)
        free(graph[i]);
    free(graph);
    free(inDegree);
    free(outDegree);
    free(outCount);
    free(queue);

    // 如果学完的课等于总课程数，说明没有环；否则存在死锁
    return takenCourses == numCourses;
}