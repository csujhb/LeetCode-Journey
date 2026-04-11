/*
递归 DFS（深度优先搜索）
时间复杂度：O(n)，每个节点访问一次。
空间复杂度：最坏 O(n)（链表），平均 O(log n)（递归栈深度）。
*/
#include <stdlib.h>
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
typedef struct TreeNode TreeNode;
struct TreeNode* invertTree(struct TreeNode* root) {
    if(root==NULL) return NULL;
    if(root->left==NULL&&root->right==NULL)  return root;//这一行可以省略
    TreeNode *left= invertTree(root->right);
    TreeNode *right=invertTree(root->left);
    root->left=left;
    root->right=right;
    return root;
}