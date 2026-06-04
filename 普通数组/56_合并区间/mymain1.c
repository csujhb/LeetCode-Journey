// 2026.6.4
#include <stdlib.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int cmp(const void *p1, const void *p2)
{
    int res1 = (*(int **)p1)[0];
    int res2 = (*(int **)p2)[0];
    return res1 > res2;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize, int **returnColumnSizes)
{
    int **res = (int **)malloc(intervalsSize * sizeof(int *));
    *returnColumnSizes = (int *)malloc(intervalsSize * sizeof(int));
    qsort(intervals, intervalsSize, sizeof(int *), cmp);
    *returnSize = 0;
    for (int i = 0; i < intervalsSize; i++)
    {
        int start = intervals[i][0];
        int end = intervals[i][1];
        while (i + 1 < intervalsSize && end >= intervals[i + 1][0])
        {
            i++;
            end = MAX(intervals[i][1], end);
        }
        res[*returnSize] = (int *)malloc(2 * sizeof(int));
        res[*returnSize][0] = start;
        res[*returnSize][1] = end;
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize)++;
    }
    return res;
}