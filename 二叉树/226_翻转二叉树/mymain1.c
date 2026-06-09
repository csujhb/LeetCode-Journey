// 2026.6.9
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *invertTree(struct TreeNode *root)
{
    if (root == NULL)
        return NULL;
    struct TreeNode *queue[101];
    int front = 0;
    int rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        struct TreeNode *node = queue[front++];

        struct TreeNode *temp = node->left;
        node->left = node->right;
        node->right = temp;
        if (node->left)
            queue[rear++] = node->left;
        if (node->right)
            queue[rear++] = node->right;
    }
    return root;
}