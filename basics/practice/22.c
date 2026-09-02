#include <stdio.h>

void main()
{
    int rows, cols, i, j;
    int matrix[10][10];
    int evenSum = 0, oddSum = 0;

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

    // Calculate sum of even and odd numbers
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] % 2 == 0)
            {
                evenSum += matrix[i][j];
            }
            else
            {
                oddSum += matrix[i][j];
            }
        }
    }

    printf("\nSum of even numbers: %d\n", evenSum);
    printf("Sum of odd numbers: %d\n", oddSum);
}
