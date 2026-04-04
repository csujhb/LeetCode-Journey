# 力扣 49. 字母异位词分�?学习笔记

## 1. 题目描述

给你一个字符串数组 `strs`，请你将 **字母异位�?* 组合在一起，可以按任意顺序返回结果列表�?

### 字母异位词的定义
如果两个字符串包含的字符种类相同，并且每种字符出现的次数也完全相同，只是字符顺序不同，那么它们就是字母异位词�?

例如�?

- `"eat"`、`"tea"`、`"ate"` 是一�?
- `"tan"`、`"nat"` 是一�?
- `"bat"` 单独一�?

---

## 2. 题目本质

这道题的核心不在“比较两个字符串是否相同”，而在于：

> **如何给每个字符串构造一个“特�?key”，使得同一组字母异位词拥有相同�?key�?*

只要 key 一样，就说明这些字符串应该分到同一组�?

---

## 3. 常见两种解法

这题最常见有两种思路�?

### 方法一：排序后作为 key
把每个字符串排序，排序结果相同的分到一组�?

例如�?

- `"eat"` 排序后是 `"aet"`
- `"tea"` 排序后也�?`"aet"`
- `"ate"` 排序后还�?`"aet"`

所以这三个字符串应该分到同一组�?

---

### 方法二：统计 26 个字母频次作�?key
因为题目保证字符串只包含小写字母，所以可以统计每个字符串中：

- `a` 出现几次
- `b` 出现几次
- ...
- `z` 出现几次

只要两个字符串这 26 个字母的频次完全相同，它们就是字母异位词�?

例如 `"eat"`�?

- a: 1
- e: 1
- t: 1
- 其余字母: 0

那么 `"tea"`、`"ate"` 的频次统计也完全相同�?

---

# 方法一：排序后作为 key

## 4. 思路

对每个字符串�?

1. 复制一份字符串
2. 对复制后的字符串排序
3. 把排好序的字符串作为 key
4. 用哈希表维护�?
   ```text
   key -> 组号

5. 相同 key 的字符串放到同一�?

---

## 5. 示例分析

输入�?

```text
["eat","tea","tan","ate","nat","bat"]
```

排序后：

* `"eat"` -> `"aet"`
* `"tea"` -> `"aet"`
* `"tan"` -> `"ant"`
* `"ate"` -> `"aet"`
* `"nat"` -> `"ant"`
* `"bat"` -> `"abt"`

于是分组结果是：

```text
"aet" -> ["eat","tea","ate"]
"ant" -> ["tan","nat"]
"abt" -> ["bat"]
```

---

## 6. C 语言实现思路

### 6.1 排序单个字符�?

可以对字符串副本使用 `qsort`�?

### 6.2 哈希�?

哈希表里存：

* 排序后的字符�?key
* 对应组的下标

### 6.3 动态数组存组内元素

每组用动态数组保存字符串指针�?

---

## 7. 排序法参考代�?

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
    *returnSize = 0;
    if (strsSize == 0) {
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
            groups[idx].words = (char**)realloc(groups[idx].words,
                                sizeof(char*) * groups[idx].capacity);
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

## 8. 排序法复杂度分析

设：

* `n = strsSize`，字符串个数
* `k = 平均字符串长度`

### 时间复杂�?

每个字符串排序需要：

```text
O(k log k)
```

总共 `n` 个字符串，因此总时间复杂度为：

```text
O(n * k log k)
```

### 空间复杂�?

* 哈希表存组信息：`O(n)`
* 分组结果：`O(n)`
* 每次排序时临时复制字符串：单�?`O(k)`

总体可记为：

```text
O(n * k)
```

如果只考虑额外辅助结构，也可以近似记为�?

```text
O(n)
```

但由�?key 是排序后的字符串副本，严格说和字符串长度也有关�?

---

## 9. 排序法优缺点

### 优点

* 思路最直观
* 容易理解
* 容易�?

### 缺点

* 每个字符串都要排�?
* 当字符串较长时，性能不如频次统计�?

---

# 方法二：统计 26 个字母频次作�?key

## 10. 思路

因为题目只包含小写字母，所以每个字符串都可以唯一表示为一�?26 维频次数组：

```text
[a的个�? b的个�? c的个�? ..., z的个数]
```

对于每个字符串：

1. 统计 26 个字母出现次�?
2. 把这个频次数组作�?key
3. 用哈希表维护�?

   ```text
   key -> 组号
   ```
4. 相同频次数组的字符串放进同一�?

---

## 11. 为什么这种方法正�?

因为两个字符串互为字母异位词，当且仅当：

> **这两个字符串�?26 个字母的出现次数完全一致�?*

所以“频次数组”可以作为这道题最本质的特征�?

---

## 12. 两种频次 key 的实现方�?

### 方式 A：把频次数组拼成字符�?key

例如�?

```text
#1#0#0#0#1#0#0...
```

这样实现比较直观，但会有字符串拼接和比较的额外开销�?

### 方式 B：直接用 `Key[26]` 作为二进�?key

例如�?

```c
typedef uint16_t Key[26];
```

这是更高效、更底层的写法�?

下面重点写这种方式�?

---

## 13. 频次统计法参考代码（固定 26 �?key�?

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

static void expandHashTable(HashTable** ht, int newCapacity) {
    HashTable* old = *ht;
    HashTable* newHt = createHashTable(newCapacity);

    for (int i = 0; i < old->capacity; i++) {
        if (old->entries[i].used) {
            insertGroup(newHt, old->entries[i].key, old->entries[i].groupIndex);
        }
    }

    freeHashTable(old);
    *ht = newHt;
}

static void buildKey(const char* s, Key key) {
    memset(key, 0, sizeof(Key));
    while (*s) {
        key[*s - 'a']++;
        s++;
    }
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (strsSize == 0) {
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

            if (ht->size * 4 > ht->capacity * 3) {
                expandHashTable(&ht, ht->capacity * 2 + 1);
            }

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

## 14. 频次统计法复杂度分析

设：

* `n = strsSize`
* `k = 平均字符串长度`
* `L = 所有字符串总长度`

其中�?

```text
L = sum(len(strs[i]))
```

### 时间复杂�?

#### 1）构�?key

对每个字符串统计字符频次，需要遍历整个字符串�?

```text
O(k)
```

所有字符串总计�?

```text
O(L)
```

#### 2）哈希查�?/ 插入

平均情况下：

```text
O(1)
```

#### 3）总时间复杂度

因此总体平均复杂度为�?

```text
O(L + n)
```

通常写成�?

```text
O(n * k)
```

#### 4）最坏时间复杂度

如果哈希冲突极端严重，开放定址查找可能退化，最坏接近：

```text
O(n^2 + L)
```

但正常情况下通常按平均复杂度分析�?

---

### 空间复杂�?

#### 哈希�?

```text
O(n)
```

#### 分组数组

```text
O(n)
```

#### 组内字符串指�?

总共保存 `n` 个字符串指针�?

```text
O(n)
```

#### 总空间复杂度

整体额外空间复杂度为�?

```text
O(n)
```

如果把返回结果一起算上，仍然可以记作�?

```text
O(n)
```

因为没有复制字符串内容，只保存字符串指针�?

---

## 15. 频次统计法优缺点

### 优点

* 不需要排�?
* 理论复杂度更�?
* 对本题“小写字母”场景非常适合
* 直接抓住了“异位词”的本质特征

### 缺点

* 实现复杂度更�?
* 自己写哈希表时，代码量大
* 不如排序法直�?

---

# 两种方法对比

## 16. 复杂度对比表

| 方法    | key 设计     |            时间复杂�?|             空间复杂�?| 优点        | 缺点             |
| ----- | ---------- | ---------------: | ----------------: | --------- | -------------- |
| 排序�?  | 排序后的字符�?   | `O(n * k log k)` | `O(n)` �?`O(n*k)` | 简单直观，容易实现 | 每个字符串都要排序，性能略差 |
| 频次统计�?| 26 个字母频次数�?|    平均 `O(n * k)` |            `O(n)` | 更高效，更贴近本�?| 实现更复�?         |

---

## 17. 如何选择

### 如果你是初学�?

优先掌握 **排序�?*，因为它最容易理解和写出来�?

### 如果你追求更优复杂度

优先掌握 **频次统计�?*，尤其是题目限定为“小写字母”时，它更合适�?

### 如果是面�?

推荐先说�?

1. 可以排序作为 key
2. 但排序每次要 `O(k log k)`
3. 由于题目字符集固定为 26 个小写字母，所以可以进一步优化成频次统计法，把复杂度降到平均 `O(n*k)`

这样会显得思路完整�?

---

# 18. 示例完整分析

输入�?

```text
["eat","tea","tan","ate","nat","bat"]
```

---

## 用排序法

* `"eat"` -> `"aet"`
* `"tea"` -> `"aet"`
* `"tan"` -> `"ant"`
* `"ate"` -> `"aet"`
* `"nat"` -> `"ant"`
* `"bat"` -> `"abt"`

结果�?

```text
"aet" -> ["eat","tea","ate"]
"ant" -> ["tan","nat"]
"abt" -> ["bat"]
```

---

## 用频次统计法

### `"eat"`

* a:1
* e:1
* t:1
* 其他:0

### `"tea"`

* a:1
* e:1
* t:1
* 其他:0

### `"ate"`

* a:1
* e:1
* t:1
* 其他:0

所以这三个 key 一样，分到同一组�?

### `"tan"` �?`"nat"`

* a:1
* n:1
* t:1
* 其他:0

分到另一组�?

### `"bat"`

* a:1
* b:1
* t:1
* 其他:0

单独一组�?

---

# 19. 易错点总结

## 易错�?1：误以为只比较字符集合就够了

不够，必须比较字�?*频次**�?

例如�?

* `"ab"` �?`"aab"` 字符种类都包�?a、b
* 但它们不是异位词

---

## 易错�?2：排序时直接修改原字符串

如果直接�?`strs[i]` 排序，会破坏原输入�?
一般应先复制副本再排序�?

---

## 易错�?3：哈希冲突没处理

哈希表不能只看哈希值，冲突后还必须比较真正�?key�?

---

## 易错�?4：组内数组忘记扩�?

一个分组里可能有很多字符串，因此必须支持动态扩容�?

---

## 易错�?5：返回格式写�?

C 语言版本最麻烦的地方之一就是�?

* 返回值：`char***`
* `returnSize`
* `returnColumnSizes`

三者都要按力扣要求正确构造�?

---

# 20. 面试回答模板

如果面试官问你怎么做，可以这样回答�?

> 这题关键是为每个字符串构造一个能唯一表示异位词特征的 key�?
> 最直接的方法是把每个字符串排序，排序结果相同的放到同一组，这样总复杂度�?`O(n * k log k)`�?
> 由于题目限定只包�?26 个小写字母，还可以进一步优化：统计每个字符串的 26 个字母频次，把这个频次数组作�?key�?
> 这样每个字符串只需要遍历一次即可构�?key，哈希查找和插入平均�?`O(1)`，所以总时间复杂度平均�?`O(n * k)`，空间复杂度�?`O(n)`�?

---

# 21. 一句话总结

这道题的核心就是�?

> **为每个字符串构造一个“异位词特征 key”，然后用哈希表完成分组�?*

其中�?

* **排序�?* 更直�?
* **频次统计�?* 更高�?

---

# 22. 最终结�?

## 排序�?

* 好理�?
* 好实�?
* 时间复杂度：`O(n * k log k)`

## 频次统计�?

* 更贴近异位词本质
* 平均更快
* 时间复杂度：`O(n * k)`

对于这道题：

> **如果只是做题，排序法足够常见；如果追求更优实现，频次统计法更值得掌握�?*

```

如果你愿意，我还可以继续给你补一�?**“力�?C 语言返回格式专项笔记�?*，专门讲 `char***`、`returnSize`、`returnColumnSizes` 这三个到底该怎么理解�?
```
