# 📚 LeetCode 98: 验证二叉搜索树 (Validate BST) 学习笔记

**核心概念**：二叉搜索树（BST）的严格定义是，对于树中的任意一个节点：
* 其**左子树**中的**所有**节点的值，都必须严格小于该节点的值。
* 其**右子树**中的**所有**节点的值，都必须严格大于该节点的值。

---

## 💡 方法一：递归上下界法 (Range Constraints)

这是最直观、最符合 BST 树形结构定义的解法。我们不能仅仅比较父子节点，而是要为每一个节点设定一个合法的“取值范围”。

### 核心逻辑

* 根节点的取值范围是无限制的 `(-∞, +∞)`。
* 往**左**子树递归时，当前节点的值就变成了左子树所有节点的**最大上限 (max)**。
* 往**右**子树递归时，当前节点的值就变成了右子树所有节点的**最小下限 (min)**。
* **C语言技巧**：为了应对 LeetCode 中极端的整型边界测试用例（如 `INT_MAX` 和 `INT_MIN`），我们使用 `struct TreeNode*` 指针来传递边界，用 `NULL` 表示没有边界。

### C 语言代码实现
```c
#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 辅助函数：携带了允许的最小值节点指针 (minNode) 和最大值节点指针 (maxNode)
bool isValidBSTHelper(struct TreeNode* node, struct TreeNode* minNode, struct TreeNode* maxNode) {
    if (node == NULL) {
        return true; // 空节点默认合法
    }
    
    // 如果当前节点的值违反了上下界限制，则不是 BST
    if (minNode != NULL && node->val <= minNode->val) {
        return false;
    }
    if (maxNode != NULL && node->val >= maxNode->val) {
        return false;
    }
    
    // 递归检查左右子树：
    // 左子树的上限更新为当前 node
    // 右子树的下限更新为当前 node
    return isValidBSTHelper(node->left, minNode, node) && 
           isValidBSTHelper(node->right, node, maxNode);
}

bool isValidBST(struct TreeNode* root) {
    // 初始状态，没有上下界限制
    return isValidBSTHelper(root, NULL, NULL);
}
```

###  复杂度分析
* **时间复杂度**：$O(N)$，每个节点恰好被访问一次。
* **空间复杂度**：$O(H)$，$H$ 为树的高度。主要为递归调用栈的开销（最坏情况下树退化为链表为 $O(N)$，最好情况平衡树为 $O(\log N)$）。

---

## 💡 方法二：中序遍历法 (In-order Traversal)

这是利用了二叉搜索树非常重要的一个数学性质，也是解决很多 BST 进阶问题的通用钥匙。

###  核心逻辑
* **BST 的中序遍历（左 -> 根 -> 右）序列必然是一个严格递增的序列。**
* 我们不需要开辟数组来存储整个序列，只需要在遍历过程中，维护一个指向**上一个被访问节点**的指针 (`prev`)。
* 每次访问当前节点时，比较 `当前节点的值 > 上一个节点的值` 是否成立即可。
* **C语言技巧**：为了在递归的不同层级（不同的函数栈帧）中共享和修改同一个 `prev` 指针，必须使用**双重指针** `struct TreeNode** prev`。

###  C 语言代码实现
```c
#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 辅助函数：执行中序遍历，prev 是指向指针的指针
bool inorder(struct TreeNode* node, struct TreeNode** prev) {
    if (node == NULL) {
        return true;
    }
    
    // 1. 遍历并检查左子树
    if (!inorder(node->left, prev)) {
        return false;
    }
    
    // 2. 检查当前节点 (Root)
    // 如果当前节点的值 <= 上一个节点的值，破坏了严格递增性，不是 BST
    if (*prev != NULL && node->val <= (*prev)->val) {
        return false;
    }
    
    // 将当前节点记录为“上一个节点”，供后续节点比较
    *prev = node;
    
    // 3. 遍历并检查右子树
    return inorder(node->right, prev);
}

bool isValidBST(struct TreeNode* root) {
    struct TreeNode* prev = NULL;
    // 传入 prev 的地址
    return inorder(root, &prev);
}
```

###  复杂度分析
* **时间复杂度**：$O(N)$，最坏情况下需要访问所有节点。但如果发现不符合条件会提前返回（剪枝）。
* **空间复杂度**：$O(H)$，$H$ 为树的高度，主要为递归栈开销。

---

## 📝 总结与避坑指南
1. **常见陷阱**：初学者常犯的错误是只比较 `root->val > root->left->val`，这只能保证**局部**合法，无法保证**整棵**左子树的所有节点都小于根节点。
2. **方法选择**：
   * **上下界法**思路直接，代码清晰，推荐作为首选解法。
   * **中序遍历法**十分优雅，且深刻体现了 BST 的本质，在解决“寻找 BST 第 K 小节点”、“恢复错误 BST”等题目时，中序遍历是核心思路。