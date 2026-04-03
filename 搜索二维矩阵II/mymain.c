#include <stdbool.h>

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
	int row = 0;
	int col = matrixColSize[0] - 1;
	while (row < matrixSize && col >= 0) {
		if (target < matrix[row][col]) {
			col--;
		}
		else if (target > matrix[row][col]) {
			row++;
		}
		else {
			return true;
		}
	}
	return false;
}
