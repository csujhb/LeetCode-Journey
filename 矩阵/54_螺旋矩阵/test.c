#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 邻接表节点
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// 邻接表头数组
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// 图结构
typedef struct Graph {
    int V;              // 顶点数
    AdjList* array;     // 邻接表数组
} Graph;

// 创建邻接表节点
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// 创建图（V个顶点）
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// 添加无向边
void addEdge(Graph* graph, int src, int dest) {
    // 添加 src -> dest
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // 无向图，添加 dest -> src
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}


// 递归辅助函数
void DFSUtil(Graph* graph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);   // 访问当前顶点

    AdjListNode* p = graph->array[v].head;
    while (p) {
        int adj = p->dest;
        if (!visited[adj])
            DFSUtil(graph, adj, visited);
        p = p->next;
    }
}

// 递归DFS（从 start 开始）
void DFS_recursive(Graph* graph, int start) {
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    printf("DFS (递归) 从 %d 开始: ", start);
    DFSUtil(graph, start, visited);
    // 如果图不连通，可以继续遍历未访问的顶点（示例中省略）
    free(visited);
    printf("\n");
}

int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 2, 4);
    DFS_recursive(graph, 4);
    //DFS_stack(graph, 0);

    // 释放图内存（略）
    return 0;
}
