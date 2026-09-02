#include <stdio.h>

void main()
{
    int n, i;
    int marks[20];
    int sum = 0;
    float average;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("\nEnter marks of %d students:\n", n);
    for (i = 0; i < n; i++)
    {
        printf("Marks [%d]: ", i + 1);
        scanf("%d", &marks[i]);
        sum += marks[i];
    }

    average = (float)sum / n;

    printf("\nTotal marks: %d\n", sum);
    printf("Average marks: %.2f\n", average);
}
