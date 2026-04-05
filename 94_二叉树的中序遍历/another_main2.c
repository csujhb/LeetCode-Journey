#include <stdio.h>
#include <stdlib.h>
//方法3:Morris 遍历
/*
 (最极客的解法)时间复杂度：O(N)。
    很多同学看到里面有两层 while 循环，下意识觉得是 O(N^2)。其实不然，你可以把寻找“前驱节点”的过程理解为走树的边。在整个 Morris 遍历中，树里的每一条边最多只会被走 2 次（一次用来建立线索，一次用来拆除线索），所以均摊下来依然是严格的 O(N)。
空间复杂度：O(1)。
    这是它最大的亮点！除了存放结果的 res 数组外，执行过程中只用了 curr 和 pre 两个辅助指针。它巧妙地利用了树底部的空闲 right 指针，完全省去了栈的开销。对于空间要求极其苛刻的嵌入式系统，这是一个满分答案。
*/
// 树节点的定义 (LeetCode 后台已经提供，这里写出来为了方便理解)
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// ==========================================
// 方法三：Morris 遍历 (O(1) 空间复杂度的神仙算法)
// ==========================================
// 核心思想：利用树中大量闲置的（叶子节点）右指针，临时将树连成一条线（建立线索），
// 遍历完再拆掉（恢复树的原貌），从而完全抛弃了栈。
void inorderMorris(struct TreeNode* root, int* res, int* returnSize) {
    struct TreeNode* curr = root;
    struct TreeNode* pre = NULL;

    while (curr != NULL) {
        if (curr->left == NULL) {
            // 如果没有左子树，说明该访问当前节点了，然后向右走
            res[(*returnSize)++] = curr->val;
            curr = curr->right;
        } else {
            // 找当前节点在左子树里的“前驱节点”（即左子树里最右下角的节点）
            pre = curr->left;
            while (pre->right != NULL && pre->right != curr) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                // 第一次访问到前驱：建立线索，把前驱的右指针指向当前节点，然后放心往左走
                pre->right = curr;
                curr = curr->left;
            } else {
                // 第二次访问到前驱：说明左子树已经全遍历完了。断开线索恢复原貌，访问当前节点，往右走
                pre->right = NULL;
                res[(*returnSize)++] = curr->val;
                curr = curr->right;
            }
        }
    }
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
    
    //inorder(root, res, returnSize);          // 方法一：递归法
    // inorderIterative(root, res, returnSize); // 方法二：迭代法(栈)
     inorderMorris(root, res, returnSize);    // 方法三：Morris 遍历
    
    return res;
}