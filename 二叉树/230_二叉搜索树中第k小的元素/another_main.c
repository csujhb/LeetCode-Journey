/*
最优算法：迭代法（显式使用栈）
在 C 语言中，递归会带来函数调用栈的开销。对于这种“找到第 k 个就停下”的需求，使用迭代法（模拟栈）往往是工业界和算法面试中更受欢迎的做法。
它的优势在于：到达第 k 个元素后，可以直接 break 或 return 跳出整个循环，完全没有递归回溯的负担。

时间复杂度：O(H + k)
空间复杂度：O(H)
*/
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
int kthSmallest(struct TreeNode* root, int k) {
    // LeetCode 数据规模通常节点数 <= 10^4，这里开辟一个足够大的数组作为栈
    struct TreeNode* stack[10005]; 
    int top = -1;
    struct TreeNode* curr = root;

    while (curr != NULL || top != -1) {
        // 1. 一直向左走，把左边界全部压入栈中
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }

        // 2. 弹出栈顶元素（即当前中序遍历到的最小值）
        curr = stack[top--];
        k--; // 找到一个更小的元素，k 减 1

        // 3. 如果 k 减到 0，说明当前弹出的就是第 k 小的元素
        if (k == 0) {
            return curr->val;
        }

        // 4. 转向右子树
        curr = curr->right;
    }

    return -1; // 理论上如果 k 有效，不会走到这里
}