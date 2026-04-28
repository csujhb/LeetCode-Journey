/*
时间 O(N)，空间 O(H)（H 为树高，递归栈开销）
*/
#include <stddef.h>
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };
// struct TreeNode {
//     int val;
//     struct TreeNode *left;
//     struct TreeNode *right;
// };

void dfs(struct TreeNode* node, struct TreeNode** lastNode) {
    if (node == NULL) return;
    
    // 提前保存左右子节点，防止被覆盖后丢失
    struct TreeNode* left = node->left;
    struct TreeNode* right = node->right;
    
    // 如果上一个节点存在，将其连接到当前节点
    if (*lastNode != NULL) {
        (*lastNode)->left = NULL;
        (*lastNode)->right = node;
    }
    
    // 更新 lastNode 为当前节点
    *lastNode = node;
    
    // 按照原来的左右指针继续遍历
    dfs(left, lastNode);    
    dfs(right, lastNode);
}

void flatten(struct TreeNode* root) {
    struct TreeNode* lastNode = NULL; 
    // 传入指针的地址，以便在递归中修改这个指针的指向
    dfs(root, &lastNode);
}