// 2026.6.9
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *rightSideView(struct TreeNode *root, int *returnSize)
{
    *returnSize = 0;
    if (root == NULL)
        return NULL;
    int *res = (int *)malloc(100 * sizeof(int));
    struct TreeNode *queue[101];
    int front = 0;
    int rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        int len = rear - front;
        for (int i = 0; i < len; i++)
        {
            if (i == 0)
                res[*returnSize] = queue[front]->val;
            struct TreeNode *node = queue[front++];
            if (node->right)
                queue[rear++] = node->right;
            if (node->left)
                queue[rear++] = node->left;
        }
        (*returnSize)++;
    }
    return res;
}