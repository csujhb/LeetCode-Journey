# 📝 LeetCode 155. 最小栈 (Min Stack) 学习笔记

## 核心思想：空间换时间
普通的栈实现 `push`、`pop` 和 `top` 操作的时间复杂度天然是 $O(1)$。但由于栈是“后进先出”（LIFO）的数据结构，要随时知道当前的最小值，就必须记录**“每一次压栈操作发生后的当前全局最小值”**。

核心解法是引入**辅助记录**（无论是合并在结构体内还是用独立的辅助栈），在每次压入新元素时，同步计算并保存当前层级的最小值。

**状态转移逻辑：**

* 当栈为空时压入第一个元素：`当前层最小值 = 该元素本身`
* 当栈非空时压入新元素：`当前层最小值 = min(新元素, 上一层的最小值)`

---

## C 语言实现方案对比与核心代码

在 C 语言中，这道题的实现方式完美体现了不同的工程权衡（Trade-off）。主要分为三种流派：

### 结构体单数组 (AoS - Array of Structures) / 动态扩容
* **做法：** 定义一个包含当前值和最小值的结构体，栈本质上是一个存放该结构体的动态数组。
* **优势：** 内存安全（只有一次分配，错误回滚容易，极少发生内存泄漏），缓存友好（强相关数据物理相邻，提升 CPU 缓存命中率）。
* **适用场景：** 真实的工业级 C/C++ 工程项目。

```c
#include <stdlib.h>

typedef struct {
    int val;
    int min;
} Element;

typedef struct {
    Element* arr;
    int topIndex;
    int capacity;
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->capacity = 8192;
    obj->arr = (Element*)malloc(obj->capacity * sizeof(Element));
    obj->topIndex = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->topIndex == obj->capacity - 1) {
        obj->capacity *= 2;
        obj->arr = (Element*)realloc(obj->arr, obj->capacity * sizeof(Element));
    }
    obj->topIndex++;
    obj->arr[obj->topIndex].val = val;
    if (obj->topIndex == 0) {
        obj->arr[obj->topIndex].min = val;
    } else {
        int currentMin = obj->arr[obj->topIndex - 1].min;
        obj->arr[obj->topIndex].min = (val < currentMin) ? val : currentMin;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->topIndex >= 0) obj->topIndex--;
}

int minStackTop(MinStack* obj) {
    return obj->arr[obj->topIndex].val;
}

int minStackGetMin(MinStack* obj) {
    return obj->arr[obj->topIndex].min;
}

void minStackFree(MinStack* obj) {
    if (obj) {
        if (obj->arr) free(obj->arr);
        free(obj);
    }
}
```

### 双数组 (SoA - Structure of Arrays) / 动态扩容
* **做法：** 结构体包含两个独立的动态数组指针。
* **优势：** 极其直观，完美契合教科书中“主栈 + 辅助栈”的逻辑，代码可读性极强。
* **劣势：** 扩容时需要连续两次调用 `realloc`，极端情况下可能出现一个成功一个失败的“状态不一致”问题。
* **适用场景：** 面试手写代码（向面试官解释逻辑最清晰）。

```c
#include <stdlib.h>

typedef struct {
    int *data;      // 普通栈
    int *mins;      // 最小值栈
    int size;       // 当前元素个数
    int capacity;   // 栈容量
} MinStack;

MinStack* minStackCreate() {
    MinStack *obj = (MinStack *)malloc(sizeof(MinStack));
    obj->capacity = 16;
    obj->size = 0;
    obj->data = (int *)malloc(sizeof(int) * obj->capacity);
    obj->mins = (int *)malloc(sizeof(int) * obj->capacity);
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->size == obj->capacity) {
        obj->capacity *= 2;
        obj->data = (int *)realloc(obj->data, sizeof(int) * obj->capacity);
        obj->mins = (int *)realloc(obj->mins, sizeof(int) * obj->capacity);
    }
    obj->data[obj->size] = val;
    if (obj->size == 0) {
        obj->mins[obj->size] = val;
    } else {
        int currentMin = obj->mins[obj->size - 1];
        obj->mins[obj->size] = val < currentMin ? val : currentMin;
    }
    obj->size++;
}

void minStackPop(MinStack* obj) {
    if (obj->size > 0) obj->size--;
}

int minStackTop(MinStack* obj) {
    return obj->data[obj->size - 1];
}

int minStackGetMin(MinStack* obj) {
    return obj->mins[obj->size - 1];
}

void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj->mins);
    free(obj);
}
```

### 双数组 / 定长静态数组 (刷题特化版)
* **做法：** 直接在结构体中声明写死大小的数组。
* **优势：** 没有任何 `realloc` 动态分配开销，评测机运行速度无敌，代码精简，免去了容量检查。
* **劣势：** 空间利用率极差，且存在 10000 次上限的硬伤，超出则越界崩溃。
* **适用场景：** 算法竞赛（ACM/OI）、LeetCode 刷题（已知数据量不会超标的前提下）。

```c
#include <stdlib.h>

typedef struct {
    int dataStack[10000];
    int minStack[10000];
    int dataTop;
    int minTop;
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->dataTop = -1;
    obj->minTop = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    obj->dataStack[++obj->dataTop] = val;
    if (obj->minTop == -1 || val < obj->minStack[obj->minTop]) {
        obj->minStack[++obj->minTop] = val;
    } else {
        obj->minStack[obj->minTop + 1] = obj->minStack[obj->minTop];
        obj->minTop++;
    }
}

void minStackPop(MinStack* obj) {
    obj->dataTop--;
    obj->minTop--;
}

int minStackTop(MinStack* obj) {
    return obj->dataStack[obj->dataTop];
}

int minStackGetMin(MinStack* obj) {
    return obj->minStack[obj->minTop];
}

void minStackFree(MinStack* obj) {
    free(obj);
}
```

---

## 方案对比总结表

| 方案 | 内存布局 | 空间分配 | 优点 | 缺点 | 适用场景 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **单数组打包 (AoS)** | 单数组 | 动态扩容 | 内存安全，扩容原子性高，缓存友好 | 逻辑不如双栈直观 | 工业级代码开发 |
| **双数组分离 (SoA)** | 双数组 | 动态扩容 | 逻辑极其直观，完美对应概念 | 需维护两个指针，存在扩容失败风险 | 面试白板编程 |
| **定长硬编码** | 双数组 | 静态分配 | 运行速度极快，代码最短 | 存在越界风险，极度浪费内存 | LeetCode 刷题 |

---

## 复杂度分析

无论采用上述哪种方案，时间与空间复杂度的理论值都是一致的：

* **时间复杂度：** $O(1)$
  * `push`、`pop`、`top`、`getMin` 均只涉及数组末尾的直接索引和常数级别的比较。
  * *注：动态扩容方案在触发 `realloc` 时会有 $O(n)$ 开销，但均摊时间复杂度依然是 $O(1)$。*
* **空间复杂度：** $O(n)$
  * 我们需要额外的空间来存储每个状态下的最小值。$n$ 为栈中元素的数量。

---

## 避坑指南与经验法则 (Tips)

* **小心栈溢出 (Stack Overflow)：** 如果使用“定长静态数组”方案，**切忌**在函数内使用局部变量初始化（如 `MinStack obj;`），这会将几十 KB 的数据强塞进系统的函数调用栈导致崩溃。必须使用 `malloc(sizeof(MinStack))` 将其分配到**堆区 (Heap)**。
* **出栈操作的健壮性：** 在执行 `pop` 或 `top` 前，最好养成习惯检查栈是否为空（例如判断 `size > 0` 或 `topIndex >= 0`），防止非法内存访问引发的段错误。