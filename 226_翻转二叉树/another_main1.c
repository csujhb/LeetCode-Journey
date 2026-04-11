/*
迭代 DFS（显式栈模拟递归）
时间复杂度：O(n)

空间复杂度：最坏 O(n)
*/
#include <stdlib.h>
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
struct StackNode {
    struct TreeNode** data;
    int top;
};

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL) return NULL;

    // 假设最大节点数10000，实际可用动态数组
    struct TreeNode* stack[10000];
    int top = 0;
    stack[top++] = root;

    while (top > 0) {
        struct TreeNode* node = stack[--top];
        // 交换左右子节点
        struct TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;

        // 将非空子节点入栈（顺序任意）
        if (node->left)  stack[top++] = node->left;
        if (node->right) stack[top++] = node->right;
    }
    return root;
}