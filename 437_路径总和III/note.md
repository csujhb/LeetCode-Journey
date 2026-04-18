# LeetCode 437: 路径总和 III - 学习笔记

## 🎯 题目核心难点与特征
1. **起点不固定：** 路径不需要从根节点开始。
2. **终点不固定：** 路径不需要在叶子节点结束。
3. **方向唯一：** 只能“从上往下”走（父节点到子节点）。
4. **存在负数：** 节点值有正有负，所以遇到累加和等于目标值时**不能立刻停止搜索**（后面可能跟着一正一负抵消掉，形成新的合法路径）。
5. **易溢出：** 极端测试用例中累加和会超出 `int` 范围，必须使用 `long long` 规避防溢出。

---

## 解法一：双重递归（暴力法 / 直觉法）

这是最直观的解法，虽然时间复杂度稍高，但在面试中是最容易且最稳妥写出来的思路。

### 🔑 核心逻辑
既然起点不固定，那就**强行枚举所有起点**。
1. **外层 DFS (`pathSum`)：** 相当于二叉树的遍历（前序遍历），把树上的**每一个节点**都当做一次起点。
2. **内层 DFS (`countPaths`)：** 固定起点后，顺着这个起点一直往下找。每次往下走，就把 `targetSum` 减去当前节点的值，如果减到 0，说明找到了一条合法路径。

### 💻 C 语言核心代码模板
```c
// 辅助函数：计算“必须以当前 node 为起点”的合法路径数
int countPaths(struct TreeNode* node, long long target) {
    if (node == NULL) return 0;
    
    int count = 0;
    if (node->val == target) count++; // 找到了，但不能 return，继续往下找
    
    // 向左右子树继续延伸，目标值减去当前节点值
    count += countPaths(node->left, target - node->val);
    count += countPaths(node->right, target - node->val);
    
    return count;
}

// 主函数：枚举每一个节点作为起点
int pathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) return 0;
    
    // 1. 根节点自己当起点
    int pathsFromRoot = countPaths(root, (long long)targetSum);
    // 2. 左子树里的节点当起点
    int pathsFromLeft = pathSum(root->left, targetSum);
    // 3. 右子树里的节点当起点
    int pathsFromRight = pathSum(root->right, targetSum);
    
    return pathsFromRoot + pathsFromLeft + pathsFromRight;
}
```

**复杂度分析：**
* **时间复杂度：** $O(N^2)$（最坏情况树退化成链表），平衡树情况下为 $O(N \log N)$。
* **空间复杂度：** $O(H)$，H 为树的高度，即递归栈的深度。

---

## 解法二：前缀和 + 哈希表 + 回溯（最优解法）



这种解法将树上的路径问题降维成了经典的“一维数组两数之差”问题（类似于 LeetCode 560）。

### 🔑 核心逻辑
1. **什么是树上前缀和？** 从“根节点”到“当前节点”这条路径上所有节点值的总和。
2. **核心等式：** `当前前缀和 - 某个祖先的前缀和 = targetSum`。
   转换一下：`某个祖先的前缀和 = 当前前缀和 - targetSum`。
   这就意味着：只要我们在往下走的过程中，发现哈希表里记录过 `当前前缀和 - targetSum` 这个值，就说明从那个祖先到当前节点，刚好拼出了一条和为 `targetSum` 的路径。
3. **回溯的必要性：** 树是会分叉的！左子树走出的前缀和，不能拿给右子树用（它们不属于同一条垂直路径）。所以在退回父节点时，必须把当前节点产生的前缀和从哈希表里“撤销”（频次减 1）。

### 💻 核心代码思维框架 (伪代码/极简版)
```c
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
}

int pathSum(TreeNode* root, int targetSum) {
    HashMap* map = createHashMap();
    // 【易错点】必须初始化放入 (0, 1)！
    // 含义：为了处理“从根节点到当前节点刚好等于 targetSum”的情况
    putIntoHash(map, 0, 1); 
    
    return dfs(root, map, 0, targetSum);
}
```

**复杂度分析：**
* **时间复杂度：** $O(N)$，每个节点只遍历一次，哈希表存取为 $O(1)$。
* **空间复杂度：** $O(N)$，哈希表最多存储 N 个前缀和，递归栈深度也是 $O(N)$。

---

## 📝 综合总结

| 解法 | 优点 | 缺点 | 适用场景 |
| :--- | :--- | :--- | :--- |
| **双重递归** | 思维简单，代码极短，不需要额外数据结构 | 有重复计算，最差时间复杂度达 $O(N^2)$ | 笔试/面试求稳，或是 C 语言等没有内置哈希表的语言时首选 |
| **前缀和+回溯** | 时间复杂度严格 $O(N)$，极其高效 | 需维护哈希表，必须理解回溯，容易在初始状态 `(0,1)` 上踩坑 | 追求性能极致，使用 C++/Java/Python 等自带哈希表的语言时 |

**一句话口诀：**
遇到树上路径问题，**想暴力就双重 DFS（换起点+深搜），想优雅就前缀和加回溯（做减法查哈希）。**