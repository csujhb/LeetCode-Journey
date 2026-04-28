#include <stdlib.h>
 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };
 int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) {
        *returnColumnSizes = NULL;
        return NULL;
    }
    int capacity=100;
    int **res=(int**)malloc(capacity*sizeof(int*));
    *returnColumnSizes=(int *)malloc(capacity*sizeof(int));

    struct TreeNode*queue[2000];
    int front=0,rear=0;
    queue[rear++]=root;
    while(rear>front){
        int num=rear-front;
        int *tmp=(int*)malloc(num*sizeof(int));
        for(int i=0;i<num;i++){
            struct TreeNode* node=queue[front++];
            tmp[i]=node->val;
            if(node->left) queue[rear++]=node->left;
            if(node->right) queue[rear++]=node->right;
        }
        (*returnColumnSizes)[*returnSize]=num;
        res[*returnSize]=tmp;
        (*returnSize)++;
        if (*returnSize >= capacity) {
            capacity *= 2;
            res = (int**)realloc(res, sizeof(int*) * capacity);
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * capacity);
        }
    }
    return res;
 }