#include <stdlib.h>

// 定义栈中每个元素的结构：同时保存原始值和到达该层的最小值
typedef struct
{
    int val;
    int min;
} Element;

typedef struct
{
    Element *arr; // 动态数组指针
    int topIndex; // 栈顶索引
    int capacity; // 栈的当前容量
} MinStack;

// 初始化堆栈对象
MinStack *minStackCreate()
{
    MinStack *obj = (MinStack *)malloc(sizeof(MinStack));
    obj->capacity = 8192; // 设置一个合理的初始容量（可以根据需要扩容）
    obj->arr = (Element *)malloc(obj->capacity * sizeof(Element));
    obj->topIndex = -1; // 初始化为空栈
    return obj;
}

// 将元素 val 推入堆栈
void minStackPush(MinStack *obj, int val)
{
    // 动态扩容机制（如果超出了当前容量）
    if (obj->topIndex == obj->capacity - 1)
    {
        obj->capacity *= 2;
        obj->arr = (Element *)realloc(obj->arr, obj->capacity * sizeof(Element));
    }

    obj->topIndex++;
    obj->arr[obj->topIndex].val = val;

    // 如果是第一个元素，它自己就是最小值
    if (obj->topIndex == 0)
    {
        obj->arr[obj->topIndex].min = val;
    }
    else
    {
        // 否则，比较当前值和上一层的最小值，取更小的那个
        int currentMin = obj->arr[obj->topIndex - 1].min;
        obj->arr[obj->topIndex].min = (val < currentMin) ? val : currentMin;
    }
}

// 删除堆栈顶部的元素
void minStackPop(MinStack *obj)
{
    if (obj->topIndex >= 0)
    {
        obj->topIndex--;
    }
}

// 获取堆栈顶部的元素
int minStackTop(MinStack *obj)
{
    return obj->arr[obj->topIndex].val;
}

// 获取堆栈中的最小元素
int minStackGetMin(MinStack *obj)
{
    return obj->arr[obj->topIndex].min;
}

// 释放内存，防止内存泄漏
void minStackFree(MinStack *obj)
{
    if (obj)
    {
        if (obj->arr)
        {
            free(obj->arr);
        }
        free(obj);
    }
}
/*
typedef struct {
      int dataStack[10000];
      int minStack[10000];
      int dataTop;
      int minTop;
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj=(MinStack*)malloc(sizeof(MinStack));
    obj->dataTop=-1;
    obj->minTop=-1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    obj->dataStack[++obj->dataTop]=val;
    if(obj->minTop==-1||val<obj->minStack[obj->minTop])
    obj->minStack[++obj->minTop]=val;
    else{
    obj->minStack[obj->minTop+1]=obj->minStack[obj->minTop];obj->minTop++;
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
*/