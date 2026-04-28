/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdio.h>
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};

typedef struct TreeNode TreeNode;
 int maxDepth(struct TreeNode* root) {
    if(root==NULL)  return 0;
      int res1=maxDepth(root->left)+1;
      int res2=maxDepth(root->right)+1;
      return res1>res2?res1:res2;
}