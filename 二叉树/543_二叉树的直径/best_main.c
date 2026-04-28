/*
时间复杂度：O(n)，每个节点访问一次

空间复杂度：O(h)，其中 h 为树的高度，即递归调用栈的深度。最坏情况（退化成链表）为 O(n)，平均情况为 O(log n)


*/
#include <stdlib.h>
#include <math.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int max_diameter;  // 全局变量，记录最大直径

// 返回以 root 为根的子树的最大深度（边数）
int dfs(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    int left_depth = dfs(root->left);   // 左子树最大深度
    int right_depth = dfs(root->right); // 右子树最大深度
    
    // 经过当前节点的直径 = 左深度 + 右深度
    int diameter_through_root = left_depth + right_depth;
    if (diameter_through_root > max_diameter) {
        max_diameter = diameter_through_root;
    }
    
    // 返回当前子树的最大深度（左右较大者 + 1）
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int diameterOfBinaryTree(struct TreeNode* root) {
    max_diameter = 0;
    dfs(root);
    return max_diameter;
}