#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#define MIN_VAL -1001
#define MAX(a,b) ((a)>(b)?(a):(b))
//a为根节点
int getMax(int a,int b,int c){
    int res1=MAX(a,MAX(b,c));
    int res2=MAX(a+b,MAX(a+b+c,a+c));
    return MAX(res1,res2);
}

int dfs(struct TreeNode* root,int *max){
    if(root==NULL) return MIN_VAL;
     int l=dfs(root->left,max);
     int r=dfs(root->right,max);
     int v=root->val;
     *max=MAX(getMax(v,l,r),*max);
    return MAX(v,MAX(v+r,v+l));
}

int maxPathSum(struct TreeNode* root) {
    int res=MIN_VAL;
    dfs(root,&res);
    return res;
}