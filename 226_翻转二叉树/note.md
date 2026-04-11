# LeetCode 226 翻转二叉树 —— 学习笔记

## 题目回顾
翻转一棵二叉树，即镜像反转：每个节点的左右子树交换位置。

**示例**  
输入：
```
     4
   /   \
  2     7
 / \   / \
1   3 6   9
```
输出：
```
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

---

## 方法一：递归 DFS（深度优先搜索）—— 最简洁最优解

### 思路
1. 递归翻转左子树，得到新的左子树（原右子树的镜像）。
2. 递归翻转右子树，得到新的右子树（原左子树的镜像）。
3. 将当前节点的左右指针互换。

**递推公式**：
```
invert(root) = 交换( invert(root.left), invert(root.right) )
```

### 代码
```c
struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL) return NULL;
    struct TreeNode* left = invertTree(root->left);
    struct TreeNode* right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}
```

### 复杂度分析
- **时间复杂度**：O(n)，每个节点访问一次。
- **空间复杂度**：最坏 O(n)（链表），平均 O(log n)（递归栈深度）。

### 优点与缺点
- ✅ 代码极其简洁，符合直觉，面试首选。
- ❌ 递归过深可能栈溢出（实际测试极少发生）。

---

## 方法二：迭代 DFS（显式栈模拟递归）

### 思路
- 使用栈模拟递归过程。
- 每次从栈中弹出一个节点，交换其左右子节点，然后将非空子节点压入栈。

### 代码
```c
struct StackNode {
    struct TreeNode** data;
    int top;
};

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL) return NULL;

    // 假设最大节点数10000，实际可用动态数组
    struct TreeNode* stack[10000];
    int top = 0;
    stack[top++] = root;

    while (top > 0) {
        struct TreeNode* node = stack[--top];
        // 交换左右子节点
        struct TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;

        // 将非空子节点入栈（顺序任意）
        if (node->left)  stack[top++] = node->left;
        if (node->right) stack[top++] = node->right;
    }
    return root;
}
```

### 复杂度分析
- **时间复杂度**：O(n)
- **空间复杂度**：最坏 O(n)

### 优点与缺点
- ✅ 避免递归栈溢出。
- ❌ 代码略长，需手动维护栈。

---

## 方法三：层序遍历 BFS（广度优先搜索）

### 思路
- 利用队列进行层序遍历。
- 每访问一个节点，就交换其左右子节点，然后将非空子节点入队。

### 代码
```c
#define MAX_SIZE 10000

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL) return NULL;

    struct TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* node = queue[front++];
        // 交换左右子节点
        struct TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;

        if (node->left)  queue[rear++] = node->left;
        if (node->right) queue[rear++] = node->right;
    }
    return root;
}
```

### 复杂度分析
- **时间复杂度**：O(n)
- **空间复杂度**：O(n)（队列中最多存储一层节点）

### 优点与缺点
- ✅ 按层处理，逻辑直观。
- ❌ 队列可能占用更多内存（尤其宽树）。

---

## 三种方法对比总结

| 方法               | 时间复杂度 | 空间复杂度         | 适用场景               | 特点                       |
| ------------------ | ---------- | ------------------ | ---------------------- | -------------------------- |
| **递归 DFS**       | O(n)       | 最坏 O(n)，平均 O(log n) | 常规二叉树，代码简洁优先 | 最简洁，面试必写           |
| **迭代 DFS（栈）** | O(n)       | 最坏 O(n)          | 树极深，担心递归溢出   | 手动控栈，无递归风险       |
| **层序 BFS（队列）** | O(n)       | 最坏 O(n)          | 树极宽，或需要按层遍历 | 层序处理，便于扩展其他逻辑 |

---

## 重点记忆点

1. **递归核心操作**：交换当前节点的左右子节点，并递归处理左右子树。
2. 三种解法均遍历所有节点，时间复杂度 **O(n)** 无法优化。
3. 面试时直接写出递归版本，若被追问递归风险，可补充栈或队列实现。