#include <stdlib.h>
//使用BFS,可以用但是手写队列进行 BFS 会占用固定的线性内存（必须开辟容纳所有节点的数组）
// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize) {
    * returnSize=0;
    if(root==NULL) return NULL;
    int* res=(int*)malloc(105*sizeof(int));
    struct TreeNode* queue[105];
    int front=0,rear=0;
    queue[rear++]=root;
    while(front<rear){
        int len=rear-front;
        for(int i=0;i<len;i++){
            if(queue[front]->left) queue[rear++]=queue[front]->left;
            if(queue[front]->right) queue[rear++]=queue[front]->right;
            front++;
        }
        res[(*returnSize)++]=queue[front-1]->val;
    }
    return res;
}