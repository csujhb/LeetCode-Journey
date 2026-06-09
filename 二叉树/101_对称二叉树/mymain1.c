#include <stdbool.h>
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSame(struct TreeNode *n1, struct TreeNode *n2)
{
    if (n1 == NULL && n2 == NULL)
        return true;
    if (n1 == NULL || n2 == NULL)
        return false;
    return (n1->val == n2->val) &&
           isSame(n1->left, n2->right) &&
           isSame(n1->right, n2->left);
}

bool isSymmetric(struct TreeNode *root)
{
    if (root == NULL)
        return true;
    struct TreeNode *left = root->left;
    struct TreeNode *right = root->right;
    return isSame(left, right);
}