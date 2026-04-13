#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode*buildNode(int *arr,int left,int right){
    if(left>right) return NULL;
    int mid=(left+right+1)/2;
    struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode ));
    root->val=arr[mid];
    root->left=buildNode(arr,left,mid-1);
    root->right=buildNode(arr,mid+1,right);
    return root;
}


struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    return buildNode(nums,0,numsSize-1);
}