/*
相对于我最开始写的代码，主要进行了以下修改：
1）给 result[*returnSize] 分配空间：result[*returnSize] = (int*)malloc(2 * sizeof(int));
2）删掉这句：*intervalsColSize = 2;

*/

#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int* row_a = *(int**)a;
    int* row_b = *(int**)b;
    return (row_a[0] > row_b[0]) - (row_a[0] < row_b[0]);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
    int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    // 按区间左端点排序
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    // 最多合并出 intervalsSize 个区间
    int** result = (int**)malloc(intervalsSize * sizeof(int*));

    for (int i = 0; i < intervalsSize; i++) {
        // 给当前结果行分配空间
        result[*returnSize] = (int*)malloc(2 * sizeof(int));

        // 当前合并区间的起点
        result[*returnSize][0] = intervals[i][0];
        int max = intervals[i][1];

        // 向后合并所有有重叠的区间
        while (i + 1 < intervalsSize && max >= intervals[i + 1][0]) {
            i++;
            if (max < intervals[i][1]) {
                max = intervals[i][1];
            }
        }

        // 当前合并区间的终点
        result[*returnSize][1] = max;
        (*returnSize)++;
    }

    // 返回每一行的列数，都是 2
    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    return result;
}
