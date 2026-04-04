#include <stdlib.h>

#define HASH_SIZE 100003

typedef struct Node {
    long long key;         // 前缀和
    int count;             // 这个前缀和出现的次数
    struct Node* next;
} Node;

/* 哈希函数：处理负数 */
static int hash(long long key) {
    long long h = key % HASH_SIZE;
    if (h < 0) h += HASH_SIZE;
    return (int)h;
}

/* 查找某个 key 出现了多少次 */
static int findCount(Node** table, long long key) {
    int idx = hash(key);
    Node* cur = table[idx];
    while (cur) {
        if (cur->key == key) {
            return cur->count;
        }
        cur = cur->next;
    }
    return 0;
}

/* 将 key 的出现次数 +1 */
static void insertOrAdd(Node** table, long long key) {
    int idx = hash(key);
    Node* cur = table[idx];

    while (cur) {
        if (cur->key == key) {
            cur->count++;
            return;
        }
        cur = cur->next;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->count = 1;
    node->next = table[idx];
    table[idx] = node;
}

/* 释放哈希表内存 */
static void freeTable(Node** table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* cur = table[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

int subarraySum(int* nums, int numsSize, int k) {
    Node** table = (Node**)calloc(HASH_SIZE, sizeof(Node*));

    long long prefixSum = 0;
    int ans = 0;

    // 前缀和为 0 出现 1 次：表示“从下标 0 开始”的子数组
    insertOrAdd(table, 0);

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];

        // 查找是否存在 prefixSum - k
        ans += findCount(table, prefixSum - k);

        // 当前前缀和加入哈希表
        insertOrAdd(table, prefixSum);
    }

    freeTable(table);
    free(table);

    return ans;
}
