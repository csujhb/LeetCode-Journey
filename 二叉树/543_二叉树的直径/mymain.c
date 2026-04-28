//写的还是不对
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdlib.h>

 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int getDepth(struct TreeNode* root){
    if(root==NULL) return 0;
    int left=getDepth(root->left);
    int right=getDepth(root->right);
    return 1+(right>left?right:left);
}

int getmax(int a,int b,int c){
    if(a>b){
        if(a>c) return a;
        else return c;
    }else{
        if(b<c) return c;
        else return b;
    }
}

int diameterOfBinaryTree(struct TreeNode* root) {
    if(root==NULL) return 0;
    return getmax(getDepth(root->left)+getDepth(root->right)+1,1,1);
}