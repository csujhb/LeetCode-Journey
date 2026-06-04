// 2026.06.04
void setZeroes(int **matrix, int matrixSize, int *matrixColSize)
{
    int cols = *matrixColSize;
    int first_row = 0;
    int first_col = 0;
    for (int i = 0; i < cols; i++)
    {
        if (matrix[0][i] == 0)
        {
            first_row = 1;
            break;
        }
    }
    for (int i = 0; i < matrixSize; i++)
    {
        if (matrix[i][0] == 0)
        {
            first_col = 1;
            break;
        }
    }
    for (int i = 1; i < matrixSize; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for (int i = 1; i < matrixSize; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            if (matrix[0][j] == 0 || matrix[i][0] == 0)
            {
                matrix[i][j] = 0;
            }
        }
    }

    if (first_row)
    {
        for (int i = 0; i < cols; i++)
        {
            matrix[0][i] = 0;
        }
    }
    if (first_col)
    {
        for (int i = 0; i < matrixSize; i++)
        {
            matrix[i][0] = 0;
        }
    }
}