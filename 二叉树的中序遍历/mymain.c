

#include <stdlib.h>
#define MAX_SIZE 100 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right; 
};

typedef struct TreeNode TreeNode;
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    if(root==NULL) return NULL;
    int *res=(int*)malloc(MAX_SIZE*sizeof(TreeNode));
    static int idx=0;
}