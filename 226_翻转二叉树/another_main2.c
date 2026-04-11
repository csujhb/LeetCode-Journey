/*
层序遍历 BFS（广度优先搜索）
时间复杂度：O(n)

空间复杂度：O(n)（队列中最多存储一层节点）
*/

#include <stdlib.h>
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
#define MAX_SIZE 10000

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL) return NULL;

    struct TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* node = queue[front++];
        // 交换左右子节点
        struct TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;

        if (node->left)  queue[rear++] = node->left;
        if (node->right) queue[rear++] = node->right;
    }
    return root;
}