//与我方法相反，使用了右-左-根，不用担心右子节点丢失
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };
void dfs_reverse(struct TreeNode* node, struct TreeNode** nextNode) {
    if (node == NULL) return;
    
    // 遍历顺序：右 -> 左 -> 根
    dfs_reverse(node->right, nextNode);
    dfs_reverse(node->left, nextNode);
    
    // 处理当前节点：接上后面的链表，清空左指针
    node->right = *nextNode;
    node->left = NULL;
    
    // 将自己作为下一个节点的“后继节点”
    *nextNode = node;
}

void flatten(struct TreeNode* root) {
    struct TreeNode* nextNode = NULL;
    dfs_reverse(root, &nextNode);
}