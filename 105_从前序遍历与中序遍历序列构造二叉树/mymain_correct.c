/*
时间复杂度：O(N)
空间复杂度：O(N)  哈希表+递归
*/

#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 1. 扩大哈希表容量，使用大于 3000*2 的质数，降低哈希冲突概率
#define ARR_SIZE 10007 

typedef struct HashMap {
    int key;    // 值
    int value;  // 下标
    int isused;
} HashMap;

unsigned int hashInt(int val){
    // 2. 修复负数取模的问题，确保下标安全且分布均匀
    return (unsigned int)(((val % ARR_SIZE) + ARR_SIZE) % ARR_SIZE);
}

void hashInsert(HashMap* table, int *arr, int len){
    for(int i = 0; i < len; i++){
        unsigned int idx = hashInt(arr[i]);
        while(table[idx].isused){
            idx = (idx + 1) % ARR_SIZE;
        }
        table[idx].isused = 1;
        table[idx].key = arr[i];
        table[idx].value = i;
    }
}

int getIndex(HashMap* table, int key){
    unsigned int idx = hashInt(key);
    while(table[idx].isused){
        if(table[idx].key == key) return table[idx].value;
        idx = (idx + 1) % ARR_SIZE;
    }
    return -1;
}

struct TreeNode* createNode(int val){
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    return node;
}

// 3. 核心修改：同时传入 preorder 和 inorder 的边界索引
struct TreeNode* buildTree_Helper(HashMap* table, int* preorder, int pre_start, int pre_end, int in_start, int in_end){
    if(pre_start > pre_end || in_start > in_end) return NULL;
    
    int root_value = preorder[pre_start];
    int root_idx = getIndex(table, root_value); // 获取根节点在中序遍历中的下标
    
    struct TreeNode* node = createNode(root_value);
    
    // 计算左子树有多少个节点
    int left_size = root_idx - in_start;
    
    // 递归构建左子树：
    // 前序区间：[pre_start + 1, pre_start + left_size]
    // 中序区间：[in_start, root_idx - 1]
    node->left = buildTree_Helper(table, preorder, pre_start + 1, pre_start + left_size, in_start, root_idx - 1);
    
    // 递归构建右子树：
    // 前序区间：[pre_start + left_size + 1, pre_end]
    // 中序区间：[root_idx + 1, in_end]
    node->right = buildTree_Helper(table, preorder, pre_start + left_size + 1, pre_end, root_idx + 1, in_end);
    
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    HashMap* table = (HashMap*)calloc(ARR_SIZE, sizeof(HashMap));
    hashInsert(table, inorder, inorderSize);
    
    // 初始调用时传入四个边界
    struct TreeNode* root = buildTree_Helper(table, preorder, 0, preorderSize - 1, 0, inorderSize - 1);
    
    // 4. 释放动态分配的哈希表内存
    free(table); 
    
    return root;
}