/*
* 时间复杂度：O(N)（每个节点严格被访问和处理一次）
* 空间复杂度：O(1)（如果不算递归系统栈的消耗，没有额外开辟任何数据结构）
*/
#include <stdlib.h>

/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
*/
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 辅助递归函数
struct TreeNode* build(int* preorder, int preorderSize, int* p_pre, 
                       int* inorder, int* p_in, int stop) {
    // 1. 如果前序遍历的节点都用光了，说明树建完了
    if (*p_pre >= preorderSize) {
        return NULL;
    }
    
    // 2. 如果中序遍历当前指向的值 == 传进来的停止标志
    // 说明当前子树已经没有剩余节点了，要回溯
    if (inorder[*p_in] == stop) {
        (*p_in)++; // 中序指针往前走一步，越过这个根节点
        return NULL;
    }
    
    // 3. 从前序数组拿出一个值，作为当前根节点
    int root_val = preorder[(*p_pre)++];
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = root_val;
    
    // 4. 构建左子树：一直向左走，直到遇到当前节点的值为止
    node->left = build(preorder, preorderSize, p_pre, inorder, p_in, root_val);
    
    // 5. 构建右子树：左边都建完了，继续建右边，右边的停止条件和父节点一致
    node->right = build(preorder, preorderSize, p_pre, inorder, p_in, stop);
    
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int pre_idx = 0; // 追踪前序数组走到了哪里
    int in_idx = 0;  // 追踪中序数组走到了哪里
    
    // 题目给出节点值的范围是 -3000 <= Node.val <= 3000
    // 所以取 3001 这个不可能出现的值作为最外层的初始停止标志
    return build(preorder, preorderSize, &pre_idx, inorder, &in_idx, 3001);
}