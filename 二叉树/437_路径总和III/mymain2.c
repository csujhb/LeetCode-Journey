// 没写出来
// 2026.6.9
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int dfs(struct TreeNode *root)
{
    if (root == NULL)
        return 0;
    int res1 = dfs(root->left);
    int res2 = dfs(root->right);
}

int pathSum(struct TreeNode *root, int targetSum)
{
    if (root == NULL)
        return 0;
}