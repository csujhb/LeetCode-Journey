/*
 时间复杂度：O(N)
 空间复杂度： O(N)，空间复杂度主要取决于递归调用栈的最大深度。在最坏情况下（二叉树退化为链表），深度为 N；如果是平衡二叉树，深度为 O(log N)
*/

#include <limits.h>
#include <stdlib.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
// 递归函数：返回当前节点能为父节点提供的最大贡献值
int dfs(struct TreeNode* root, int* maxSum) {
    if (root == NULL) {
        return 0; 
    }

    // 【关键修复】：先调用函数存入变量，绝对不能把函数调用直接塞进 MAX 宏里！
    int left_val = dfs(root->left, maxSum);
    int right_val = dfs(root->right, maxSum);

    // 利用变量进行剪枝（舍弃负数）
    int left = MAX(0, left_val);
    int right = MAX(0, right_val);

    // 计算当前子树内部的最大路径和，挑战全局最大值
    int currentPathSum = root->val + left + right;
    *maxSum = MAX(*maxSum, currentPathSum);

    // 返回当前节点作为单条分支的最大贡献
    return root->val + MAX(left, right);
}

int maxPathSum(struct TreeNode* root) {
    int maxSum = INT_MIN; 
    dfs(root, &maxSum);
    return maxSum;
}