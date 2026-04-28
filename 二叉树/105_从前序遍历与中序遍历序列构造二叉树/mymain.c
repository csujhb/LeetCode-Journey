/*
自己写的代码的问题：
递归索引混乱（核心问题）
你的 buildTree_Helper 中只传了 start 和 end 两个参数。
在递归左子树时：buildTree_Helper(table, preorder, start + 1, root_idx)。
这里的 start + 1 是前序遍历（preorder）的下标，
而 root_idx 是从哈希表中查出来的中序遍历（inorder）的下标。这两个下标属于不同的数组，
绝对不能混用作为区间的首尾！
*/
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };
#define ARR_SIZE 3000
typedef struct HashMap{
    int key;//值
    int value;//下标
    int isused;
}HashMap;

unsigned int hashInt(int val){
    return (unsigned int)val%ARR_SIZE;
}

void hashInsert(HashMap* table,int *arr,int len){
    for(int i=0;i<len;i++){
        unsigned int idx=hashInt(arr[i]);
        while(table[idx].isused){
            idx=(idx+1)%ARR_SIZE;
        }
        table[idx].isused=1;
        table[idx].key=arr[i];
        table[idx].value=i;
    }
}

int getIndex(HashMap* table,int key){
    unsigned int idx=hashInt(key);
    while(table[idx].isused){
        if(table[idx].key==key) return table[idx].value;
        idx=(idx+1)%ARR_SIZE;
    }
    return -1;
}

struct TreeNode* createNode(int val){
    struct TreeNode*node=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->left=NULL;
    node->right=NULL;
    node->val=val;
    return node;
}

struct TreeNode* buildTree_Helper(HashMap*table,int* preorder,int start,int end){
    if(start>end) return NULL;
    int root_value=preorder[start];
    int root_idx=getIndex(table,root_value);
    struct TreeNode*node=createNode(root_value);
    node->left=buildTree_Helper(table,preorder,start+1,root_idx);
    node->right=buildTree_Helper(table,preorder,root_idx+1,end);
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    HashMap*table=(HashMap*)calloc(ARR_SIZE,sizeof(HashMap));
    hashInsert(table,inorder,inorderSize);
   return buildTree_Helper(table,preorder,0,preorderSize-1);

}