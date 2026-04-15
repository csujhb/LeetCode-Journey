/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
//没考虑左子树的右节点与根节点、右子树的左节点与根节点的关系
#include <stdbool.h>
#include <stdlib.h>
struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};
typedef struct TreeNode TreeNode;
bool isValidBST(struct TreeNode* root) {
    if(root==NULL) return true;
    if(root->left==NULL&&root->right==NULL) return true;
    if(root->left){
        if(root->val<=root->left->val) return false;
    }
     if(root->right){
        if(root->val>=root->right->val) return false;
    }
    return isValidBST(root->left)&&isValidBST(root->right);
}