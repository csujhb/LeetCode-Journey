---

# 📚 学习笔记：随机链表的复制 (LeetCode 138)

## 题目核心痛点：先有鸡还是先有蛋？

我们要进行的是 **深拷贝（Deep Copy）**，不仅要创建全新的节点，还要完美复刻所有指针。
* **`next` 指针**很好处理，顺着链表一边走一边创建即可。
* **`random` 指针是灾难**：当我们在创建节点 A'，并试图连接 A' 的 `random` 时，它指向的目标节点 C' **可能还没有被创建出来**！这就是本题最大的痛点。

---

## 解法一：哈希表法（空间换时间）—— 逻辑最直观

* **时间复杂度**：$O(N)$
* **空间复杂度**：$O(N)$（使用了额外的哈希表）

### 💡 核心思想

准备一个“字典”（哈希表），建立 **`原节点 -> 新节点`** 的一一映射关系：
1.  **第一趟遍历**：不管指针，先把所有新节点在内存里“生造”出来，并存入字典。
2.  **第二趟遍历**：照着字典查表，把新节点的 `next` 和 `random` 连上。

### 💻 伪代码（C++ / Java 首选）

```cpp
// 1. 造节点查字典
while (curr) {
    nodeMap[curr] = new Node(curr->val);
    curr = curr->next;
}
// 2. 连指针查字典
while (curr) {
    nodeMap[curr]->next = nodeMap[curr->next];
    nodeMap[curr]->random = nodeMap[curr->random];
    curr = curr->next;
}
```

---

## 解法二：节点交织法（顶级神仙微操）—— 真正的工业级写法

在 C 语言这种缺乏内置哈希表的底层语言中，我们需要用纯指针操作来化解危机。

* **时间复杂度**：$O(N)$
* **空间复杂度**：$O(1)$（完美！）

### 💡 核心思想：三步走战略


#### 第一步：克隆并交织（肉身绑定）
将新克隆的节点直接插在原节点的正后方：
* **原链表**：`A -> B -> C`
* **交织后**：`A -> A' -> B -> B' -> C -> C'`

#### 第二步：复制 Random 指针（借力打力）
这是全场最精华的一步！因为交织结构，我们有了一个无敌公式：
**`新节点的 target = 原节点 target 的下一个节点`**
翻译成代码就是：`curr->next->random = curr->random->next`。利用原节点的 `random` 作为跳板，瞬间找到克隆目标！

#### 第三步：拆分链表（过河拆桥）
将交织的长链表拆开，恢复原链表，并提取出纯净的克隆链表。
**注意**：绝对不能只提取克隆链表而破坏原链表结构，否则会被评测机报错。

### 💻 核心代码：节点交织法 (纯 C 语言实现)

```c
struct Node* copyRandomList(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* curr = head;

    // 第一步：克隆节点，并将其“肉身绑定”在原节点的正后方
    while (curr != NULL) {
        struct Node* cloneNode = (struct Node*)malloc(sizeof(struct Node));
        cloneNode->val = curr->val;
        
        cloneNode->next = curr->next;
        curr->next = cloneNode;
        
        curr = cloneNode->next;
    }

    // 第二步：借力打力，为克隆节点连接 random 指针
    curr = head;
    while (curr != NULL) {
        struct Node* cloneNode = curr->next;
        
        if (curr->random != NULL) {
            // 【核心公式】：克隆节点的 random = 原节点 random 指向目标的“下一个节点”
            cloneNode->random = curr->random->next;
        } else {
            cloneNode->random = NULL;
        }
        
        curr = cloneNode->next;
    }

    // 第三步：过河拆桥，拆分链表
    curr = head;
    struct Node* cloneHead = head->next; 
    
    while (curr != NULL) {
        struct Node* cloneNode = curr->next;
        struct Node* nextOriginal = cloneNode->next; 
        
        // 1. 恢复原链表的 next
        curr->next = nextOriginal;
        
        // 2. 连接克隆链表的 next
        if (nextOriginal != NULL) {
            cloneNode->next = nextOriginal->next;
        } else {
            cloneNode->next = NULL;
        }
        
        // 3. curr 移动到下一个原节点
        curr = nextOriginal;
    }

    return cloneHead;
}
```

---

## 死亡雷区 (面试高频翻车点)

* **空指针解引用 (Segfault)**：在第二步赋值 `random` 时，原节点的 `random` 可能为 `NULL`。必须加 `if (curr->random != NULL)` 判断，否则 `curr->random->next` 会直接引发段错误导致程序崩溃。
* **破坏原始输入数据**：在第三步拆分链表时，一定要双管齐下，把原链表的 `next` 恢复原样。只提取克隆链表而不恢复原链表在工程上是严重的 **副作用（Side Effect）**，会导致评测判错。