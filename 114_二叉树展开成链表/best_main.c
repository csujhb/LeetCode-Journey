#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };
void flatten(struct TreeNode* root) {
    struct TreeNode* curr = root;
    
    while (curr != NULL) {
        if (curr->left != NULL) {
            // 1. 找左子树的最右侧节点 (也就是展开后，右子树应该挂载的位置)
            struct TreeNode* pre = curr->left;
            while (pre->right != NULL) {
                pre = pre->right;
            }
            
            // 2. 将原本的右子树，挂到左子树最右侧节点的右边
            pre->right = curr->right;
            
            // 3. 将整个左子树移到当前节点的右边，并把左子树清空
            curr->right = curr->left;
            curr->left = NULL;
        }
        
        // 4. 继续处理下一个节点（现在左子树已经空了，一路向右走即可）
        curr = curr->right;
    }
}