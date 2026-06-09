// 2026.6.9
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{

    *returnSize = 0;
    if (root == NULL)
    {
        *returnColumnSizes == NULL;
        return NULL;
    }

    int **res = (int **)malloc(sizeof(int *) * 2000);
    *returnColumnSizes = (int *)malloc(sizeof(int) * 2000);
    struct TreeNode *queue[2000];
    int front = 0;
    int rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        int len = rear - front;
        res[*returnSize] = (int *)malloc(sizeof(int) * len);
        (*returnColumnSizes)[*returnSize] = len;
        for (int i = 0; i < len; i++)
        {
            struct TreeNode *node = queue[front++];
            res[*returnSize][i] = node->val;
            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
        (*returnSize)++;
    }
    return res;
}
