# 102. 二叉树的层序遍历 —— C语言多解法学习笔记

## 问题概述

给定一个二叉树，要求返回其**层序遍历**的结果：即逐层地、从上到下、从左到右访问所有节点，并将每一层的节点值作为一个独立的数组返回。注意，层序遍历与单纯的 BFS 有所不同——BFS 的结果是一个一维序列，而本题要求**区分每一层**，返回二维结构。

**C 语言特有问题**：由于 C 语言函数只能返回一个值，题目要求通过三个参数来传递结果：
- `returnSize`：输出参数，存放二叉树的层数；
- `returnColumnSizes`：输出参数，存放一个数组，其中每个元素表示对应层的节点个数；
- 返回值 `int**`：指向一个指针数组，该数组中的每个指针指向一个存放该层节点值的数组。

---

## 解法一：BFS（广度优先搜索 / 队列）

### 核心思想

BFS 是层序遍历最直观的思路，核心是 **“队列控层 + 按层处理”** 。基本步骤如下：

1. 将根节点入队；
2. 当队列非空时，记录当前队列的大小 `levelSize`，这就是当前层的节点数；
3. 依次弹出 `levelSize` 个节点，收集它们的值；同时将每个节点的左右子节点（如果存在）入队；
4. 将收集到的当前层节点值存入结果数组，重复步骤 2~3 直至队列为空。

**关键点**：`levelSize = queue.size()` 是层序遍历的“灵魂”，通过固定当前层节点数，避免不同层的节点混在一起遍历。

### C 语言实现

```c
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 用数组模拟队列（题目节点数 ≤ 2000）
    struct TreeNode* queue[2000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    // 结果数组的动态分配
    int capacity = 100;
    int** result = (int**)malloc(sizeof(int*) * capacity);
    *returnColumnSizes = (int*)malloc(sizeof(int) * capacity);

    while (front < rear) {
        int levelSize = rear - front;          // 当前层的节点数
        int* levelVals = (int*)malloc(sizeof(int) * levelSize);
        
        // 遍历当前层所有节点
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            levelVals[i] = node->val;
            
            // 左右子节点入队（先左后右，保证层内顺序）
            if (node->left)  queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }

        // 存储当前层结果
        (*returnColumnSizes)[*returnSize] = levelSize;
        result[*returnSize] = levelVals;
        (*returnSize)++;

        // 动态扩容
        if (*returnSize >= capacity) {
            capacity *= 2;
            result = (int**)realloc(result, sizeof(int*) * capacity);
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * capacity);
        }
    }

    return result;
}
```

###  BFS 变种思路

除了在循环开头获取队列大小外，还可以用**双计数法**：用两个变量分别记录当前层剩余节点数 `curLayerCount` 和下一层节点数 `nextLayerCount`，每次弹出一个节点，`curLayerCount--`，子节点入队时 `nextLayerCount++`；当 `curLayerCount == 0` 时，表示一层结束，交换两个计数器的值。

---

## 解法二：DFS（深度优先搜索 / 递归）

###  核心思想

DFS 并非天然按层遍历，但可以通过**在递归时传递当前深度 `depth`** 来实现按层存储。

基本逻辑：
1. 每次递归调用携带一个 `depth` 参数，表示当前节点所在的层数（从 0 开始计数）；
2. 检查结果数组的大小是否 `<= depth`：若是，说明这一层还没有被创建，需要新建一个数组来存放该层的节点值；否则，直接追加到对应层的数组中；
3. 按**先左后右**的顺序递归遍历子树（保证每层内从左到右的顺序），递归时 `depth + 1`。

###  C 语言实现

```c
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void dfs(struct TreeNode* node, int depth, int** result, int* returnSize, int* colSizes, int* colCapacity) {
    if (node == NULL) return;

    // 如果当前深度对应的层还没有被创建
    if (*returnSize <= depth) {
        // 为新的一层分配数组（这里假设每层节点数不超过当前总节点数，实际可以动态调整）
        result[depth] = (int*)malloc(sizeof(int) * 1000); // 简化处理，实际应更精确
        colSizes[depth] = 0;
        (*returnSize)++;
    }

    // 将当前节点值存入对应层
    result[depth][colSizes[depth]++] = node->val;

    // 先左后右递归，保证同一层内的顺序
    dfs(node->left, depth + 1, result, returnSize, colSizes, colCapacity);
    dfs(node->right, depth + 1, result, returnSize, colSizes, colCapacity);
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 假设最大层数为 1000（根据题目约束可调整）
    int maxDepth = 1000;
    int** result = (int**)malloc(sizeof(int*) * maxDepth);
    int* colSizes = (int*)calloc(maxDepth, sizeof(int));

    dfs(root, 0, result, returnSize, colSizes, NULL);

    // 为每一层重新分配精确大小的数组（可选优化）
    for (int i = 0; i < *returnSize; i++) {
        int* exactArr = (int*)malloc(sizeof(int) * colSizes[i]);
        for (int j = 0; j < colSizes[i]; j++) {
            exactArr[j] = result[i][j];
        }
        free(result[i]);
        result[i] = exactArr;
    }

    *returnColumnSizes = colSizes;
    return result;
}
```

> **⚠️ 注意**：DFS 解法在 C 语言中处理内存时需要特别小心。上面代码是一个**简化版本**，实际应用时建议先用一次 DFS 计算出树的最大深度和每层节点数，再精确分配内存，避免浪费或溢出。

---

## 解法对比分析

| 维度 | BFS（队列） | DFS（递归） |
|------|------------|------------|
| **核心数据结构** | 队列（Queue） | 递归调用栈 + depth 参数 |
| **遍历顺序** | 天然按层逐层推进 | 深度优先，通过 depth 参数归位 |
| **时间复杂度** | O(n)，每个节点入队出队各一次 | O(n)，每个节点访问一次 |
| **空间复杂度** | O(n)，队列在最宽层可能容纳 O(n) 个节点 | O(h)，递归调用栈深度为树高 h，最坏 O(n) |
| **优点** | 逻辑直观，符合层序遍历的语义 | 无需维护队列，代码更简洁 |
| **缺点** | 需要额外的队列空间 | 依赖递归栈，树极深时可能栈溢出 |
| **适用场景** | 面试首选，工程推荐 | 树结构较浅或需要利用深度信息时 |

**BFS 是更经典和推荐的解法**，因为其逻辑最符合“层序遍历”的直观理解。DFS 则更多作为一种扩展思路，帮助理解如何用深度信息来模拟按层收集的过程。

---

## 相关题目扩展

掌握了本题的 BFS 模板后，可以轻松应对以下变种题目：

| 题目 | 与 102 的关系 |
|------|--------------|
| **LeetCode 103. 二叉树的锯齿形层序遍历** | 在 102 的基础上，根据层数的奇偶性决定是否反转当前层的节点列表 |
| **LeetCode 107. 二叉树的层序遍历 II** | 与 102 完全相同，只需最后将结果数组反转（自底向上） |
| **LeetCode 199. 二叉树的右视图** | BFS 层序遍历，每层只取最后一个节点即可 |
| **LeetCode 429. N 叉树的层序遍历** | 队列中处理的节点从“左右子节点”变为“子节点列表” |

---

## 学习要点总结

1. **理解“按层”与普通 BFS 的区别**：普通 BFS 输出一维序列，本题需要借助 `levelSize` 将不同层隔开。
2. **掌握 BFS 模板**：`queue → while(!empty) → 记录size → for循环处理size个节点 → 子节点入队`，这是解决层序遍历相关问题的万能模板。
3. **理解 DFS 的“深度”参数思想**：通过递归传递深度信息，可以将深度优先的访问结果“映射”到对应的层中。
4. **C 语言的内存管理**：注意 `malloc` 分配的大小，记得为每一层单独分配数组，并在调用方正确释放。