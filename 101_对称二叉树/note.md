# LeetCode 101 对称二叉树 —— 学习笔记

## 题目回顾
给定一个二叉树，检查它是否是镜像对称的。  
例如，二叉树 `[1,2,2,3,4,4,3]` 是对称的，而 `[1,2,2,null,3,null,3]` 不是。

## 核心思想
**两棵树对称的条件**：

- 它们的根节点值相等；
- 每棵树的左子树与另一棵树的右子树镜像对称。

---

## 方法一：递归 DFS（最优解）

### 思路
定义一个辅助函数 `bool isMirror(TreeNode* left, TreeNode* right)`，判断两棵树是否镜像对称：
1. 若两个节点都为空 → 对称。
2. 若一个为空另一个非空 → 不对称。
3. 若值不相等 → 不对称。
4. 递归比较 `left->left` 与 `right->right` 以及 `left->right` 与 `right->left`。

### 代码
```c
bool isMirror(struct TreeNode* left, struct TreeNode* right) {
    if (left == NULL && right == NULL) return true;
    if (left == NULL || right == NULL) return false;
    return (left->val == right->val) &&
           isMirror(left->left, right->right) &&
           isMirror(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;
    return isMirror(root->left, root->right);
}
```

### 复杂度
- **时间**：O(n)，每个节点访问一次。
- **空间**：O(h)，递归栈深度（最坏 O(n)）。

---

## 方法二：迭代 DFS（显式栈）

### 思路
用栈模拟递归，每次压入一对需要比较的节点 `(left, right)`，循环弹出并判断。

### 代码
```c
#define MAX_SIZE 2000

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;

    struct TreeNode* stack[MAX_SIZE][2]; // 存一对节点
    int top = 0;
    stack[top][0] = root->left;
    stack[top][1] = root->right;
    top++;

    while (top > 0) {
        top--;
        struct TreeNode* left  = stack[top][0];
        struct TreeNode* right = stack[top][1];

        if (left == NULL && right == NULL) continue;
        if (left == NULL || right == NULL) return false;
        if (left->val != right->val) return false;

        // 注意入栈顺序：比较 (左的左, 右的右) 和 (左的右, 右的左)
        stack[top][0] = left->left;
        stack[top][1] = right->right;
        top++;
        stack[top][0] = left->right;
        stack[top][1] = right->left;
        top++;
    }
    return true;
}
```

---

## 方法三：层序遍历 BFS（按层检查回文）—— 你的思路正确实现

### 思路
1. 使用队列按层遍历，**将空节点也入队**（用特殊标记或直接存 `NULL` 指针）。
2. 每次处理一层：记录当前层的节点数量 `levelSize`，收集这一层所有节点的值（或指针）到数组中。
3. 用双指针检查该层数组是否对称（首尾比较）。
4. 同时将下一层的节点（包括空节点的“左右孩子”）继续入队。

### 代码（C语言，直接存 `NULL`）
```c
#define MAX_SIZE 10000

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;

    struct TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;          // 当前层的节点数
        // 用数组暂存当前层的节点指针（包含 NULL）
        struct TreeNode* level[MAX_SIZE];
        for (int i = 0; i < levelSize; i++) {
            level[i] = queue[front++];
        }

        // 检查当前层是否对称
        int left = 0, right = levelSize - 1;
        while (left < right) {
            struct TreeNode* a = level[left];
            struct TreeNode* b = level[right];
            if (a == NULL && b == NULL) {
                left++; right--;
                continue;
            }
            if (a == NULL || b == NULL) return false;
            if (a->val != b->val) return false;
            left++; right--;
        }

        // 将下一层的节点入队（包括空节点）
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = level[i];
            if (node != NULL) {
                queue[rear++] = node->left;   // 可能是 NULL
                queue[rear++] = node->right;
            }
            // 注意：如果 node 是 NULL，不需要入队它的“孩子”
            // 因为 NULL 没有孩子，保持队列中不出现无意义的空节点扩展
        }
    }
    return true;
}
```

### 更简洁的 BFS（直接按对比较，无需分层数组）
其实可以更简单：每次从队列中取出**两个**节点（左子树的节点和右子树的对应节点），直接比较。
```c
bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;

    struct TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = root->left;
    queue[rear++] = root->right;

    while (front < rear) {
        struct TreeNode* left  = queue[front++];
        struct TreeNode* right = queue[front++];

        if (left == NULL && right == NULL) continue;
        if (left == NULL || right == NULL) return false;
        if (left->val != right->val) return false;

        // 按镜像对应关系入队
        queue[rear++] = left->left;
        queue[rear++] = right->right;
        queue[rear++] = left->right;
        queue[rear++] = right->left;
    }
    return true;
}
```
这个版本避免了按层数组，更加简洁高效。

---

## 三种方法对比

| 方法                     | 时间复杂度 | 空间复杂度     | 特点                           |
| ------------------------ | ---------- | -------------- | ------------------------------ |
| **递归 DFS**             | O(n)       | O(h)           | 代码最短，逻辑清晰，面试首选   |
| **迭代 DFS（栈）**       | O(n)       | O(n)           | 手动模拟递归，避免栈溢出       |
| **迭代 BFS（队列成对）** | O(n)       | O(n)           | 无递归，按层比较，易理解       |

---

## 重点记忆

1. **递归关系**：判断 `left` 和 `right` 镜像对称，需要满足：
   - `left->val == right->val`
   - `left->left` 与 `right->right` 对称
   - `left->right` 与 `right->left` 对称
2. 处理空节点是本题的关键，必须显式判断 `NULL`。
3. 你的队列思路完全可行，修正后就能 AC，但推荐优先掌握递归写法。