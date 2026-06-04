// 2026.06.04
void rotate(int **matrix, int matrixSize, int *matrixColSize)
{
    int cols = *matrixColSize;
    int rows = matrixSize;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
    int left = 0;
    int right = cols - 1;
    while (left < right)
    {
        for (int i = 0; i < rows; i++)
        {
            int temp = matrix[i][left];
            matrix[i][left] = matrix[i][right];
            matrix[i][right] = temp;
        }
        left++;
        right--;
    }
}