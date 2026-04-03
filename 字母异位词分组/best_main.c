#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// 每个键是 26 个 16 位整数（支持字符串长度 ≤ 10000）
typedef uint16_t Key[26];

// 哈希表条目，开放定址法
typedef struct {
    Key key;        // 频次键
    int groupIndex; // 所属组索引
    int used;       // 是否被占用（1=已占用，0=空闲）
} HashEntry;

// 哈希表结构
typedef struct {
    HashEntry* entries;
    int capacity;   // 表大小（质数）
    int size;       // 已存储条目数
} HashTable;

// 组结构（动态数组存储字符串指针）
typedef struct {
    char** words;
    int size;
    int capacity;
} Group;

// 简单高效的哈希函数（对 Key 的 52 字节计算 djb2 变种）
static unsigned int hashKey(const Key key, int tableSize) {
    unsigned int hash = 5381;
    // 将 26 个 uint16_t 视为 52 字节依次处理
    const unsigned char* p = (const unsigned char*)key;
    for (int i = 0; i < 26 * sizeof(uint16_t); i++) {
        hash = ((hash << 5) + hash) ^ p[i];
    }
    return hash % tableSize;
}

// 创建哈希表
static HashTable* createHashTable(int capacity) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->entries = (HashEntry*)calloc(capacity, sizeof(HashEntry));
    return ht;
}

// 释放哈希表
static void freeHashTable(HashTable* ht) {
    free(ht->entries);
    free(ht);
}

// 查找键对应的组索引，若不存在返回 -1
static int findGroup(HashTable* ht, const Key key) {
    int idx = hashKey(key, ht->capacity);
    while (ht->entries[idx].used) {
        if (memcmp(ht->entries[idx].key, key, sizeof(Key)) == 0) {
            return ht->entries[idx].groupIndex;
        }
        idx = (idx + 1) % ht->capacity; // 线性探测
    }
    return -1;
}

// 插入新键值对（假设键一定不存在）
static void insertGroup(HashTable* ht, const Key key, int groupIndex) {
    int idx = hashKey(key, ht->capacity);
    while (ht->entries[idx].used) {
        idx = (idx + 1) % ht->capacity;
    }
    memcpy(ht->entries[idx].key, key, sizeof(Key));
    ht->entries[idx].groupIndex = groupIndex;
    ht->entries[idx].used = 1;
    ht->size++;
}

// 扩容哈希表（当负载因子 > 0.75 时调用）
static void expandHashTable(HashTable** ht, int newCapacity) {
    HashTable* old = *ht;
    HashTable* newHt = createHashTable(newCapacity);
    // 重新插入所有旧条目
    for (int i = 0; i < old->capacity; i++) {
        if (old->entries[i].used) {
            insertGroup(newHt, old->entries[i].key, old->entries[i].groupIndex);
        }
    }
    freeHashTable(old);
    *ht = newHt;
}

// 构建频次键
static void buildKey(const char* s, Key key) {
    int count[26] = { 0 };
    while (*s) {
        count[*s - 'a']++;
        s++;
    }
    for (int i = 0; i < 26; i++) {
        key[i] = (uint16_t)count[i];
    }
}

// 主函数：字母异位词分组
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (strsSize == 0) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 初始哈希表大小（选择质数，这里简单取 2*strsSize+1 并确保为质数，为简化直接使用）
    int initCapacity = strsSize * 2 + 1;
    HashTable* ht = createHashTable(initCapacity);

    // 最多 strsSize 个组
    Group* groups = (Group*)malloc(sizeof(Group) * strsSize);
    int groupCount = 0;

    for (int i = 0; i < strsSize; i++) {
        Key key;
        buildKey(strs[i], key);

        int idx = findGroup(ht, key);
        if (idx == -1) {
            // 新建组
            idx = groupCount++;
            groups[idx].size = 0;
            groups[idx].capacity = 4;   // 初始容量
            groups[idx].words = (char**)malloc(sizeof(char*) * groups[idx].capacity);
            // 插入哈希表（若负载因子过高则扩容）
            if (ht->size * 4 > ht->capacity * 3) { // 负载因子 > 0.75
                expandHashTable(&ht, ht->capacity * 2 + 1);
            }
            insertGroup(ht, key, idx);
        }

        // 将当前字符串指针加入对应组
        Group* g = &groups[idx];
        if (g->size == g->capacity) {
            g->capacity *= 2;
            g->words = (char**)realloc(g->words, sizeof(char*) * g->capacity);
        }
        g->words[g->size++] = strs[i];
    }

    // 构造返回结果
    char*** result = (char***)malloc(sizeof(char**) * groupCount);
    *returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);
    for (int i = 0; i < groupCount; i++) {
        result[i] = groups[i].words;
        (*returnColumnSizes)[i] = groups[i].size;
    }

    *returnSize = groupCount;

    // 释放临时数据结构（注意 groups[i].words 已转移给 result，无需释放）
    free(groups);
    freeHashTable(ht);

    return result;
}
