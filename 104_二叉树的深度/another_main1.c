/*
迭代 DFS（显式栈模拟递归）
*/

#include <stdio.h>
// 栈元素结构体
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};

struct StackNode {
    struct TreeNode* node;
    int depth;
};

int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;

    // 简单数组模拟栈（假设节点数不超过10000，实际可用动态分配）
    struct StackNode stack[10000];
    int top = 0;
    int maxDepth = 0;

    stack[top++] = (struct StackNode){root, 1};

    while (top > 0) {
        struct StackNode curr = stack[--top];
        struct TreeNode* node = curr.node;
        int depth = curr.depth;

        // 更新最大深度
        if (depth > maxDepth) maxDepth = depth;

        // 先压右，再压左（保证左子树先处理，不过顺序不影响最终结果）
        if (node->right) stack[top++] = (struct StackNode){node->right, depth + 1};
        if (node->left)  stack[top++] = (struct StackNode){node->left, depth + 1};
    }

    return maxDepth;
}