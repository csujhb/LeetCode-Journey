

---

# 力扣 49. 字母异位词分组 学习笔记

## 题目描述

给你一个字符串数组 `strs`，请你将 **字母异位词** 组合在一起，可以按任意顺序返回结果列表。

### 字母异位词的定义

如果两个字符串包含的字符种类相同，并且每种字符出现的次数也完全相同，只是字符顺序不同，那么它们就是字母异位词。

例如：
- `"eat"`、`"tea"`、`"ate"` 是一组
- `"tan"`、`"nat"` 是一组
- `"bat"` 单独一组


---

##  题目本质

这道题的核心不在“比较两个字符串是否相同”，而在于：

> **如何给每个字符串构造一个“特征 key”，使得同一组字母异位词拥有相同的 key？**

只要 key 一样，就说明这些字符串应该分到同一组。

---

## 常见两种解法

这题最常见有两种思路：

### 方法一：排序后作为 key
把每个字符串排序，排序结果相同的分到一组。
例如：`"eat"`、`"tea"`、`"ate"` 排序后均为 `"aet"`。

### 方法二：统计 26 个字母频次作为 key

统计每个字符串中 `a-z` 出现的次数。只要频次完全相同，它们就是字母异位词。

---

# 方法一：排序后作为 key

##  思路

对每个字符串：
1. 复制一份字符串。
2. 对复制后的字符串排序。
3. 把排好序的字符串作为 key。
4. 用哈希表维护 `key -> 组号` 的映射。
5. 相同 key 的字符串放到同一组。

---

## 示例分析

输入：`["eat","tea","tan","ate","nat","bat"]`

排序后映射：
* `"aet"` -> `["eat","tea","ate"]`
* `"ant"` -> `["tan","nat"]`
* `"abt"` -> `["bat"]`

---

## C 语言实现思路

* **排序**：使用标准库的 `qsort`。
* **哈希表**：存储排序后的字符串作为 key，以及对应组的下标。
* **动态数组**：每组用动态数组保存字符串指针。

---

## 排序法参考代码

```c
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* key;
    int groupIndex;
    struct Node* next;
} Node;

typedef struct {
    char** words;
    int size;
    int capacity;
} Group;

static char* strDup(const char* s) {
    int len = (int)strlen(s);
    char* p = (char*)malloc(len + 1);
    strcpy(p, s);
    return p;
}

static int cmpChar(const void* a, const void* b) {
    return (*(const char*)a - *(const char*)b);
}

static unsigned int hashString(const char* s) {
    unsigned int hash = 5381;
    while (*s) {
        hash = hash * 33 + (unsigned char)(*s);
        s++;
    }
    return hash;
}

static int findGroup(Node** table, int tableSize, const char* key) {
    unsigned int idx = hashString(key) % tableSize;
    Node* cur = table[idx];
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            return cur->groupIndex;
        }
        cur = cur->next;
    }
    return -1;
}

static void insertGroup(Node** table, int tableSize, const char* key, int groupIndex) {
    unsigned int idx = hashString(key) % tableSize;
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = strDup(key);
    node->groupIndex = groupIndex;
    node->next = table[idx];
    table[idx] = node;
}

static void freeTable(Node** table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        Node* cur = table[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(table);
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int tableSize = strsSize * 2 + 1;
    Node** table = (Node**)calloc(tableSize, sizeof(Node*));
    Group* groups = (Group*)malloc(sizeof(Group) * strsSize);
    int groupCount = 0;

    for (int i = 0; i < strsSize; i++) {
        char* sorted = strDup(strs[i]);
        qsort(sorted, strlen(sorted), sizeof(char), cmpChar);

        int idx = findGroup(table, tableSize, sorted);
        if (idx == -1) {
            idx = groupCount++;
            groups[idx].size = 0;
            groups[idx].capacity = 4;
            groups[idx].words = (char**)malloc(sizeof(char*) * groups[idx].capacity);
            insertGroup(table, tableSize, sorted, idx);
        }

        if (groups[idx].size == groups[idx].capacity) {
            groups[idx].capacity *= 2;
            groups[idx].words = (char**)realloc(groups[idx].words, sizeof(char*) * groups[idx].capacity);
        }
        groups[idx].words[groups[idx].size++] = strs[i];
        free(sorted);
    }

    char*** result = (char***)malloc(sizeof(char**) * groupCount);
    *returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);
    for (int i = 0; i < groupCount; i++) {
        result[i] = groups[i].words;
        (*returnColumnSizes)[i] = groups[i].size;
    }
    *returnSize = groupCount;

    free(groups);
    freeTable(table, tableSize);
    return result;
}
```

---

## 排序法复杂度分析

* **时间复杂度**：$O(n \cdot k \log k)$，其中 $n$ 为字符串个数，$k$ 为平均长度。
* **空间复杂度**：$O(n \cdot k)$，用于存储哈希表中的 key 副本及分组结果。

---

# 方法二：统计 26 个字母频次作为 key

## 思路

将每个字符串表示为一个 26 维频次数组 `[a的个数, b的个数, ..., z的个数]`。
两个字符串是字母异位词，当且仅当它们的频次数组完全一致。

---

##  频次统计法参考代码

```c
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint16_t Key[26];

typedef struct {
    Key key;
    int groupIndex;
    int used;
} HashEntry;

typedef struct {
    HashEntry* entries;
    int capacity;
    int size;
} HashTable;

typedef struct {
    char** words;
    int size;
    int capacity;
} Group;

static unsigned int hashKey(const Key key, int tableSize) {
    unsigned int hash = 5381;
    const unsigned char* p = (const unsigned char*)key;
    for (int i = 0; i < 26 * sizeof(uint16_t); i++) {
        hash = ((hash << 5) + hash) ^ p[i];
    }
    return hash % tableSize;
}

static HashTable* createHashTable(int capacity) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->entries = (HashEntry*)calloc(capacity, sizeof(HashEntry));
    return ht;
}

static void freeHashTable(HashTable* ht) {
    free(ht->entries);
    free(ht);
}

static int findGroup(HashTable* ht, const Key key) {
    int idx = hashKey(key, ht->capacity);
    while (ht->entries[idx].used) {
        if (memcmp(ht->entries[idx].key, key, sizeof(Key)) == 0) {
            return ht->entries[idx].groupIndex;
        }
        idx = (idx + 1) % ht->capacity;
    }
    return -1;
}

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

static void buildKey(const char* s, Key key) {
    memset(key, 0, sizeof(Key));
    while (*s) {
        key[*s - 'a']++;
        s++;
    }
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int initCapacity = strsSize * 2 + 1;
    HashTable* ht = createHashTable(initCapacity);
    Group* groups = (Group*)malloc(sizeof(Group) * strsSize);
    int groupCount = 0;

    for (int i = 0; i < strsSize; i++) {
        Key key;
        buildKey(strs[i], key);
        int idx = findGroup(ht, key);
        if (idx == -1) {
            idx = groupCount++;
            groups[idx].size = 0;
            groups[idx].capacity = 4;
            groups[idx].words = (char**)malloc(sizeof(char*) * groups[idx].capacity);
            insertGroup(ht, key, idx);
        }
        Group* g = &groups[idx];
        if (g->size == g->capacity) {
            g->capacity *= 2;
            g->words = (char**)realloc(g->words, sizeof(char*) * g->capacity);
        }
        g->words[g->size++] = strs[i];
    }

    char*** result = (char***)malloc(sizeof(char**) * groupCount);
    *returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);
    for (int i = 0; i < groupCount; i++) {
        result[i] = groups[i].words;
        (*returnColumnSizes)[i] = groups[i].size;
    }
    *returnSize = groupCount;

    free(groups);
    freeHashTable(ht);
    return result;
}
```

---

##  频次统计法复杂度分析

* **时间复杂度**：平均 $O(n \cdot k)$，因为只需遍历一次字符串构造 key。
* **空间复杂度**：$O(n)$，哈希表存储组索引，不复制原字符串内容。

---

## 两种方法对比

| 方法 | key 设计 | 时间复杂度 | 空间复杂度 | 优点 | 缺点 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **排序法** | 排序后的字符串 | $O(n \cdot k \log k)$ | $O(n \cdot k)$ | 简单直观 | 性能略差 |
| **频次统计法** | 26 字母频次数组 | 平均 $O(n \cdot k)$ | $O(n)$ | 更高效 | 实现较复杂 |

---

## 易错点总结

1.  **频次 vs 集合**：必须比较字符**频次**，仅比较字符种类是不够的（如 `"a"` 和 `"aa"`）。
2.  **原地修改**：排序时不要直接修改原字符串，应使用副本。
3.  **哈希冲突**：必须处理哈希冲突并比较真实的 key。
4.  **返回格式**：C 语言中 `returnSize` 和 `returnColumnSizes` 必须正确分配并赋值。

---

##  一句话总结

> **核心是为每个字符串构造一个“特征 key”（通过排序或频次统计），并利用哈希表进行高效分组。**