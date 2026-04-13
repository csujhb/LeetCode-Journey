#include <stdlib.h>

 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int max;
int dfs(struct TreeNode* root){
    if(root==NULL) return 0;
    int left_dep=dfs(root->left);
    int rig_dep=dfs(root->right);

    if(left_dep+rig_dep>max) max=left_dep+rig_dep;

    return (left_dep>rig_dep?left_dep:rig_dep)+1;
}
int diameterOfBinaryTree(struct TreeNode* root) {
    max = 0;
    dfs(root);
    return max;
}