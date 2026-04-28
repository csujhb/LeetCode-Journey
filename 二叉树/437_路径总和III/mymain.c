//自己写的不对s
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 1. 扩大哈希表容量，使用大于 3000*2 的质数，降低哈希冲突概率
#define HASH_SIZE 10007 

typedef struct HashMap {
    int key;    // 值
    int count;  // 下标
} HashMap;

unsigned int hashInt(int val){
    // 2. 修复负数取模的问题，确保下标安全且分布均匀
    return (unsigned int)(((val % HASH_SIZE) + HASH_SIZE) % HASH_SIZE);
}

void hashInsert(HashMap* table, int key){
        unsigned int idx = hashInt(key);
        while(table[idx].count){
            if(table[idx].key == key){
                table[idx].count++;
                return;
            } 
            idx = (idx + 1) % HASH_SIZE;
        }
        table[idx].key = key;
        table[idx].count = 1;
}

int getCount(HashMap* table, int key){
    unsigned int idx = hashInt(key);
    while(table[idx].count){
        if(table[idx].key == key) return table[idx].count;
        idx = (idx + 1) % HASH_SIZE;
    }
    return 0;
}

int pathSum(struct TreeNode* root, int targetSum) {
    if(root==NULL) return 0;
    HashMap*table=(HashMap*)calloc(HASH_SIZE,calloc);
    table[0].count=1;
    table[0].key=0;
    int premix=0;
    int res=0;
    struct TreeNode**stack=(struct TreeNode**)malloc(1000*sizeof(struct TreeNode*));
    int top=-1;
    stack[++top]=root;
    while(top!=-1){
        struct TreeNode*node=stack[top--];
        premix+=node->val;
        res+=getCount(table,targetSum-premix);
        hashInsert(table,premix);
        int tmp=premix;
        while(node!=NULL){    
            node=node->left;
            if(node) {
                stack[++top]=node; 
                premix+=node->val;
                res+=getCount(table,targetSum-premix);
                hashInsert(table,premix);
            }       
        };


    }
}