/*方法二：迭代 DFS（显式栈）*/
#include <stdlib.h>
#include <stdbool.h>
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
#define MAX_SIZE 2000

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;

    struct TreeNode* stack[MAX_SIZE][2]; // 存一对节点
    int top = 0;
    stack[top][0] = root->left;
    stack[top][1] = root->right;
    top++;

    while (top > 0) {
        top--;
        struct TreeNode* left  = stack[top][0];
        struct TreeNode* right = stack[top][1];

        if (left == NULL && right == NULL) continue;
        if (left == NULL || right == NULL) return false;
        if (left->val != right->val) return false;

        // 注意入栈顺序：比较 (左的左, 右的右) 和 (左的右, 右的左)
        stack[top][0] = left->left;
        stack[top][1] = right->right;
        top++;
        stack[top][0] = left->right;
        stack[top][1] = right->left;
        top++;
    }
    return true;
}