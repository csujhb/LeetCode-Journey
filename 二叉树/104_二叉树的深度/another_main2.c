/*
BFS  队列
*/
// 使用数组模拟循环队列
#define MAX_SIZE 10000
#include <stdio.h>
// 栈元素结构体
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0;
    int depth = 0;

    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;   // 当前层的节点数
        // 将当前层所有节点出队，并将其子节点入队
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            if (node->left)  queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        depth++;  // 完成一层，深度+1
    }

    return depth;
}