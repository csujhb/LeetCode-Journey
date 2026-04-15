//使用中序遍历，数值逐渐增大，与二叉搜索树完全符合

/*
时间复杂度：O(N)。在最坏情况下，我们需要访问树中的每一个节点一次。

空间复杂度：O(H)。H是树的高度。空间主要消耗在递归的函数调用栈上。在最坏情况下（树退化成链表），空间复杂度为O(N)；在最好情况下（树完全平衡），空间复杂度为O(log N)。
*/
#include <stdbool.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 辅助函数：执行中序遍历
// 参数 prev 传入的是一个指向指针的指针，用于在递归中同步更新“上一个访问的节点”
bool inorder(struct TreeNode* node, struct TreeNode** prev) {
    // 空节点直接返回 true
    if (node == NULL) {
        return true;
    }
    
    // 1. 遍历左子树 (Left)
    // 如果左子树已经发现不是 BST，直接返回 false，提前剪枝
    if (!inorder(node->left, prev)) {
        return false;
    }
    
    // 2. 处理当前节点 (Root)
    // 检查当前节点的值是否严格大于上一个节点的值
    // 注意：*prev 解引用拿到的是上一个 TreeNode 的指针
    if (*prev != NULL && node->val <= (*prev)->val) {
        return false;
    }
    // 将“上一个节点”更新为当前节点
    *prev = node;
    
    // 3. 遍历右子树 (Right)
    return inorder(node->right, prev);
}

bool isValidBST(struct TreeNode* root) {
    // 初始化 prev 为 NULL
    struct TreeNode* prev = NULL;
    // 传入 prev 的地址
    return inorder(root, &prev);
}