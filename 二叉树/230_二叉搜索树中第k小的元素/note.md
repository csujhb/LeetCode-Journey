# 📝 学习笔记：230. 二叉搜索树中第 K 小的元素

##  核心原理
**二叉搜索树（BST）的特性：**

* **中序遍历（左 -> 根 -> 右）** 得到的结果是一个**严格递增**的有序序列。
* **破题关键：** 寻找第 $k$ 小的元素，本质上就是找中序遍历序列中的第 $k$ 个节点。

---

##  解法实现

###  递归法（带提前剪枝优化）

利用系统调用栈。为了提高效率，必须在找到目标后立即停止所有递归分支。

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * struct TreeNode *left;
 * struct TreeNode *right;
 * };
 */

void inorder(struct TreeNode* node, int k, int* count, int* res) {
    // 1. 递归终止条件：节点为空，或者已经找到了结果（*count >= k）
    if (node == NULL || *count >= k) return;

    // 2. 遍历左子树
    inorder(node->left, k, count, res);

    // 3. 核心优化：从左子树回来后，再次检查是否已找到目标，防止多余的操作
    if (*count >= k) return;

    // 4. 处理当前节点
    (*count)++;
    if (*count == k) {
        *res = node->val;
        return;
    }

    // 5. 遍历右子树
    inorder(node->right, k, count, res);
}

int kthSmallest(struct TreeNode* root, int k) {
    int count = 0;
    int res = -1;
    inorder(root, k, &count, &res);
    return res;
}
```

### 迭代法（显式栈实现） 🌟 推荐
手动模拟中序遍历的过程。这种方法在找到第 $k$ 个元素时能直接返回，控制流最清晰。

```c
#include <stdlib.h>

int kthSmallest(struct TreeNode* root, int k) {
    // 根据 LeetCode 题目范围，节点数不超过 10^4
    struct TreeNode* stack[10005]; 
    int top = -1;
    struct TreeNode* curr = root;

    while (curr != NULL || top != -1) {
        // 1. 一路向左：把左边界所有节点入栈
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }

        // 2. 弹出并处理：弹出栈顶（当前最小值）
        curr = stack[top--];
        k--; // 找到一个，计数减1
        
        if (k == 0) {
            return curr->val; // 找到第 k 小，立即退出
        }

        // 3. 转向右子树：准备处理右侧分支
        curr = curr->right;
    }
    return -1;
}
```

---

##  复杂度分析
| 维度 | 复杂度 | 说明 |
| :--- | :--- | :--- |
| **时间复杂度** | $O(H + k)$ | $H$ 为树的高度。需要先下行至最左叶子（$H$），再遍历 $k$ 个元素。 |
| **空间复杂度** | $O(H)$ | 无论是递归栈还是显式栈，深度都取决于树的高度 $H$。 |

---

##  进阶思考：如果频繁查询怎么办？
**面试官追问：** 如果树结构经常变动（插入/删除），且需要频繁查找第 $k$ 小，如何优化到 $O(H)$？

* **优化方案：** 修改节点结构，增加一个字段 `size`，记录**以该节点为根的子树节点总数**。
* **查找逻辑：**
    1.  令 `left_size = node->left->size`。
    2.  如果 `k == left_size + 1`，则当前节点就是目标。
    3.  如果 `k <= left_size`，去左子树找第 $k$ 小。
    4.  如果 `k > left_size + 1`，去右子树找第 $k - (left_size + 1)$ 小。
* **效果：** 这样可以将单次查询的时间复杂度降低到 $O(H)$，即只与树的高度有关，不再遍历多余的节点。

---

##  总结
1.  **BST + 顺序 = 中序遍历**。
2.  **递归**要注意“剪枝”，否则会浪费时间遍历整棵树。
3.  **迭代**在 C 语言中更可控，是处理树遍历问题的通用且高效的方案。