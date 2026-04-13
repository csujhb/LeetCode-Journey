#include <stdlib.h>
#include <math.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
int depth(struct TreeNode* root) {
    if (!root) return 0;
    return fmax(depth(root->left), depth(root->right)) + 1;
}

void travel(struct TreeNode* root, int* max_dia) {
    if (root) {
        int dia = depth(root->left) + depth(root->right);
        *max_dia = fmax(*max_dia, dia);
        travel(root->left, max_dia);
        travel(root->right, max_dia);
    }
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int max_dia = 0;
    travel(root, &max_dia);
    return max_dia;
}