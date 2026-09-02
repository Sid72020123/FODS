#include <stdio.h>

void main()
{
    int n, i, j;
    int arr[10][10];
    int rows, cols;
    float sum = 0, average;
    int count = 0;
    int choice;

    printf("Choose array type:\n");
    printf("1. 1D Array\n");
    printf("2. 2D Array\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\nEnter number of elements: ");
        scanf("%d", &n);

        printf("\nEnter array elements:\n");
        for (i = 0; i < n; i++)
        {
            printf("Element [%d]: ", i);
            scanf("%d", &arr[0][i]);
            sum += arr[0][i];
        }
        average = sum / n;

        printf("\nSum: %.2f\n", sum);
        printf("Average: %.2f\n", average);
    }
    else if (choice == 2)
    {
        printf("\nEnter number of rows: ");
        scanf("%d", &rows);

        printf("Enter number of columns: ");
        scanf("%d", &cols);

        printf("\nEnter matrix elements:\n");
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                printf("Element [%d][%d]: ", i, j);
                scanf("%d", &arr[i][j]);
                sum += arr[i][j];
                count++;
            }
        }
        average = sum / count;

        printf("\nSum: %.2f\n", sum);
        printf("Average: %.2f\n", average);
    }
}
