//未成功写出正确答案
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 1000
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
typedef struct TreeNode TreeNode;
bool check(struct TreeNode ** queue,int front,int rear){
    while(front<rear){
        if(queue[front]!=NULL&&queue[rear]!=NULL){
            if(queue[front]->val!=queue[rear]->val) return false;
        }else if(queue[front]==NULL&&queue[rear]==NULL) continue;
        else return false;
    }
    return true;
}

bool isSymmetric(struct TreeNode* root) {
    TreeNode *queue[MAX_SIZE];
    int rear=0;
    int front=0;
    queue[rear++]=root;
    int dep=0;
    while(front<rear){
        TreeNode * node=queue[front++];
        queue[rear++] = node->left;
        queue[rear++] = node->right;
    }
}