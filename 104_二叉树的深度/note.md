# LeetCode 104 二叉树的最大深度 —— 学习笔记

## 题目回顾

给定一个二叉树，找出其最大深度。二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

**示例**  
给定二叉树 `[3,9,20,null,null,15,7]`：

```
    3
   / \
  9  20
    /  \
   15   7
```

返回最大深度：3。

---

## 方法一：递归 DFS（深度优先搜索）

### 思路

- 当前树的最大深度 = 左子树最大深度 与 右子树最大深度 中的较大值 **+ 1**（根节点本身）
- 递归终止条件：遇到空节点返回 0

### 代码

```c
int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}
```

精简版（使用 `fmax`）：

```c
#include <math.h>

int maxDepth(struct TreeNode* root) {
    return root ? fmax(maxDepth(root->left), maxDepth(root->right)) + 1 : 0;
}
```

### 复杂度分析

- **时间复杂度**：O(n)，每个节点访问一次。
- **空间复杂度**：最坏 O(n)（树退化为链表），最好 O(log n)（平衡二叉树），递归栈深度。

### 优点与缺点

- ✅ 代码极简，符合直觉，面试首选。
- ❌ 极端深树可能引发递归栈溢出（但在常规 OJ 测试用例中极少发生）。

---

## 方法二：迭代 DFS（显式栈模拟递归）

### 思路

- 用栈模拟递归过程，栈中同时存储**节点指针**和**当前节点深度**。
- 每次从栈顶取出元素，更新最大深度，并将左右子节点（及其深度+1）压入栈中。

### 代码

```c
// 栈元素结构体
struct StackNode {
    struct TreeNode* node;
    int depth;
};

int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;

    // 简单数组模拟栈（假设节点数不超过10000，实际可用动态分配）
    struct StackNode stack[10000];
    int top = 0;
    int maxDepth = 0;

    stack[top++] = (struct StackNode){root, 1};

    while (top > 0) {
        struct StackNode curr = stack[--top];
        struct TreeNode* node = curr.node;
        int depth = curr.depth;

        // 更新最大深度
        if (depth > maxDepth) maxDepth = depth;

        // 先压右，再压左（保证左子树先处理，不过顺序不影响最终结果）
        if (node->right) stack[top++] = (struct StackNode){node->right, depth + 1};
        if (node->left)  stack[top++] = (struct StackNode){node->left, depth + 1};
    }

    return maxDepth;
}
```

### 复杂度分析

- **时间复杂度**：O(n)，每个节点入栈出栈一次。
- **空间复杂度**：最坏 O(n)（栈中最多存储所有节点），实际与树高有关。

### 优点与缺点

- ✅ 避免递归栈溢出风险，适合深度极大的树。
- ❌ 代码稍长，需要手动维护栈结构。

---

## 方法三：层序遍历 BFS（广度优先搜索）

### 思路

- 利用队列进行**层序遍历**，每遍历完一层，深度计数器 +1。
- 队列中只存储节点指针，通过记录当前层节点数量来控制层结束。

### 代码

```c
// 使用数组模拟循环队列
#define MAX_SIZE 10000

int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0;
    int depth = 0;

    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;   // 当前层的节点数
        // 将当前层所有节点出队，并将其子节点入队
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            if (node->left)  queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        depth++;  // 完成一层，深度+1
    }

    return depth;
}
```

### 复杂度分析

- **时间复杂度**：O(n)，每个节点入队出队一次。
- **空间复杂度**：最坏 O(n)（队列中同时存储某一层的全部节点，对于满二叉树最后一层有 n/2 个节点）。

### 优点与缺点

- ✅ 逻辑直观，按层计数，不易出错。
- ✅ 适合处理**非常宽**的树，避免递归栈过深。
- ❌ 在宽树情况下队列占用内存较大。

---

## 三种方法对比总结

| 方法               | 时间复杂度 | 空间复杂度         | 适用场景                         | 特点                     |
| ------------------ | ---------- | ------------------ | -------------------------------- | ------------------------ |
| **递归 DFS**       | O(n)       | 最坏 O(n)，平均 O(log n) | 常规二叉树，代码简洁优先         | 最简洁，面试首选         |
| **迭代 DFS（栈）** | O(n)       | 最坏 O(n)          | 树极深，担心递归溢出             | 手动控栈，避免递归风险   |
| **层序 BFS（队列）** | O(n)       | 最坏 O(n)          | 树极宽，或需要按层处理其他逻辑   | 按层遍历，易于扩展其他功能 |

---

## 重点记忆点

1. **递归公式**：`maxDepth = 1 + max(maxDepth(left), maxDepth(right))`
2. 三种解法均遍历所有节点，时间复杂度**无法突破 O(n)**。
3. 面试时优先写递归版本，若被追问递归风险，再补充迭代方案。