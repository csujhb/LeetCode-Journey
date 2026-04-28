//Definition for a binary tree node.
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };
typedef struct TreeNode TreeNode;

void dfs(TreeNode*node,TreeNode**lastNode){
    if(node==NULL) return;
    TreeNode*left=node->left;
    TreeNode*right=node->right;
    if(lastNode!=NULL&&*lastNode!=NULL) {
        (*lastNode)->left=NULL;
        (*lastNode)->right=node;
    }
    *lastNode=node;
    dfs(left,lastNode);    
    dfs(right,lastNode);
}

void flatten(struct TreeNode* root) {
    if(root==NULL) return;
    TreeNode tmp;
    TreeNode*tmp1=&tmp;
    dfs(root,&tmp1);
}