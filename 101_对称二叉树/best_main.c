/*递归 DFS（最优解）*/

/*
时间：O(n)，每个节点访问一次。

空间：O(h)，递归栈深度（最坏 O(n)）。
*/
#include <stdlib.h>
#include <stdbool.h>
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
bool isMirror(struct TreeNode* left, struct TreeNode* right) {
    if (left == NULL && right == NULL) return true;
    if (left == NULL || right == NULL) return false;
    return (left->val == right->val) &&
           isMirror(left->left, right->right) &&
           isMirror(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;
    return isMirror(root->left, root->right);
}