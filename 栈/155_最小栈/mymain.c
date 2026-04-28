
#include <stdlib.h>
typedef struct
{
    int *stack;
    int size;
    int capacity;
    int *min_arr;
} MinStack;

MinStack *minStackCreate()
{
    MinStack *obj = (MinStack *)malloc(sizeof(MinStack));

    obj->capacity = 16;
    obj->size = 0;

    obj->stack = (int *)malloc(sizeof(int) * obj->capacity);
    obj->min_arr = (int *)malloc(sizeof(int) * obj->capacity);

    return obj;
}

void minStackPush(MinStack *obj, int val)
{
    if (obj->size == obj->capacity)
    {
        obj->capacity *= 2;

        obj->stack = (int *)realloc(obj->stack, sizeof(int) * obj->capacity);
        obj->min_arr = (int *)realloc(obj->min_arr, sizeof(int) * obj->capacity);
    }
    obj->stack[obj->size] = val;
    if (obj->size == 0)
    {
        obj->min_arr[obj->size] = val;
    }
    else
    {
        int currentMin = obj->min_arr[obj->size - 1];
        obj->min_arr[obj->size] = val < currentMin ? val : currentMin;
    }
    obj->size++;
}

void minStackPop(MinStack *obj)
{
    if (obj->size == 0)
    {
        return;
    }
    else
    {
        obj->size--;
    }
}

int minStackTop(MinStack *obj)
{
    return obj->stack[obj->size - 1];
}

int minStackGetMin(MinStack *obj)
{
    return obj->min_arr[obj->size - 1];
}

void minStackFree(MinStack *obj)
{
    free(obj->stack);
    free(obj->min_arr);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/