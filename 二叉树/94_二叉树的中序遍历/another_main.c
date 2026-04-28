#include <stdio.h>
#include <stdlib.h>
//方法2:迭代法
/*
时间复杂度：O(N)。
    每个节点被压入我们自己创建的栈一次，弹出一次。
空间复杂度：O(H)。
    和递归法基本一致，只是把系统的栈换成了我们自己用 malloc 开辟的数组。最坏情况下栈里也会堆积 O(N) 个节点
*/
// 树节点的定义 (LeetCode 后台已经提供，这里写出来为了方便理解)
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void inorderIterative(struct TreeNode* root, int* res, int* returnSize) {
    // 题目提示节点数最多 100 个，所以分配 100 个容量的栈
    struct TreeNode** stack = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 100);
    int top = -1; // 栈顶指针，-1 表示栈为空
    struct TreeNode* curr = root;

    while (curr != NULL || top != -1) {
        // 1. 顺着左边一直往下走，把路上遇到的节点全部压入栈
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        
        // 2. 走到最左下角（空）了，从栈顶弹出一个节点
        curr = stack[top--];
        
        // 3. 访问这个节点（存入数组）
        res[(*returnSize)++] = curr->val;
        
        // 4. 转向该节点的右子树，继续上面的循环
        curr = curr->right;
    }
    
    free(stack); // 释放我们申请的栈内存
}

/**
 * LeetCode 题目要求的接口
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* res = (int*)malloc(sizeof(int) * 100);
    *returnSize = 0;
    
    // ========================================================
    // 你可以在这里自由切换这三种函数，提交 LeetCode 都能 100% 通过！
    // ========================================================
    
    inorderIterative(root, res, returnSize); // 方法二：迭代法(栈)
    // inorderMorris(root, res, returnSize);    // 方法三：Morris 遍历
    
    return res;
}