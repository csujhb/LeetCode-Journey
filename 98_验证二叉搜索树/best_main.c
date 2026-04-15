/*
时间复杂度为 O(N)（每个节点访问一次），空间复杂度为 O(H)（H 为树的高度，主要用于递归调用栈）
*/

#include <stdbool.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 辅助函数，携带了允许的最小值节点指针和最大值节点指针
bool isValidBSTHelper(struct TreeNode* node, struct TreeNode* minNode, struct TreeNode* maxNode) {
    // 空节点默认是合法的 BST
    if (node == NULL) {
        return true;
    }
    
    // 如果当前节点的值小于等于下限，或者大于等于上限，则不合法
    if (minNode != NULL && node->val <= minNode->val) {
        return false;
    }
    if (maxNode != NULL && node->val >= maxNode->val) {
        return false;
    }
    
    // 递归检查左子树：左子树的所有节点都必须小于当前节点（更新 maxNode 为当前 node）
    // 递归检查右子树：右子树的所有节点都必须大于当前节点（更新 minNode 为当前 node）
    return isValidBSTHelper(node->left, minNode, node) && 
           isValidBSTHelper(node->right, node, maxNode);
}

bool isValidBST(struct TreeNode* root) {
    // 初始状态下，根节点没有任何上下界限制，所以传 NULL
    return isValidBSTHelper(root, NULL, NULL);
}