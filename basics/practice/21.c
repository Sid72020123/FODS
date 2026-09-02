#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix[10][10];

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("\nEnter matrix elements:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nEven numbers in matrix: ");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] % 2 == 0)
            {
                printf("%d ", matrix[i][j]);
            }
        }
    }

    printf("\n\nOdd numbers in matrix: ");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] % 2 != 0)
            {
                printf("%d ", matrix[i][j]);
            }
        }
    }
    printf("\n");
}
