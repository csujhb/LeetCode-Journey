#include <stdlib.h>

int cmp(const void* a, const void* b) {
    // a, b 是指向指针的指针，即 int** 类型
    int* row_a = *(int**)a;   // 获取行指针
    int* row_b = *(int**)b;
    return (row_a[0] > row_b[0]) - (row_a[0] < row_b[0]);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    qsort(intervals, intervalsSize, sizeof(int*), cmp);
    int** result = (int**)malloc(intervalsSize*sizeof(int*));
    for (int i = 0; i < intervalsSize; i++) {
        result[*returnSize][0] = intervals[i][0];
        int max = intervals[i][1];
        while (i + 1 < intervalsSize && max >= intervals[i + 1][0]) {
            i++;
            if (max < intervals[i][1])  max = intervals[i][1];
        }
        result[*returnSize][1] = max;
        (*returnSize)++;
    }
    *returnColumnSizes = (int*)calloc(*returnSize, sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    *intervalsColSize = 2;
    return result;
}
