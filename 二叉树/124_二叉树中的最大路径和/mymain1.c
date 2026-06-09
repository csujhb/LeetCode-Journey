#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int dfs(struct TreeNode *root, int *max)
{
    if (root == NULL)
        return 0;
    int res1 = dfs(root->left, max);
    res1 = MAX(0, res1);
    int res2 = dfs(root->right, max);
    res2 = MAX(0, res2);
    *max = MAX(*max, root->val + res1 + res2);
    return MAX(res1, res2) + root->val;
}

int maxPathSum(struct TreeNode *root)
{
    int max = INT_MIN;
    dfs(root, &max);
    return max;
}