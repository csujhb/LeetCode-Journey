#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 定义一个结构体，用来打包保存节点和它需要处理的数组区间
struct Task {
    struct TreeNode* node;
    int left;
    int right;
};

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0) {
        return NULL;
    }

    // 先创建根节点（此时先不赋值）
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;

    // 模拟一个队列。因为是二叉树，队列的最大长度不会超过节点总数 numsSize
    struct Task* queue = (struct Task*)malloc(sizeof(struct Task) * numsSize);
    int head = 0; // 队头指针
    int tail = 0; // 队尾指针

    // 将根节点和完整的数组区间作为一个初始“任务”入队
    queue[tail].node = root;
    queue[tail].left = 0;
    queue[tail].right = numsSize - 1;
    tail++;

    // 当队列不为空时，循环处理任务
    while (head < tail) {
        // 出队：取出当前的任务
        struct Task current = queue[head++];
        struct TreeNode* currNode = current.node;
        int l = current.left;
        int r = current.right;

        // 计算中间位置，并给当前节点赋值
        int mid = l + (r - l) / 2;
        currNode->val = nums[mid];

        // 处理左半区间：如果左边还有元素，说明存在左子树
        if (l <= mid - 1) {
            // 创建左子节点
            currNode->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            currNode->left->left = NULL;
            currNode->left->right = NULL;
            
            // 将左子节点和左半区间打包成新任务，入队
            queue[tail].node = currNode->left;
            queue[tail].left = l;
            queue[tail].right = mid - 1;
            tail++;
        }

        // 处理右半区间：如果右边还有元素，说明存在右子树
        if (mid + 1 <= r) {
            // 创建右子节点
            currNode->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            currNode->right->left = NULL;
            currNode->right->right = NULL;
            
            // 将右子节点和右半区间打包成新任务，入队
            queue[tail].node = currNode->right;
            queue[tail].left = mid + 1;
            queue[tail].right = r;
            tail++;
        }
    }

    // 释放队列使用的内存
    free(queue);
    
    return root;
}