#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
*/

#define HASH_SIZE 10007

// --- 1. 手写哈希表（拉链法，解决冲突） ---
typedef struct HashNode {
    long long key;      // 记录前缀和的值
    int count;          // 这个前缀和出现的次数
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode* buckets[HASH_SIZE];
} HashMap;

HashMap* createMap() {
    // calloc 会自动将所有指针初始化为 NULL
    return (HashMap*)calloc(1, sizeof(HashMap)); 
}

// 负数取模安全处理
int getHash(long long key) {
    long long val = key % HASH_SIZE;
    if (val < 0) val += HASH_SIZE;
    return (int)val;
}

// 在哈希表中增加或减少某个前缀和的次数 (delta 为 1 或 -1)
void put(HashMap* map, long long key, int delta) {
    int idx = getHash(key);
    HashNode* curr = map->buckets[idx];
    
    // 查找是否已经存在该前缀和
    while (curr != NULL) {
        if (curr->key == key) {
            curr->count += delta;
            return;
        }
        curr = curr->next;
    }
    
    // 如果是增加新的前缀和且不存在，新建节点头插法入链表
    if (delta > 0) {
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->count = delta;
        newNode->next = map->buckets[idx];
        map->buckets[idx] = newNode;
    }
}

// 查询某个前缀和出现的次数
int get(HashMap* map, long long key) {
    int idx = getHash(key);
    HashNode* curr = map->buckets[idx];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->count;
        }
        curr = curr->next;
    }
    return 0;
}

// 释放哈希表内存（良好的工程习惯）
void freeMap(HashMap* map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = map->buckets[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(map);
}

// --- 2. 核心 DFS 逻辑 ---
int dfs(struct TreeNode* node, HashMap* map, long long curr_sum, int targetSum) {
    if (node == NULL) {
        return 0;
    }
    
    // 1. 更新当前路径的前缀和
    curr_sum += node->val;
    
    // 2. 核心步骤：去哈希表里查，有没有出现过 curr_sum - targetSum 的前缀和？
    int res = get(map, curr_sum - targetSum);
    
    // 3. 把当前的前缀和加入哈希表，供它的子节点使用
    put(map, curr_sum, 1);
    
    // 4. 递归去左子树和右子树里继续寻找
    res += dfs(node->left, map, curr_sum, targetSum);
    res += dfs(node->right, map, curr_sum, targetSum);
    
    // 5. 灵魂步骤：回溯！
    // 左右子树都找完了，要退回父节点了，当前节点的前缀和不能带给其他分支，必须撤销！
    put(map, curr_sum, -1);
    
    return res;
}

// --- 3. 主函数 ---
int pathSum(struct TreeNode* root, int targetSum) {
    HashMap* map = createMap();
    
    // 极其重要的一步：初始化前缀和为 0 的次数为 1。
    // 意义在于：如果从根节点到当前节点的总和本身就等于 targetSum，
    // 那么 curr_sum - targetSum = 0。我们要让它能在哈希表里查到 1 条路径。
    put(map, 0, 1);
    
    int total_paths = dfs(root, map, 0, targetSum);
    
    freeMap(map);
    return total_paths;
}