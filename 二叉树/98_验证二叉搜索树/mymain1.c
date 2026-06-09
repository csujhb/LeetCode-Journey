// 不对
// 2026.6.9
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool dfs(struct TreeNode *root, long long max, long long min) // 若想正确，应该将int max和min都改成long long;best_main.c中的解法更合适
{
    if (root == NULL)
        return true;
    if (root->val <= min || root->val >= max)
    {
        return false;
    }
    bool res1 = dfs(root->left, root->val, min);
    bool res2 = dfs(root->right, max, root->val);
    return res1 && res2;
}

bool isValidBST(struct TreeNode *root)
{
    return dfs(root, LLONG_MAX, LLONG_MIN);
}