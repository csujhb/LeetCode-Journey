# 学习笔记：108. 将有序数组转换为二叉搜索树

## 📌 题目描述
* **输入：** 一个按**升序排列**的整数数组 `nums`。
* **输出：** 一棵**高度平衡**的二叉搜索树（BST）。
* **高度平衡定义：** 一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1。

---

## 🧠 核心思想：分治法 (Divide and Conquer)
因为数组已经是**升序**的，这与二叉搜索树的**中序遍历**结果完全一致。
要保证构建出来的 BST 是“高度平衡”的，我们需要保证根节点左右两边的节点数量尽可能相等。因此，**每次选择数组的中间元素作为当前的根节点**是破局的核心。

**步骤拆解：**

1.  找到当前数组区间的中间位置 `mid`。
2.  将 `nums[mid]` 作为当前子树的根节点。
3.  以 `mid` 为界，将数组一分为二：
    * 左半部分 `[left, mid - 1]` 递归构建为左子树。
    * 右半部分 `[mid + 1, right]` 递归构建为右子树。

---

## 🚀 解题思路与算法实现

这道题存在多种解法，主要区别在于**中间节点的选择**以及**遍历方式（递归 vs 迭代）**。

### 方法一：递归法（始终选择左中间节点）—— 🌟 最佳实践
当数组长度为偶数时，中间节点有两个。此方法约定俗成地选择靠左的那个中间节点。

```c
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* buildNode(int* arr, int left, int right) {
    if (left > right) return NULL; // 递归终止条件
    
    // 安全地计算中间位置（左中间节点）
    int mid = left + (right - left) / 2; 
    
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = arr[mid];
    
    // 分治：递归构建左右子树
    root->left = buildNode(arr, left, mid - 1);
    root->right = buildNode(arr, mid + 1, right);
    
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    return buildNode(nums, 0, numsSize - 1);
}
```

### 方法二：递归法（始终选择右中间节点）
这是你最初尝试的思路。当数组长度为偶数时，选择靠右的中间节点。逻辑同上，仅中点计算公式不同。
* **中点公式：** `int mid = left + (right - left + 1) / 2;`

### 方法三：迭代法（借助队列模拟 BFS）

不使用系统调用栈，而是手动使用队列来维护“当前节点”和“对应的数组区间”。

> **注：** 此方法代码较长且容易出错，主要用于开拓思维和应对极端限制环境，日常工程与面试中**不推荐**作为首选。

```c
// 伪代码思路回顾
1. 初始化一个队列，将根节点和全数组区间 [0, numsSize-1] 作为一个任务入队。
2. 当队列不为空时，出队一个任务。
3. 计算该区间的 mid，为当前出队的节点赋值。
4. 如果 mid 左侧有元素，创建一个左空节点，并将（左空节点，左区间）入队。
5. 如果 mid 右侧有元素，创建一个右空节点，并将（右空节点，右区间）入队。
6. 循环直到队列为空。
7. #include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 定义一个结构体，用来打包保存节点和它需要处理的数组区间
struct Task {
    struct TreeNode* node;
    int left;
    int right;
};

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0) {
        return NULL;
    }

    // 先创建根节点（此时先不赋值）
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;

    // 模拟一个队列。因为是二叉树，队列的最大长度不会超过节点总数 numsSize
    struct Task* queue = (struct Task*)malloc(sizeof(struct Task) * numsSize);
    int head = 0; // 队头指针
    int tail = 0; // 队尾指针

    // 将根节点和完整的数组区间作为一个初始“任务”入队
    queue[tail].node = root;
    queue[tail].left = 0;
    queue[tail].right = numsSize - 1;
    tail++;

    // 当队列不为空时，循环处理任务
    while (head < tail) {
        // 出队：取出当前的任务
        struct Task current = queue[head++];
        struct TreeNode* currNode = current.node;
        int l = current.left;
        int r = current.right;

        // 计算中间位置，并给当前节点赋值
        int mid = l + (r - l) / 2;
        currNode->val = nums[mid];

        // 处理左半区间：如果左边还有元素，说明存在左子树
        if (l <= mid - 1) {
            // 创建左子节点
            currNode->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            currNode->left->left = NULL;
            currNode->left->right = NULL;
            
            // 将左子节点和左半区间打包成新任务，入队
            queue[tail].node = currNode->left;
            queue[tail].left = l;
            queue[tail].right = mid - 1;
            tail++;
        }

        // 处理右半区间：如果右边还有元素，说明存在右子树
        if (mid + 1 <= r) {
            // 创建右子节点
            currNode->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            currNode->right->left = NULL;
            currNode->right->right = NULL;
            
            // 将右子节点和右半区间打包成新任务，入队
            queue[tail].node = currNode->right;
            queue[tail].left = mid + 1;
            queue[tail].right = r;
            tail++;
        }
    }

    // 释放队列使用的内存
    free(queue);
    
    return root;
}
```

---

## ⏱️ 复杂度分析

对于上述的递归算法（方法一和方法二）：

| 维度 | 复杂度 | 说明 |
| :--- | :--- | :--- |
| **时间复杂度** | $O(N)$ | $N$ 为数组长度。每个数字都会且仅会被访问一次，用来创建一个树节点。 |
| **空间复杂度** | $O(\log N)$ | 主要是递归调用栈的开销。因为我们构建的是高度平衡的 BST，所以树的高度严格对数化为 $\log N$。 |

---

## 🚨 踩坑记录与排雷指南

在手写二分查找或分治算法时，计算中点位置是一个高频踩坑点！

* ❌ **危险写法：** `int mid = (left + right) / 2;`
    * **原因：** 当 `left` 和 `right` 的值很大时（接近 `INT_MAX`），两数相加会直接导致**整数溢出**，变成负数，继而导致数组越界，程序崩溃（Segmentation Fault）。
* ✅ **安全写法：** `int mid = left + (right - left) / 2;`
    * **原因：** 通过相减求距离，再加到基准值上，完美规避了相加溢出的风险。这是所有二分/分治类算法的**黄金标准写法**。

---

## 🎯 总结

《将有序数组转换为二叉搜索树》是一道极其经典的**树+分治**入门题。
1.  **数据结构特性：** 深刻理解 BST 的中序遍历即为有序数组这一特性，是逆向推导构建过程的关键。
2.  **代码范式：** 树的结构天生适合用**递归**来表达。在面对天然具有自相似性的问题时（比如一棵树的左右子树本身也是一棵树），优先考虑递归，它可以让代码逻辑变得极度清晰优雅。
3.  **工程严谨性：** 永远对涉及数字相加的操作保持警惕，养成使用 `left + (right - left) / 2` 的肌肉记忆。