//我写的这种方式不可行
//主要是边界的范围处理和循环内部的条件判断不对
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
	int left = 0;
	int right = matrixColSize[0] - 1;
	int top = 0;
	int bottom = matrixSize - 1;
	*returnSize = matrixColSize[0] * matrixSize;
	int* result = (int*)malloc(sizeof(int) * (*returnSize));
	int idx = 0;
	while (left < right && top < bottom) {
		for (int i = left; i <= right; i++) {
			result[idx++] = matrix[top][i];
		}
		top++;
		for (int i = top; i <= bottom; i++) {
			result[idx++] = matrix[i][right];
		}
		right--;
		if (left <= right) {
			for (int i = right; i >= left; i--) {
				result[idx++] = matrix[bottom][i];
			}
			bottom--;
		}
		if (top <= bottom) {
			for (int i = bottom; i >= top; i--) {
				result[idx++] = matrix[i][left];
			}
			left++;
		}
	}
	return result;
}
