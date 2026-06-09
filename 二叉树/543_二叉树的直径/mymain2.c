// 2026.6.9
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int dfs(struct TreeNode *root, int *max)
{
    if (root == NULL)
    {
        return 0;
    }

    int left_depth = dfs(root->left, max);
    int right_depth = dfs(root->right, max);

    int diameter_through_root = left_depth + right_depth;
    if (diameter_through_root > *max)
    {
        *max = diameter_through_root;
    }

    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int diameterOfBinaryTree(struct TreeNode *root)
{
    if (root == NULL)
        return 0;
    int max_diameter = 0;
    dfs(root, &max_diameter);
    return max_diameter;
}