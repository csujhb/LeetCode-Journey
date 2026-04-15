#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void inorder(struct TreeNode* node, int k,int*count,struct TreeNode**res){
    if(node==NULL) return;
    inorder(node->left,k,count,res);
    (*count)++;
    if((*count)==k){
        *res=node;
        return;
    }
    inorder(node->right,k,count,res);
}

int kthSmallest(struct TreeNode* root, int k) {
    int count=0;
    struct TreeNode*res=NULL;
    inorder(root,k,&count,&res);
    return res->val;
}