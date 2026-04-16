# LeetCode 105: 从前序与中序遍历序列构造二叉树 - 学习笔记

## 💡 核心基础：两种遍历的物理意义

解这道题，最根本的前提是理解两个数组到底给我们提供了什么信息：
* **前序遍历 (Preorder):** `[根节点, 左子树, 右子树]` 
    * **作用：** 提供**“生成清单”**。数组的第一个元素永远是当前子树的根节点。
* **中序遍历 (Inorder):** `[左子树, 根节点, 右子树]`
    * **作用：** 提供**“边界基准”**。找到根节点在中序数组中的位置后，它的左边全是左子树节点，右边全是右子树节点。

---

## 解法一：哈希表分治法（“上帝视角”常规解法）

这是最直观的解法。拿到完整的数组，找出根节点，把数组“切”成左右两半，分别交给左右子树去递归。

### 🔑 核心逻辑
1.  **建表：** 遍历一遍中序数组，将 `(节点值 -> 数组下标)` 存入哈希表，实现 O(1) 的查找速度。
2.  **分治：** 从前序数组拿第一个值作为 Root。查哈希表得到 Root 在中序数组的位置 `root_idx`。
3.  **切分：** 利用 `root_idx` 计算出左子树的节点个数 `left_size`。
4.  **递归：**
    * 左子树的前序区间：`[pre_start + 1, pre_start + left_size]`
    * 右子树的前序区间：`[pre_start + left_size + 1, pre_end]`

### ⚠️ C 语言实现避坑指南
* **哈希冲突与容量：** C 语言手写开放寻址哈希表时，容量必须大于数据量的 2 倍，且最好是质数（如 10007），否则极易因冲突导致超时或死循环。
* **负数取模：** 节点值可能为负数（$-3000 \sim 3000$）。C 语言中负数取模依然是负数，必须处理为正数下标：`((val % SIZE) + SIZE) % SIZE`。
* **内存管理：** `malloc/calloc` 的空间在用完后切记 `free`，养成良好工程习惯。

### 💻 核心代码模板
```c
#include <stdlib.h>

// 扩大哈希表容量，使用质数降低冲突概率
#define ARR_SIZE 10007 

typedef struct HashMap {
    int key;    
    int value;  
    int isused;
} HashMap;

// 安全的哈希函数，处理负数取模
unsigned int hashInt(int val){
    return (unsigned int)(((val % ARR_SIZE) + ARR_SIZE) % ARR_SIZE);
}

void hashInsert(HashMap* table, int *arr, int len){
    for(int i = 0; i < len; i++){
        unsigned int idx = hashInt(arr[i]);
        while(table[idx].isused){
            idx = (idx + 1) % ARR_SIZE;
        }
        table[idx].isused = 1;
        table[idx].key = arr[i];
        table[idx].value = i;
    }
}

int getIndex(HashMap* table, int key){
    unsigned int idx = hashInt(key);
    while(table[idx].isused){
        if(table[idx].key == key) return table[idx].value;
        idx = (idx + 1) % ARR_SIZE;
    }
    return -1;
}

struct TreeNode* createNode(int val){
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    return node;
}

// 核心递归：同时传递前序和中序的边界索引
struct TreeNode* buildTree_Helper(HashMap* table, int* preorder, int pre_start, int pre_end, int in_start, int in_end){
    if(pre_start > pre_end || in_start > in_end) return NULL;
    
    int root_value = preorder[pre_start];
    int root_idx = getIndex(table, root_value); 
    struct TreeNode* node = createNode(root_value);
    
    int left_size = root_idx - in_start;
    
    // 递归左子树
    node->left = buildTree_Helper(table, preorder, pre_start + 1, pre_start + left_size, in_start, root_idx - 1);
    // 递归右子树
    node->right = buildTree_Helper(table, preorder, pre_start + left_size + 1, pre_end, root_idx + 1, in_end);
    
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    HashMap* table = (HashMap*)calloc(ARR_SIZE, sizeof(HashMap));
    hashInsert(table, inorder, inorderSize);
    
    struct TreeNode* root = buildTree_Helper(table, preorder, 0, preorderSize - 1, 0, inorderSize - 1);
    
    free(table); // 释放哈希表内存
    return root;
}
```

**复杂度：**
* 时间复杂度：O(N)
* 空间复杂度：O(N)（哈希表占用空间）

---

## 解法二：停止标志位法（“第一人称视角”进阶解法）

不需要哈希表，不需要切分数组，空间消耗极小。这种方法假装自己是一个正在遍历树的指针，模拟了计算机底层的调用栈。

### 🔑 核心逻辑
不需要在中序数组里去“找”根节点，而是维护两个指针 `pre_idx` 和 `in_idx`，以及一个**停止标志 (stop)**。

1.  **无脑建树：** 只要前序数组还有值，就拿出来建节点。
2.  **一路向左：** 递归构建左子树时，把**当前节点的值**传给下一层，作为左子树的“停止标志”。
3.  **撞墙回头：** 每次建树前，先看一眼中序数组当前的数 `inorder[*p_in]`。如果它**等于**传进来的停止标志，说明左边彻底没节点了（撞墙了）。此时 `in_idx` 指针后移，返回 `NULL`。
4.  **向右探索：** 左边建完了，再去建右边。右子树的停止标志和父节点共用同一个。

### 💻 核心代码模板
```c
struct TreeNode* build(int* preorder, int preorderSize, int* p_pre, 
                       int* inorder, int* p_in, int stop) {
    // 1. 终止条件：前序数组用完
    if (*p_pre >= preorderSize) return NULL;
    
    // 2. 撞墙回头：中序当前值 == 停止标志
    if (inorder[*p_in] == stop) {
        (*p_in)++; // 越过当前根节点
        return NULL;
    }
    
    // 3. 构建当前节点
    int root_val = preorder[(*p_pre)++];
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = root_val;
    
    // 4. 递归左子树 (当前节点值作为停止标志)
    node->left = build(preorder, preorderSize, p_pre, inorder, p_in, root_val);
    // 5. 递归右子树 (继承父辈的停止标志)
    node->right = build(preorder, preorderSize, p_pre, inorder, p_in, stop);
    
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int pre_idx = 0; 
    int in_idx = 0;  
    
    // 初始调用：传入 3001（题目节点值范围之外的数）作为最外层停止标志
    return build(preorder, preorderSize, &pre_idx, inorder, &in_idx, 3001);
}
```

**复杂度：**
* 时间复杂度：O(N)（每个节点严格被访问和处理一次）
* 空间复杂度：O(1)（如果不算递归系统栈的消耗，没有额外开辟任何数据结构）

---

## 📝 个人总结

1.  在笔试/面试中，如果时间充裕且语言自带哈希表（如 C++ 的 `unordered_map`），**解法一**最不容易出错，思维最清晰。
2.  如果使用纯 C 语言，或者追求极致的性能和极简的代码，**解法二（停止标志位法）**是降维打击。它不仅避开了繁琐的哈希表底层编写，还深刻体现了对二叉树前中后序遍历本质的理解。掌握这种“标志位回溯”的思维，对解决其他复杂的树/图遍历问题非常有帮助。