# 📝 学习笔记：199. 二叉树的右视图

##  核心破题思路

题目要求“从右侧能看到的节点”，将其翻译成算法语言，本质上就是：**收集这棵树每一层最右边的那个节点。**

针对“逐层”和“最右”，我们天然有两种维度的解题策略：
1.  **广度优先（BFS / 层序遍历）**：一层一层扫，拿走每一层的**最后一个**。
2.  **深度优先（DFS / 递归遍历）**：一路向深处走，但**优先走右边**，拿走每一层**第一个碰到的**。

---

##  核心解法对比与代码实现

### BFS 广度优先（层序遍历） —— 思路最直观

利用队列（Queue）进行标准的层序遍历。

* **核心逻辑**：每次处理一整层。利用 `len = rear - front` 获取当前层的节点数，用 `for` 循环把当前层的节点全部出队，并把它们的子节点入队。当前层出队的**最后一个节点**，就是我们要找的右视图节点。
* **⚠️ 踩坑警告（C语言特有）**：
    * **队列越界**：在手写队列时，`queue` 数组的大小绝对不能只开到刚好等于最大节点数（比如 100），因为 `rear` 指针一直在递增，不复用前面的空间。保险起见应稍微开大一点（如 105）。
    * **内存分配**：不要忘记给返回的数组分配空间 `malloc`。

```c
#include <stdlib.h>

int* rightSideViewBFS(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (root == NULL) return NULL;
    
    int* res = (int*)malloc(105 * sizeof(int));
    struct TreeNode* queue[105]; // 队列大小要安全
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        int len = rear - front; 
        for (int i = 0; i < len; i++) {
            struct TreeNode* node = queue[front++]; // 取出当前节点
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        // for循环结束时，刚好处理完一层，此时 front-1 就是这一层最后入队的节点
        res[(*returnSize)++] = queue[front - 1]->val;
    }
    return res;
}
```

###  DFS 深度优先（递归） —— 代码最优雅 🌟 强烈推荐

利用隐式的系统调用栈，按照 **根 -> 右 -> 左** 的顺序遍历。

* **核心逻辑（The "Aha!" Moment）**：
    * 正常的中序/前序遍历是先左后右。但如果我们**先递归右子树，再递归左子树**，那么对于任何深度（每一层），我们**最先访问到的节点一定是最右侧的节点**。
    * 如何判断是不是第一次来到这个深度？**对比 `depth` 和 `*returnSize`**。如果 `depth == *returnSize`，说明当前层还没有被记录过，立刻将其加入结果集。

```c
#include <stdlib.h>

void dfs(struct TreeNode* node, int depth, int* res, int* returnSize) {
    if (node == NULL) return;
    
    // 如果当前深度刚好等于数组目前的长度，说明这个深度是第一次抵达
    // 因为我们是“先右后左”遍历，这必然是该层最右侧的节点
    if (depth == *returnSize) {
        res[(*returnSize)++] = node->val;
    }
    
    // 关键：务必先遍历右子树！
    dfs(node->right, depth + 1, res, returnSize);
    dfs(node->left, depth + 1, res, returnSize);
}

int* rightSideViewDFS(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (root == NULL) return NULL;
    
    int* res = (int*)malloc(105 * sizeof(int));
    dfs(root, 0, res, returnSize); // 根节点深度定为 0
    return res;
}
```

---

##  复杂度对比分析

| 特性 | BFS (层序队列) | DFS (递归遍历) | 说明 |
| :--- | :--- | :--- | :--- |
| **时间复杂度** | $O(N)$ | $O(N)$ | $N$ 为节点数。两种方法都必须遍历整棵树的每一个节点才能得出结果。 |
| **空间复杂度** | $O(N)$ | $O(H)$ | BFS 需要开辟队列存放节点，最坏情况需存放最后一层所有节点。DFS 空间开销取决于递归调用栈的深度 $H$（树高），通常情况下 DFS 空间更优。 |

---

##  💡 总结与反思

1.  **C 语言写树题的痛点**：由于没有现成的 `Queue` 容器，BFS 手写队列非常繁琐且容易踩到数组越界的坑。
2.  **思维转换的红利**：遇到“某一层最侧边”的问题，不要死磕层序遍历。利用 DFS 调整遍历顺序（先右后左），再配合 `depth` 状态判断，往往能写出“降维打击”级别的精简代码。这个技巧同样适用于“二叉树的左视图”（只需改成“先左后右”即可）。