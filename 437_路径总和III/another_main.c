#include <stdio.h>

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
// --- 辅助函数（内层 DFS）：计算必须以 node 为起点的合法路径数量 ---
// 注意：这里的 target 必须用 long long 类型！
// 因为测试用例中节点值可能很大，累加减的过程中普通 int 会发生溢出。
int countPaths(struct TreeNode* node, long long target) {
    if (node == NULL) {
        return 0;
    }
    
    int count = 0;
    
    // 如果当前节点的值刚好等于 target，说明找到了一条路径
    if (node->val == target) {
        count++;
    }
    
    // 关键点：即使找到了目标路径，也不能 return！
    // 因为下面可能有互为相反数的节点（比如往下走遇到 -2 再遇到 2），加上它们又是一条新路径
    count += countPaths(node->left, target - node->val);
    count += countPaths(node->right, target - node->val);
    
    return count;
}

// --- 主函数（外层 DFS）：遍历每一个节点，让它们都有机会做一次起点 ---
int pathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) {
        return 0;
    }
    
    // 1. 让当前 root 作为起点，往下找路径
    int pathsFromRoot = countPaths(root, (long long)targetSum);
    
    // 2. 去左子树里寻找所有的合法路径（相当于把起点的选择权交给了左子树的节点）
    int pathsFromLeft = pathSum(root->left, targetSum);
    
    // 3. 去右子树里寻找所有的合法路径（把起点的选择权交给了右子树的节点）
    int pathsFromRight = pathSum(root->right, targetSum);
    
    // 最终结果 = 根节点开头的路径数 + 左子树里的路径数 + 右子树里的路径数
    return pathsFromRoot + pathsFromLeft + pathsFromRight;
}