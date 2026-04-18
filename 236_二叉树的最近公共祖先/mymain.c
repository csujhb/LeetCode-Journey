#include <stdio.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }
    struct TreeNode* node1 = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* node2 = lowestCommonAncestor(root->right, p, q);
    if (node1 != NULL && node2 != NULL) {
        return root;
    }
    if (node1 == NULL) {
        return node2;
    }
    if (node2 == NULL) {
        return node1;
    }
    return NULL;
}