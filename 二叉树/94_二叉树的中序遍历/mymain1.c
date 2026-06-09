// 2026.6.9
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void inorder(struct TreeNode *root, int *res, int *returnSize)
{
    if (root == NULL)
        return;
    inorder(root->left, res, returnSize);
    res[(*returnSize)++] = root->val;
    inorder(root->right, res, returnSize);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    *returnSize = 0;
    if (root == NULL)
        return NULL;
    int *res = (int *)malloc(101 * sizeof(struct TreeNode));
    inorder(root, res, returnSize);
    return res;
}