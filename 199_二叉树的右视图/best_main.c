//使用 DFS,代码较为简洁

#include <stdlib.h>
// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void dfs(struct TreeNode* node, int depth, int* res, int* returnSize) {
    if (node == NULL) return;
    
    // 如果当前深度 == 结果数组的大小，说明来到了新的一层
    // 因为我们先遍历右子树，所以这必然是该层最右侧的节点
    if (depth == *returnSize) {
        res[(*returnSize)++] = node->val;
    }
    
    // 关键顺序：先右后左
    dfs(node->right, depth + 1, res, returnSize);
    dfs(node->left, depth + 1, res, returnSize);
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (root == NULL) return NULL;
    
    int* res = (int*)malloc(105 * sizeof(int));
    
    // 从根节点开始，初始深度为 0
    dfs(root, 0, res, returnSize);
    
    return res;
}