/*
空间复杂度：O(M+N)
时间复杂度：O(MN)
*/

#include <stdlib.h>
void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
	int* col = (int*)calloc(*matrixColSize, sizeof(int));
	int* row = (int*)calloc(matrixSize, sizeof(int));
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < *matrixColSize; j++) {
			if (matrix[i][j] == 0) {
					row[i] = 1;
					col[j] = 1;
			}

		}
	}
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < *matrixColSize; j++) {
			if (row[i]!= 0) {
				matrix[i][j] = 0;
			}
		}
	}
	for (int j = 0; j < *matrixColSize; j++) {
		for (int i = 0; i < matrixSize; i++) {
			if (col[j] != 0) {
				matrix[i][j] = 0;
			}
		}
	}
	free(col);
	free(row);
}
