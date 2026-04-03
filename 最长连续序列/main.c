#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

/* 哈希函数 */
static unsigned int hashInt(int key, int size) {
    return ((unsigned int)key * 2654435761u) % size;
}

/* 查询 key 是否在哈希集合中 */
static int contains(Node** table, int size, int key) {
    unsigned int idx = hashInt(key, size);
    Node* cur = table[idx];
    while (cur) {
        if (cur->key == key) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

/* 向哈希集合中插入 key（如果已存在则不插入） */
static void insert(Node** table, int size, int key) {
    unsigned int idx = hashInt(key, size);
    Node* cur = table[idx];

    while (cur) {
        if (cur->key == key) {
            return;  // 已存在，直接返回
        }
        cur = cur->next;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->next = table[idx];
    table[idx] = node;
}

/* 释放哈希表 */
static void freeTable(Node** table, int size) {
    for (int i = 0; i < size; i++) {
        Node* cur = table[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(table);
}

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    /* 哈希桶数量开大一点，降低冲突 */
    int tableSize = numsSize * 2 + 1;
    Node** table = (Node**)calloc(tableSize, sizeof(Node*));

    /* 1. 所有元素放入哈希集合 */
    for (int i = 0; i < numsSize; i++) {
        insert(table, tableSize, nums[i]);
    }

    int maxLen = 0;

    /* 2. 遍历哈希集合中的所有唯一元素 */
    for (int i = 0; i < tableSize; i++) {
        Node* cur = table[i];
        while (cur) {
            int x = cur->key;

            /* 只有当 x-1 不存在时，x 才是连续序列起点 */
            if (!contains(table, tableSize, x - 1)) {
                int len = 1;
                int y = x;

                while (contains(table, tableSize, y + 1)) {
                    y++;
                    len++;
                }

                if (len > maxLen) {
                    maxLen = len;
                }
            }

            cur = cur->next;
        }
    }

    freeTable(table, tableSize);
    return maxLen;
}
