// 2026.6.9
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int kthSmallest(struct TreeNode *root, int k)
{
    struct TreeNode *stack[10001];
    struct TreeNode *cur = root;
    int top = -1;
    while (top != -1 || cur != NULL)
    {
        while (cur)
        {
            stack[++top] = cur;
            cur = cur->left;
        }
        cur = stack[top--];
        k--;
        if (k == 0)
            return cur->val;
        cur = cur->right;
    }
    return 0;
}