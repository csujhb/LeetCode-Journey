// 2026.6.9
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void flatten(struct TreeNode *root)
{
    if (root == NULL)
        return;
    struct TreeNode *cur = root;
    while (cur != NULL)
    {
        if (cur->left != NULL)
        {
            struct TreeNode *temp = cur->left;
            while (temp->right != NULL)
            {
                temp = temp->right;
            }
            temp->right = cur->right;
            cur->right = cur->left;
            cur->left = NULL;
        }
        cur = cur->right;
    }
}