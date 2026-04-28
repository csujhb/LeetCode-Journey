#include <stdio.h>
#include <stdlib.h>

// 题目已定义的树节点结构
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 用数组模拟队列（最多2000个节点，根据题目范围调整）
    struct TreeNode* queue[2000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    // 结果数组的动态分配（初始容量可稍大，或逐步扩容）
    int capacity = 100;
    int** result = (int**)malloc(sizeof(int*) * capacity);
    *returnColumnSizes = (int*)malloc(sizeof(int) * capacity);

    while (front < rear) {
        int levelSize = rear - front;          // 当前层的节点数
        int* levelVals = (int*)malloc(sizeof(int) * levelSize);
        
        // 遍历当前层所有节点
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            levelVals[i] = node->val;
            
            // 左右子节点入队
            if (node->left)  queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }

        // 存储当前层结果
        (*returnColumnSizes)[*returnSize] = levelSize;
        result[*returnSize] = levelVals;
        (*returnSize)++;

        // 如果结果数组容量不足，扩容
        if (*returnSize >= capacity) {
            capacity *= 2;
            result = (int**)realloc(result, sizeof(int*) * capacity);
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * capacity);
        }
    }

    return result;
}