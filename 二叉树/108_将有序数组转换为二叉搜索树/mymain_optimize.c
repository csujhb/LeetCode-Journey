/*
时间复杂度： O(N)。其中 N 是数组的长度，每个节点只会被访问和创建一次。

空间复杂度： O(log N)。主要是递归调用栈的空间，因为是一棵高度平衡的二叉树，所以树的高度是 log N。
*/
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* buildNode(int* arr, int left, int right) {
    if (left > right) {
        return NULL;
    }
    
    // 安全地计算中间位置，防止整数溢出 (这里选择左中间节点)
    int mid = left + (right - left) / 2; 
    //mid = left + (right - left + 1)   //右中间节点
    //int mid = left + (right - left) / 2 + rand() % 2 //随机选择左或右中间节点
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = arr[mid];
    
    // 递归构建左右子树
    root->left = buildNode(arr, left, mid - 1);
    root->right = buildNode(arr, mid + 1, right);
    
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0) {
        return NULL;
    }
    return buildNode(nums, 0, numsSize - 1);
}