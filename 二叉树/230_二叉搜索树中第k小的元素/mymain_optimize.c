#include <stdio.h>
/* 
时间复杂度：O(H + k)
空间复杂度：O(H)
 */


// Definition for a binary tree node.
// struct TreeNode {
//     int val;
//     struct TreeNode *left;
//     struct TreeNode *right;
// };
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
void inorder(struct TreeNode* node, int k, int* count, int* res) {
    // 1. 如果节点为空，或者已经找到了结果（*count >= k），直接剪枝返回
    if (node == NULL || *count >= k) {
        return; 
    }

    // 遍历左子树
    inorder(node->left, k, count, res);

    // 2. 核心优化：从左子树回来后，再次检查是否已经找到，避免无意义地递增 count 和遍历右子树
    if (*count >= k) {
        return; 
    }

    // 处理当前节点
    (*count)++;
    if (*count == k) {
        *res = node->val;
        return;
    }

    // 遍历右子树
    inorder(node->right, k, count, res);
}

int kthSmallest(struct TreeNode* root, int k) {
    int count = 0;
    int res = -1; // 用于保存最终结果
    inorder(root, k, &count, &res);
    return res;
}