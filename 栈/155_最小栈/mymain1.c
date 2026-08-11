#include <stdlib.h>

typedef struct
{
    int val;
    int min;
} Element;

typedef struct
{
    Element *arr;
    int topIndex;
    int capacity;
} MinStack;

MinStack *minStackCreate()
{
    MinStack *obj = (MinStack *)malloc(sizeof(MinStack));
    obj->capacity = 8192;
    obj->arr = (Element *)malloc(obj->capacity * sizeof(Element));
    obj->topIndex = -1;
    return obj;
}

void minStackPush(MinStack *obj, int val)
{
    if (obj->topIndex == obj->capacity - 1)
    {
        obj->capacity *= 2;
        obj->arr = (Element *)realloc(obj->arr, obj->capacity * sizeof(Element));
    }
    obj->topIndex++;
    obj->arr[obj->topIndex].val = val;
    if (obj->topIndex == 0)
    {
        obj->arr[obj->topIndex].min = val;
    }
    else
    {
        int currentMin = obj->arr[obj->topIndex - 1].min;
        obj->arr[obj->topIndex].min = (val < currentMin) ? val : currentMin;
    }
}

void minStackPop(MinStack *obj)
{
    if (obj->topIndex >= 0)
    {
        obj->topIndex--;
    }
}

int minStackTop(MinStack *obj)
{
    return obj->arr[obj->topIndex].val;
}

int minStackGetMin(MinStack *obj)
{
    return obj->arr[obj->topIndex].min;
}

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