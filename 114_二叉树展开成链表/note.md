# 📝 学习笔记：114. 二叉树展开为链表

##  核心破题点

题目要求将二叉树展开为一个单链表，且展开后的顺序需要与**前序遍历（根 -> 左 -> 右）**的结果一致。
展开后的节点只使用 `right` 指针连接，`left` 指针必须全部置为 `NULL`。



**核心难点：**
如果在传统的前序遍历中，直接修改当前节点的 `right` 指针指向左子节点，那么**原有的右子树就会丢失（断链）**。

---

##  避坑指南：C语言指针的危险操作

在手写链表/树的指针重排时，极易犯内存错误。
* **❌ 错误示范（未初始化内存）**：
    声明一个局部的结构体变量 `TreeNode tmp;` 然后直接传它的指针进去修改。`tmp` 里面的 `left` 和 `right` 全是随机的垃圾值，随意操作会导致**未定义行为（Undefined Behavior）**，极易引发 Segmentation Fault。
* **✅ 正确做法**：
    声明一个明确的空指针 `TreeNode* lastNode = NULL;`，并将它的**地址**（即二级指针 `&lastNode`）传给函数去更新指向。

---

##  三种渐进式解法详解

###  前序遍历（直觉修复版） —— 边走边连

顺着题意，前序遍历。为了防止右子节点丢失，**在修改指针前，先把左右子节点缓存下来**。

* **逻辑**：记录上一个访问的节点 `lastNode`。每次走到新节点，就把 `lastNode` 的右指针指向当前节点，左指针清空。
* **痛点**：必须使用额外的临时变量保存 `left` 和 `right`，略显累赘。

```c
void dfs(struct TreeNode* node, struct TreeNode** lastNode) {
    if (node == NULL) return;
    
    // 关键：提前保存左右节点，防止稍后被覆盖丢失！
    struct TreeNode* left = node->left;
    struct TreeNode* right = node->right;
    
    if (*lastNode != NULL) {
        (*lastNode)->left = NULL;
        (*lastNode)->right = node;
    }
    
    *lastNode = node; // 更新指针
    
    // 使用刚才保存下来的节点继续递归
    dfs(left, lastNode);    
    dfs(right, lastNode);
}
// 调用栈： TreeNode* last = NULL; dfs(root, &last);
```

###  逆后序遍历（优雅递归版） 🌟 推荐

既然“根 -> 左 -> 右”会覆盖右子节点，那我们**反过来遍历：“右 -> 左 -> 根”**。

* **逻辑**：先一路走到最右下角，从链表的尾部开始，从后往前拼装。
* **优势**：处理当前根节点时，它的右子树和左子树已经安全地展开成了链表。此时直接把当前节点的 `right` 指向刚刚处理完的后继节点即可，完全不需要缓存变量！

```c
void dfs_reverse(struct TreeNode* node, struct TreeNode** nextNode) {
    if (node == NULL) return;
    
    // 逆向思考：右 -> 左 -> 根
    dfs_reverse(node->right, nextNode);
    dfs_reverse(node->left, nextNode);
    
    // 此时右子树和左子树都已处理完，开始处理当前节点
    node->right = *nextNode;
    node->left = NULL;
    
    *nextNode = node; // 把自己变成下一个处理节点的后继
}
// 调用栈： TreeNode* next = NULL; dfs_reverse(root, &next);
```

###  寻找前驱节点（降维打击版） 🏆 面试满分答案

以上两种递归法，空间复杂度都是 $O(H)$（调用栈）。面试官常问：**如何用 $O(1)$ 的额外空间完成？**

* **逻辑（重排指针）**：
    1.  如果当前节点有左子树，那么按照前序遍历，右子树的所有节点一定排在左子树所有节点的后面。
    2.  因此，我们要找到**左子树的最右侧节点（即左子树的最后一个被访问的节点，称为前驱节点 pre）**。
    3.  把当前节点的右子树，直接剪切并粘贴到 `pre` 的右边。
    4.  然后把整个左子树移到当前节点的右边，左边置空。
    5.  向右移动一步，重复这个过程。



```c
void flatten(struct TreeNode* root) {
    struct TreeNode* curr = root;
    
    while (curr != NULL) {
        // 如果有左子树，就需要进行乾坤大挪移
        if (curr->left != NULL) {
            // 1. 找到左子树的最右侧节点 (前驱节点)
            struct TreeNode* pre = curr->left;
            while (pre->right != NULL) {
                pre = pre->right;
            }
            
            // 2. 将原来的右子树挂到前驱节点的右边
            pre->right = curr->right;
            
            // 3. 将整个左子树移到当前节点的右边，并清空左指针
            curr->right = curr->left;
            curr->left = NULL;
        }
        
        // 4. 继续处理下一个节点 (因为左子树已经全移到右边了，一路向右即可)
        curr = curr->right;
    }
}
```

---

##  复杂度对比分析

| 维度 | 解法 1: 前序遍历 | 解法 2: 逆后序遍历 | 解法 3: 找前驱节点 (迭代) |
| :--- | :--- | :--- | :--- |
| **时间复杂度** | $O(N)$ 每个节点访问一次 | $O(N)$ 每个节点访问一次 | $O(N)$ 寻找最右节点会有重复路程，但均摊下来仍是 $O(N)$ |
| **空间复杂度** | $O(H)$ 递归系统栈 | $O(H)$ 递归系统栈 | **$O(1)$ 无额外内存分配** |

---

##  总结与面试技巧

1.  **处理指针的黄金准则**：在切断/覆盖一个指针前，一定要问自己：“我还会不会用到被它指着的那个东西？” 如果会，请先把它存下来。
2.  **逆向思维的威力**：正向操作容易破坏数据时，尝试从尾到头（逆后序）处理，往往能化繁为简。
3.  **空间优化的终点**：在树结构中，追求 $O(1)$ 空间的算法通常意味着你要**利用树自带的空闲指针（比如叶子节点的左右指针）**，解法 3 便是这一思想的完美体现（类似于 Morris 遍历）。