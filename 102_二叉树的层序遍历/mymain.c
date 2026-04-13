/*
自己写的有问题：queue[rear]->node=tmp->left;可能访问了一个空指针
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#define MAX_NUM 2000
 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

typedef struct NodeDep{
    struct TreeNode* node;
    int dep;
} NodeDep;
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize=0;
    if(root==NULL) return NULL;
    * returnColumnSizes=(int *)malloc(MAX_NUM*sizeof(int));
    int **res=(int **)malloc(MAX_NUM*sizeof(int*));
    NodeDep* queue[MAX_NUM];
    int front=0,rear=0,lastdep=-1;
    NodeDep p={root,1};
    queue[rear++]=&p;
    int count=0;
    while(front<rear){
         struct TreeNode* tmp=queue[front]->node;
         int dep=queue[front++]->dep;
         if(dep!=lastdep) {
            count=0;
             res[*returnSize]=(int *)malloc(sizeof(int)*2000);
        }
         res[*returnSize][count++]=tmp->val;
         if(tmp->left) {
            queue[rear]->node=tmp->left;
            queue[rear++]->dep=dep+1;
        }
         if(tmp->right) {
            queue[rear]->node=tmp->right;
            queue[rear++]->dep=dep+1;
        }
        (* returnColumnSizes)[*returnSize]=count;
        if(dep!=lastdep) {
            (*returnSize)++;
        }
        lastdep=dep;
    }
    return res;
}