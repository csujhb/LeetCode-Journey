#include <stdlib.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int **res=(int**)malloc(sizeof(int *)*numRows);
    * returnColumnSizes=(int*)malloc(sizeof(int)*numRows);
    res[0]=(int*)malloc(sizeof(int));
    res[0][0]=1;
    (*returnColumnSizes)[0]=1;
    for(int i=1;i<numRows;i++){
        res[i]=(int*)malloc(sizeof(int)*(i+1));
        res[i][0]=1;
        res[i][i]=1;
        for(int j=1;j<i;j++){
            res[i][j]=res[i-1][j-1]+res[i-1][j];
        }
        (*returnColumnSizes)[i]=i+1;
    }
    * returnSize=numRows;
    return res;
}