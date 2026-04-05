#include <stdio.h>
#include <stdlib.h>
//方法1:递归法
/*
时间复杂度：O(N)。
    无论树长什么样，每个节点都恰好被访问且仅被访问一次。
空间复杂度：O(H)（H 为树的高度）。
    系统需要使用隐式的“函数调用栈”。最坏情况下（树退化成一条直线的链表），深度为 N，空间是 O(N)；平均情况（平衡二叉树），深度是 log N，空间是 O(log N)。
*/
// 树节点的定义 (LeetCode 后台已经提供，这里写出来为了方便理解)
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * 辅助递归函数
 * @param root 当前遍历到的节点
 * @param res 存放结果的数组
 * @param returnSize 这是一个【指针】，指向主函数中的索引变量，确保所有递归层级共享同一个索引
 */
void inorder(struct TreeNode* root, int* res, int* returnSize) {
    if (root == NULL) {
        return;
    }

    // 1. 递归遍历左子树
    inorder(root->left, res, returnSize);

    // 2. 访问当前节点（这是核心逻辑：存入数组并增加索引）
    
    // 【索引是如何工作的？】
    // *returnSize 表示取出指针指向的值（即当前的索引数字，最开始是 0）
    // 把当前节点的值，放到 res 数组的第 *returnSize 个位置
    res[*returnSize] = root->val;
    
    // 存完之后，把指针指向的那个索引值加 1，这样下一次递归存的时候，就会存在下一个格子里
    (*returnSize)++; 
    
    /* * 上面两行代码也可以简写成一行非常经典的 C 语言写法：
     * res[(*returnSize)++] = root->val;
     * 意思是：先用当前的 *returnSize 作为索引赋值，然后再把 *returnSize 加 1。
     */

    // 3. 递归遍历右子树
    inorder(root->right, res, returnSize);
}

/**
 * LeetCode 题目要求的接口
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    // 题目提示节点数最多 100 个，所以我们直接分配 100 个 int 的空间
    int* res = (int*)malloc(sizeof(int) * 100);
    
    // 初始化返回数组的元素个数（即初始索引）为 0
    // 注意：这里的 returnSize 本身就是 LeetCode 传进来的指针，用来告诉后台数组有多大
    *returnSize = 0;
    
    // 调用辅助函数开始递归遍历
    // 我们把 returnSize 这个指针一直传进去，让递归函数去修改它
    inorder(root, res, returnSize);
    
    // 返回装满数据的数组
    return res;
}