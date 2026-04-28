//顺时针旋转90度，相当于先转置，再左右翻转
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < i; j++) {
			int temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}

	for (int i = 0; i < matrixSize; i++) {
		int left = 0;
		int right = matrixSize - 1;
		while (left < right) {
			int temp = matrix[i][left];
			matrix[i][left] = matrix[i][right];
			matrix[i][right] = temp;
			left++;
			right--;
		}
	}
}

